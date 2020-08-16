/**
*   @file    Reg_eSys.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Base - BIP Memory and DMA mapping.
*   @details Memory mapping of the IP modules and DMA channels present on the MPC5777C 
*            hardware platform.
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
* @file        Reg_eSys.h
* 
*/

/** 
* @page misra_violations MISRA-C:2004 violations
* 
* @section Reg_eSys_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file 
* This comes from the order of includes in the .c file and from include dependencies. As a safe 
* approach, any file must include all its dependencies. Header files are already protected against 
* double inclusions.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters.The used compilers use more than 31 chars for
* identifiers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and functions
* shall not be reused. The driver needs to use defines starting with letter E.
*/

#ifndef REG_ESYS_H
#define REG_ESYS_H

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
* @file        Reg_eSys.h
* @brief Include platform types
* @violates @ref Reg_eSys_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "Platform_Types.h"

/** 
* @file        Reg_eSys.h
* @brief Include IP module versions
*/
#include "Soc_Ips.h"


/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define REG_ESYS_VENDOR_ID                    43
#define REG_ESYS_MODULE_ID                    0
#define REG_ESYS_AR_RELEASE_MAJOR_VERSION     4
#define REG_ESYS_AR_RELEASE_MINOR_VERSION     0
#define REG_ESYS_AR_RELEASE_REVISION_VERSION  3
#define REG_ESYS_SW_MAJOR_VERSION             1
#define REG_ESYS_SW_MINOR_VERSION             0
#define REG_ESYS_SW_PATCH_VERSION             1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Platform_Types.h header file are of the same Autosar version */
    #if ((REG_ESYS_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
         (REG_ESYS_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Reg_eSys.h and Platform_Types.h are different"
    #endif
#endif

/* Check if source file and Soc_Ips.h header file have same versions */
#if (REG_ESYS_VENDOR_ID != SOC_IPS_VENDOR_ID)
#error "Reg_eSys.h and Soc_Ips.h have different vendor IDs"
#endif
#if ((REG_ESYS_AR_RELEASE_MAJOR_VERSION != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
     (REG_ESYS_AR_RELEASE_MINOR_VERSION != SOC_IPS_AR_RELEASE_MINOR_VERSION) || \
     (REG_ESYS_AR_RELEASE_REVISION_VERSION != SOC_IPS_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Reg_eSys.h and Soc_Ips.h are different"
#endif
#if ((REG_ESYS_SW_MAJOR_VERSION != SOC_IPS_SW_MAJOR_VERSION) || \
     (REG_ESYS_SW_MINOR_VERSION != SOC_IPS_SW_MINOR_VERSION) || \
     (REG_ESYS_SW_PATCH_VERSION != SOC_IPS_SW_PATCH_VERSION))
#error "Software Version Numbers of Reg_eSys.h and Soc_Ips.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/** 
* @brief Internal Flash 
* @details MPC5777C System Memory Map 
*/
#define INTERNAL_FLASH_BASEADDR             ((uint32)0x00000000UL)
/** 
* @brief External Development Memory
* @details MPC5777C System Memory Map 
*/
#define EXTERNAL_DEV_MEM_BASEADDR           ((uint32)0x20000000UL)
/** 
* @brief Internal RAM
* @details MPC5777C System Memory Map 
*/
#define INTERNAL_RAM_BASEADDR               ((uint32)0x40000000UL)
/** 
* @brief Internal IGF
* @details MPC5777C System Memory Map 
*/
#define IGF_1_BASEADDR               ((uint32)0xC3E04000UL)        
/** 
* @brief Internal PSI5
* @details MPC5777C System Memory Map 
*/
#define PSI5_1_BASEADDR              ((uint32)0xC3E14000UL) 

/** 
* @brief Internal SDADC0
* @details MPC5777C System Memory Map 
*/       
#define SDADC0_BASEADDR     ((uint32)0xC3E44000UL)

/** 
* @brief Internal SDADC2
* @details MPC5777C System Memory Map 
*/
#define SDADC2_BASEADDR     ((uint32)0xC3E48000UL)
/** 
* @brief Internal EQADC1
* @details MPC5777C System Memory Map 
*/
#define EQADC1_BASEADDR     ((uint32)0xC3E54000UL)
/** 
* @brief Internal SRX1
* @details MPC5777C System Memory Map 
*/
#define SRX1_BASEADDR       ((uint32)0xC3E5C000UL)
/** 
* @brief Internal FLEXCAN3
* @details MPC5777C System Memory Map 
*/
#define FLEXCAN3_BASEADDR   ((uint32)0xC3E60000UL)
/** 
* @brief Internal FLEXCAN4
* @details MPC5777C System Memory Map 
*/
#define FLEXCAN4_BASEADDR   ((uint32)0xC3E64000UL)
/**
@brief  MCAN_1 (Controller Area Network 1)
@details MPC5777C System Memory Map
*/
#define MCAN1_BASEADDR                          ((uint32)0xFFE30000UL)

/**
@brief  MCAN_2 (Controller Area Network 2)
@details MPC5777C System Memory Map
*/
#define MCAN2_BASEADDR                          ((uint32)0xFFE38000UL)

/** 
* @brief Internal CMU
* @details MPC5777C System Memory Map 
*/                         
#define CMU0_BASEADDR       ((uint32)0xC3E6C200UL)
#define CMU1_BASEADDR       ((uint32)0xC3E6C240UL)
#define CMU2_BASEADDR       ((uint32)0xC3E6C280UL)
#define CMU3_BASEADDR       ((uint32)0xC3E6C2C0UL)
#define CMU4_BASEADDR       ((uint32)0xC3E6C300UL)
#define CMU5_BASEADDR       ((uint32)0xC3E6C340UL)
#define CMU6_BASEADDR       ((uint32)0xC3E6C380UL)
#define CMU7_BASEADDR       ((uint32)0xC3E6C3C0UL)
#define CMU8_BASEADDR       ((uint32)0xC3E6C400UL)
/** 
* @brief Internal FCCU
* @details MPC5777C System Memory Map 
*/                              
#define FCCU_BASEADDR       ((uint32)0xC3F80000UL)
/** 
* @brief Internal EBI
* @details MPC5777C System Memory Map 
*/ 
#define EBI_BASEADDR        ((uint32)0xC3F84000UL)
/** 
* @brief Internal SIU
* @details MPC5777C System Memory Map 
*/ 
#define SIU_BASEADDR        ((uint32)0xC3F90000UL)
#define SIU_B_BASEADDR      ((uint32)0xC3F98000UL)

/** 
* @brief Internal EMIOS1
* @details MPC5777C System Memory Map 
*/                            
#define EMIOS1_BASEADDR     ((uint32)0xC3FA0000UL)
/** 
* @brief Internal ESCI4
* @details MPC5777C System Memory Map 
*/                            
#define ESCI3_BASEADDR      ((uint32)0xC3FB0000UL)
#define ESCI4_BASEADDR      ((uint32)0xC3FB4000UL)
#define ESCI5_BASEADDR      ((uint32)0xC3FB8000UL)
/** 
* @brief Internal PMC
* @details MPC5777C System Memory Map 
*/         
#define PMC_BASEADDR        ((uint32)0xC3FBC000UL)

/** 
* @brief Internal DSPI_3 (DSPI_D) DSPI_4 (DSPI_E)
* @details MPC5777C System Memory Map 
*/ 
#define DSPI3_BASEADDR      ((uint32)0xC3FDC000UL)
#define DSPI4_BASEADDR      ((uint32)0xC3FE0000UL)
/** 
* @brief Internal PIT
* @details MPC5777C System Memory Map 
*/ 
#define PIT_0_BASEADDR        ((uint32)0xC3FF0000UL)
/** 
* @brief Internal STCU2
* @details MPC5777C System Memory Map 
*/ 
#define STCU_BASEADDR      ((uint32)0xC3FF4000UL)

/** 
* @brief Internal IGF0
* @details MPC5777C System Memory Map 
*/ 
#define IGF0_BASEADDR       ((uint32)0xFFE20000UL)   
/** 
* @brief Internal MCAN0
* @details MPC5777C System Memory Map 
*/      
#define MCAN0_BASEADDR      ((uint32)0xFFE30000UL)
/** 
* @brief Internal PSI5_0
* @details MPC5777C System Memory Map 
*/ 
#define PSI5_0_BASEADDR      ((uint32)0xFFE3C000UL)   
/** 
* @brief Internal SDADC
* @details MPC5777C System Memory Map 
*/     
#define SDADC1_BASEADDR     ((uint32)0xFFE44000UL)
#define SDADC3_BASEADDR     ((uint32)0xFFE48000UL)
/** 
* @brief Internal SRX0
* @details MPC5777C System Memory Map 
*/
#define SRX0_BASEADDR       ((uint32)0xFFE5C000UL)
/** 
* @brief Internal EMIOS0
* @details MPC5777C System Memory Map 
*/
#define EMIOS0_BASEADDR     ((uint32)0xFFE64000UL)
/** 
* @brief Internal CRC
* @details MPC5777C System Memory Map 
*/
#define CRC_BASEADDR        ((uint32)0xFFE68000UL)
/** 
* @brief Internal SIPI
* @details MPC5777C System Memory Map 
*/
#define SIPI_BASEADDR       ((uint32)0xFFE6C000UL)
/** 
* @brief Internal PCS
* @details MPC5777C System Memory Map 
*/
#define PCS_BASEADDR        ((uint32)0xFFE70000UL)
/** 
* @brief Internal PLLDIG
* @details MPC5777C System Memory Map 
*/
#define PLLDIG_BASEADDR     ((uint32)0xFFE74000UL)
/** 
* @brief Internal DTS
* @details MPC5777C System Memory Map 
*/
#define DTS_BASEADDR        ((uint32)0xFFE78000UL)
/** 
* @brief Internal JDC
* @details MPC5777C System Memory Map 
*/
#define JDC_BASEADDR        ((uint32)0xFFE7C000UL)
/** 
* @brief Internal XBAR
* @details MPC5777C System Memory Map 
*/
#define XBAR_0_BASEADDR       ((uint32)0xFFF04000UL)
/** 
* @brief Internal XBIC
* @details MPC5777C System Memory Map 
*/
#define XBIC_BASEADDR       ((uint32)0xFFF08000UL)
/** 
* @brief Internal MPU
* @details MPC5777C System Memory Map 
*/
#define MPU_1_BASEADDR      ((uint32)0xFFF0C000UL)
#define MPU_0_BASEADDR      ((uint32)0xFFF10000UL)
#define MPU_BASEADDR        ((uint32)0xFFF10000UL)

/** 
* @brief Internal CSE
* @details MPC5777C System Memory Map 
*/
#define CSE_BASEADDR        ((uint32)0xFFF14000UL)
/** 
* @brief Internal TDM
* @details MPC5777C System Memory Map 
*/
#define TDM_BASEADDR        ((uint32)0xFFF18000UL)

/** 
* @brief Internal PRAMC
* @details MPC5777C System Memory Map 
*/
#define PRAMC_0_BASEADDR     ((uint32)0xFFF1C000UL)
#define PRAMC_1_BASEADDR     ((uint32)0xFFF20000UL)

/** 
* @brief Internal SEMA4
* @details MPC5777C System Memory Map 
*/
#define SEMA4_BASEADDR      ((uint32)0xFFF24000UL)
/** 
* @brief Internal SWT
* @details MPC5777C System Memory Map 
*/
#define SWT_1_BASEADDR       ((uint32)0xFFF34000UL)
#define SWT_BASEADDR         ((uint32)0xFFF38000UL)
#define SWT_0_BASEADDR       ((uint32)0xFFF38000UL)
/** 
* @brief Internal STM
* @details MPC5777C System Memory Map 
*/
#define STM_0_BASEADDR        ((uint32)0xFFF3C000UL)
/** 
* @brief Internal ECSM
* @details MPC5777C System Memory Map 
*/
#define ECSM_BASEADDR       ((uint32)0xFFF40000UL)
/** 
* @brief Internal DMA_0
* @details MPC5777C System Memory Map 
*/
#define DMA0_BASEADDR     ((uint32)0xFFF44000UL)
/** 
* @brief Internal INTC
* @details MPC5777C System Memory Map 
*/
#define INTC_BASEADDR       ((uint32)0xFFF48000UL)
/** 
* @brief Internal FEC_0
* @details MPC5777C System Memory Map 
*/
#define FEC_0_BASEADDR        ((uint32)0xFFF4C000UL)
/** 
* @brief Internal CCU
* @details MPC5777C System Memory Map 
*/
#define CCU_BASEADDR        ((uint32)0xFFF50000UL)
/** 
* @brief Internal DMA_1
* @details MPC5777C System Memory Map 
*/
#define DMA1_BASEADDR     ((uint32)0xFFF54000UL)
/** 
* @brief Internal ERM
* @details MPC5777C System Memory Map 
*/
#define ERM_BASEADDR        ((uint32)0xFFF60000UL)
/** 
* @brief Internal EIM
* @details MPC5777C System Memory Map 
*/
#define EIM_BASEADDR        ((uint32)0xFFF64000UL)
/** 
* @brief Internal PFLASH
* @details MPC5777C System Memory Map 
*/
#define PFLASH_BASEADDR     ((uint32)0xFFF68000UL)
/** 
* @brief Internal PCM
* @details MPC5777C System Memory Map 
*/
#define PCM_BASEADDR        ((uint32)0xFFF6C000UL)
/** 
* @brief Internal EQADC_0
* @details MPC5777C System Memory Map 
*/
#define EQADC0_BASEADDR     ((uint32)0xFFF80000UL)
/** 
* @brief Internal DECFIL
* @details MPC5777C System Memory Map 
*/
#define DECFIL_A_BASEADDR   ((uint32)0xFFF88000UL)
#define DECFIL_B_BASEADDR   ((uint32)0xFFF88800UL)
#define DECFIL_C_BASEADDR   ((uint32)0xFFF89000UL)
#define DECFIL_D_BASEADDR   ((uint32)0xFFF89800UL)
#define DECFIL_E_BASEADDR   ((uint32)0xFFF8A000UL)
#define DECFIL_F_BASEADDR   ((uint32)0xFFF8A800UL)
#define DECFIL_G_BASEADDR   ((uint32)0xFFF8B000UL)
#define DECFIL_H_BASEADDR   ((uint32)0xFFF8B800UL)
#define DECFIL_I_BASEADDR   ((uint32)0xFFF8C000UL)
#define DECFIL_J_BASEADDR   ((uint32)0xFFF8C800UL)
#define DECFIL_K_BASEADDR   ((uint32)0xFFF8D000UL)
#define DECFIL_L_BASEADDR   ((uint32)0xFFF8D800UL)

/** 
* @brief Internal DSPI
* @details MPC5777C System Memory Map 
*/
#define DSPI0_BASEADDR      ((uint32)0xFFF90000UL)
#define DSPI1_BASEADDR      ((uint32)0xFFF94000UL)
#define DSPI2_BASEADDR      ((uint32)0xFFF98000UL)
          
/** 
* @brief Internal ECSI
* @details MPC5777C System Memory Map 
*/          
#define ESCI0_BASEADDR      ((uint32)0xFFFB0000UL)
#define ESCI1_BASEADDR      ((uint32)0xFFFB4000UL)
#define ESCI2_BASEADDR      ((uint32)0xFFFB8000UL)
/** 
* @brief Internal FLEXCAN
* @details MPC5777C System Memory Map 
*/                   
#define FLEXCAN0_BASEADDR   ((uint32)0xFFFC0000UL)
#define FLEXCAN1_BASEADDR   ((uint32)0xFFFC4000UL)
               
/** 
* @brief Internal LFAST
* @details MPC5777C System Memory Map 
*/               
#define LFAST_BASEADDR      ((uint32)0xFFFD8000UL)
#define LFAST0_BASEADDR     ((uint32)0xFFFD8000UL)
/** 
* @brief Internal FMCR
* @details MPC5777C System Memory Map 
*/                   
#define FMCR_BASEADDR     ((uint32)0xFFFE8000UL)
/** 
* @brief Internal TSENS
* @details MPC5777C System Memory Map 
*/
#define TSENS_BASEADDR      ((uint32)0xFFFEC000UL)
/** 
* @brief Internal PASS
* @details MPC5777C System Memory Map 
*/                   
#define PASS_BASEADDR       ((uint32)0xFFFF4000UL)
/** 
* @brief Internal SSCM
* @details MPC5777C System Memory Map 
*/
#define SSCM_BASEADDR       ((uint32)0xFFFF8000UL)
                   
/**
@brief  Shared CAN Message RAM
@details MPC5777C System Memory Map
*/
#define SCM_RAM_BASEADDR    ((uint32)0xFFE34000UL)
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* #ifndef REG_ESYS_H*/

/** @} */
