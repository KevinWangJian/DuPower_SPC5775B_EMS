/**
*   @file    Mcu_SIU_Types.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Exported data outside of the Mcu from AFE.
*   @details Public data types exported outside of the Mcu driver.
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


#ifndef MCU_SIU_TYPES_H
#define MCU_SIU_TYPES_H


#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_SIU_Types_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
*
* @section Mcu_SIU_Types_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Mcu_SIU_Types_h_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
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
/** @violates @ref Mcu_SIU_Types_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_Cfg.h"
/** @violates @ref Mcu_SIU_Types_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Soc_Ips.h"

#include "Mcu_Reg_eSys_SIU.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_SIU_TYPES_VENDOR_ID                       43
#define MCU_SIU_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define MCU_SIU_TYPES_AR_RELEASE_MINOR_VERSION        0
#define MCU_SIU_TYPES_AR_RELEASE_REVISION_VERSION     3
#define MCU_SIU_TYPES_SW_MAJOR_VERSION                1
#define MCU_SIU_TYPES_SW_MINOR_VERSION                0
#define MCU_SIU_TYPES_SW_PATCH_VERSION                1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Mcu_Cfg header file are from the same vendor */
#if (MCU_SIU_TYPES_VENDOR_ID != MCU_CFG_VENDOR_ID)
    #error "Mcu_SIU_Types.h and Mcu_Cfg.h have different vendor ids"
#endif
/* Check if source file and Mcu_Cfg header file are of the same Autosar version */
#if ((MCU_SIU_TYPES_AR_RELEASE_MAJOR_VERSION != MCU_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_SIU_TYPES_AR_RELEASE_MINOR_VERSION != MCU_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_SIU_TYPES_AR_RELEASE_REVISION_VERSION != MCU_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_SIU_Types.h and Mcu_Cfg.h are different"
#endif
/* Check if source file and Mcu_Cfg header file are of the same Software version */
#if ((MCU_SIU_TYPES_SW_MAJOR_VERSION != MCU_CFG_SW_MAJOR_VERSION) || \
     (MCU_SIU_TYPES_SW_MINOR_VERSION != MCU_CFG_SW_MINOR_VERSION) || \
     (MCU_SIU_TYPES_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SIU_Types.h and Mcu_Cfg.h are different"
#endif

/* Check if source file and Mcu_Reg_eSys_SIU header file are from the same vendor */
#if (MCU_SIU_TYPES_VENDOR_ID != MCU_REG_ESYS_SIU_VENDOR_ID)
    #error "Mcu_SIU_Types.h and Mcu_Reg_eSys_SIU.h have different vendor ids"
#endif
/* Check if source file and Mcu_Reg_eSys_SIU header file are of the same Autosar version */
#if ((MCU_SIU_TYPES_AR_RELEASE_MAJOR_VERSION != MCU_REG_ESYS_SIU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_SIU_TYPES_AR_RELEASE_MINOR_VERSION != MCU_REG_ESYS_SIU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_SIU_TYPES_AR_RELEASE_REVISION_VERSION != MCU_REG_ESYS_SIU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_SIU_Types.h and Mcu_Reg_eSys_SIU.h are different"
#endif
/* Check if source file and Mcu_Reg_eSys_SIU header file are of the same Software version */
#if ((MCU_SIU_TYPES_SW_MAJOR_VERSION != MCU_REG_ESYS_SIU_SW_MAJOR_VERSION) || \
     (MCU_SIU_TYPES_SW_MINOR_VERSION != MCU_REG_ESYS_SIU_SW_MINOR_VERSION) || \
     (MCU_SIU_TYPES_SW_PATCH_VERSION != MCU_REG_ESYS_SIU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SIU_Types.h and Mcu_Reg_eSys_SIU.h are different"
#endif

/* Check if current file and Soc_Ips header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SIU_TYPES_AR_RELEASE_MAJOR_VERSION != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SIU_TYPES_AR_RELEASE_MINOR_VERSION != SOC_IPS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SIU_Types.h and Soc_Ips.h are different"
    #endif
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
/***********************************/
/*            PCS                  */
/***********************************/
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define PCS_SDUR_U32(value)               ((uint32)( (uint32)((value) << PCS_SDUR_SDUR_SHIFT32) & PCS_SDUR_SDUR_MASK32 ))
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define PCS_DIVC_U32(value)              ((uint32)((value) & PCS_DIVC_RWBITS_MASK32))
/* Configuration for PCS_DIVCn[INIT] field register. */
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define PCS_DIVC_INIT_U32(value)         ((uint32)( (uint32)((value) << PCS_DIVC_SHIFT_MASK32) & PCS_DIVC_INIT_MASK32 ))
/* Configuration for PCS_DIVCn[rate] field register. */
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define PCS_DIVC_RATE_U32(value)         ((uint32)((value) & PCS_DIVC_RATE_MASK32))
/* Configuration for PCS_DIVSn[DIVS] field register. */
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define PCS_DIVS_U32(value)              ((uint32)((value) & PCS_DIVS_RATE_MASK32))
/* Configuration for PCS_DIVEn[DIVE] field register. */
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define PCS_DIVE_U32(value)              ((uint32)((value) & PCS_DIVE_RATE_MASK32))


/***********************************/
/*            SIU_SRCR             */
/***********************************/
#define SIU_SRCR_SOFTWARE_SYSTEM_RESET_U32          (SIU_SRCR_SSR_MASK32)
#define SIU_SRCR_SOFTWARE_EXTERNAL_RESET_U32        (SIU_SRCR_SER_MASK32)

/***********************************/
/*            SIU_ECCR             */
/***********************************/
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
    #define MCU_SIU_ECCR_U32(value)                     ((uint32)(((value) & SIU_ECCR_RWBITS_MASK32) | SIU_ECCR_RESBITS_MASK32))

    #define SIU_ECCR_ECCS_SYSTEM_CLOCK_SOURCE_U32       ((uint32)0x00000000U)
    #define SIU_ECCR_ECCS_EXTERNAL_CLOCK_SOURCE_U32     (SIU_ECCR_ECSS_MASK32)
#else

    #define SIU_ECCR_ECCS_SOURCE_PLAT_CLK_U32     ((uint32)0x00000000U)
    #define SIU_ECCR_ECCS_SOURCE_XOSC_U32        (SIU_ECCR_ECCS_MASK32)
#endif /* (IPV_SIU == IPV_SIU_00_02_09_00) */

#define SIU_ECCR_EBTS_ZERO_HOLD_TIMES_U32           ((uint32)0x00000000U)
#define SIU_ECCR_EBTS_NON_ZERO_HOLD_TIMES_U32       ((uint32)SIU_ECCR_EBTS_MASK32)

/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_ECCR_ENGDIV_U32(value)           ((uint32)((uint32)((value) << SIU_ECCR_ENGDIV_SHIFT32) & SIU_ECCR_ENGDIV_MASK32))

/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_ECCR_EBDF_U32(value)                ((uint32)((uint32)((value) << SIU_ECCR_EBDF_SHIFT32) & SIU_ECCR_EBDF_MASK32))

/***********************************/
/*            SIU_SYSDIV           */
/***********************************/
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
    #define MCU_SIU_SYSDIV_U32(value)                   ((uint32)(((value) & SIU_SYSDIV_RWBITS_MASK32) | SIU_SYSDIV_RESBITS_MASK32))
    /** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
    #define MCU_SIU_SYSDIV_IPCLKDIV_U32(value)          ((uint32)((uint32)((value) << SIU_SYSDIV_IPCLKDIV_SHIFT32) & SIU_SYSDIV_IPCLKDIV_MASK32))

    #define SIU_SYSDIV_IPCLKDIV_ENHANCED_U32            ((uint32)0x00000000U)
    #define SIU_SYSDIV_IPCLKDIV_FULL_U32                ((uint32)0x00000001U)
    #define SIU_SYSDIV_IPCLKDIV_LEGACY_U32              ((uint32)0x00000003U)

    #define SIU_SYSDIV_BYPASS_DIS_U32                   ((uint32)0x00000000U)
    #define SIU_SYSDIV_BYPASS_EN_U32                    (SIU_SYSDIV_BYPASS_MASK32)
#else
        
    #define SIU_SYSDIV_PLL0SEL_SOURCE_XOSC_U32          ((uint32)0x00000000U)
    #define SIU_SYSDIV_PLL0SEL_SOURCE_IRC_U32           (SIU_SYSDIV_PLL0SEL_MASK32)

    #define SIU_SYSDIV_PLL1SEL_SOURCE_XOSC_U32          ((uint32)0x00000000U)
    #define SIU_SYSDIV_PLL1SEL_SOURCE_PLL0_PHI1_U32     (SIU_SYSDIV_PLL1SEL_MASK32)

    #define SIU_SYSDIV_PERCLKSEL_SOURCE_SYS_CLK_U32     ((uint32)0x00000000U)
    #define SIU_SYSDIV_PERCLKSEL_SOURCE_PLL0_PHI_U32    (SIU_SYSDIV_PERCLKSEL_MASK32)

    /** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
    #define SIU_SYSDIV_FMPERDIV_U32(value)              ((uint32)((uint32)((value) << SIU_SYSDIV_FMPERDIV_SHIFT32) & SIU_SYSDIV_FMPERDIV_MASK32))

    /** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
    #define SIU_SYSDIV_PERDIV_U32(value)                ((uint32)((uint32)((value) << SIU_SYSDIV_PERDIV_SHIFT32) & SIU_SYSDIV_PERDIV_MASK32))

    #define SIU_SYSDIV_MCANSEL_SOURCE_XOSC_U32          ((uint32)0x00000000U)
    #define SIU_SYSDIV_MCANSEL_SOURCE_PER_CLK_U32       (SIU_SYSDIV_MCANSEL_MASK32)

    #define SIU_SYSDIV_SYSCLKSEL_SOURCE_IRC_U32         ((uint32)0x00000000U)
    #define SIU_SYSDIV_SYSCLKSEL_SOURCE_XOSC_U32        ((uint32)0x00001000U)
    /** @violates @ref Mcu_SIU_Types_h_REF_3 MISRA 2004 Required Rule 1.4 */
    #define SIU_SYSDIV_SYSCLKSEL_SOURCE_PLL1_PHI_U32    ((uint32)0x00002000U)
    /** @violates @ref Mcu_SIU_Types_h_REF_3 MISRA 2004 Required Rule 1.4 */
    #define SIU_SYSDIV_SYSCLKSEL_SOURCE_PLL0_PHI_U32    (SIU_SYSDIV_SYSCLKSEL_MASK32)

    #define SIU_SYSDIV_ETPUDIV_DIVIDE_BY_2_U32          ((uint32)0x00000000U)
    #define SIU_SYSDIV_ETPUDIV_DIVIDE_BY_1_U32          (SIU_SYSDIV_ETPUDIV_MASK32)

    #define SIU_PCSEN_PCS_DISABLED_U32                  ((uint32)0x00000000U)
    #define SIU_PCSEN_PCS_ENABLED_U32                   (SIU_SYSDIV_PCSEN_MASK32)
#endif /*  (IPV_SIU == IPV_SIU_00_02_09_00) */

/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_SYSDIV_SYSCLKDIV_U32(value)             ((uint32)((uint32)((value) << SIU_SYSDIV_SYSCLKDIV_SHIFT32) & SIU_SYSDIV_SYSCLKDIV_MASK32))

#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /***********************************/
    /*            SIU_HLT            */
    /***********************************/
    #define SIU_HLT_CORE_DIS_U32                        ((uint32)0x00000000U)
    #define SIU_HLT_ETPU_DIS_U32                        ((uint32)0x00000000U)
    #define SIU_HLT_NPC_DIS_U32                         ((uint32)0x00000000U)
    #define SIU_HLT_EBI_DIS_U32                         ((uint32)0x00000000U)
    #define SIU_HLT_EQADC_DIS_U32                       ((uint32)0x00000000U)
    #define SIU_HLT_EMIOS_DIS_U32                       ((uint32)0x00000000U)
    #define SIU_HLT_DECFILT_DIS_U32                     ((uint32)0x00000000U)
    #define SIU_HLT_PIT_DIS_U32                         ((uint32)0x00000000U)
    #define SIU_HLT_FLEXCAN_D_DIS_U32                   ((uint32)0x00000000U)
    #define SIU_HLT_FLEXCAN_C_DIS_U32                   ((uint32)0x00000000U)
    #define SIU_HLT_FLEXCAN_B_DIS_U32                   ((uint32)0x00000000U)
    #define SIU_HLT_FLEXCAN_A_DIS_U32                   ((uint32)0x00000000U)
    #define SIU_HLT_DSPI_D_DIS_U32                      ((uint32)0x00000000U)
    #define SIU_HLT_DSPI_C_DIS_U32                      ((uint32)0x00000000U)
    #define SIU_HLT_DSPI_B_DIS_U32                      ((uint32)0x00000000U)
    #define SIU_HLT_DSPI_A_DIS_U32                      ((uint32)0x00000000U)
    #define SIU_HLT_ESCI_C_DIS_U32                      ((uint32)0x00000000U)
    #define SIU_HLT_ESCI_B_DIS_U32                      ((uint32)0x00000000U)
    #define SIU_HLT_ESCI_A_DIS_U32                      ((uint32)0x00000000U)

    #define SIU_HLT_CORE_EN_U32                         (SIU_HLT_CORE_MASK32)
    #define SIU_HLT_ETPU_EN_U32                         (SIU_HLT_ETPU_MASK32)
    #define SIU_HLT_NPC_EN_U32                          (SIU_HLT_NPC_MASK32)
    #define SIU_HLT_EBI_EN_U32                          (SIU_HLT_EBI_MASK32)
    #define SIU_HLT_EQADC_EN_U32                        (SIU_HLT_EQADC_MASK32)
    #define SIU_HLT_EMIOS_EN_U32                        (SIU_HLT_EMIOS_MASK32)
    #define SIU_HLT_DECFILT_EN_U32                      (SIU_HLT_DECFILT_MASK32)
    #define SIU_HLT_PIT_EN_U32                          (SIU_HLT_PIT_MASK32)
    #define SIU_HLT_FLEXCAN_D_EN_U32                    (SIU_HLT_FLEXCAN_D_MASK32)
    #define SIU_HLT_FLEXCAN_C_EN_U32                    (SIU_HLT_FLEXCAN_C_MASK32)
    #define SIU_HLT_FLEXCAN_B_EN_U32                    (SIU_HLT_FLEXCAN_B_MASK32)
    #define SIU_HLT_FLEXCAN_A_EN_U32                    (SIU_HLT_FLEXCAN_A_MASK32)
    #define SIU_HLT_DSPI_D_EN_U32                       (SIU_HLT_DSPI_D_MASK32)
    #define SIU_HLT_DSPI_C_EN_U32                       (SIU_HLT_DSPI_C_MASK32)
    #define SIU_HLT_DSPI_B_EN_U32                       (SIU_HLT_DSPI_B_MASK32)
    #define SIU_HLT_DSPI_A_EN_U32                       (SIU_HLT_DSPI_A_MASK32)
    #define SIU_HLT_ESCI_C_EN_U32                       (SIU_HLT_ESCI_C_MASK32)
    #define SIU_HLT_ESCI_B_EN_U32                       (SIU_HLT_ESCI_B_MASK32)
    #define SIU_HLT_ESCI_A_EN_U32                       (SIU_HLT_ESCI_A_MASK32)
#else
    /***********************************/
    /*            SIU_HLT1             */
    /***********************************/
    #define SIU_HLT1_CORE0_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_CORE1_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_CSE_HALT_DIS_U32             ((uint32)0x00000000U)
    #define SIU_HLT1_ETPUC_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_ETPUA_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_NPC_HALT_DIS_U32             ((uint32)0x00000000U)
    #define SIU_HLT1_EBI_HALT_DIS_U32             ((uint32)0x00000000U)
    #define SIU_HLT1_EQADCB_HALT_DIS_U32          ((uint32)0x00000000U)
    #define SIU_HLT1_EQADCA_HALT_DIS_U32          ((uint32)0x00000000U)
    #define SIU_HLT1_EMIOS0_HALT_DIS_U32          ((uint32)0x00000000U)
    #define SIU_HLT1_DECFIL_HALT_DIS_U32          ((uint32)0x00000000U)
    #define SIU_HLT1_EMIOS1_HALT_DIS_U32          ((uint32)0x00000000U)
    #define SIU_HLT1_PIT_HALT_DIS_U32             ((uint32)0x00000000U)
    #define SIU_HLT1_FLEXCAND_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT1_FLEXCANC_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT1_FLEXCANB_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT1_FLEXCANA_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT1_DSPID_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_DSPIC_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_DSPIB_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_DSPIA_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_DSPIE_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_ESCIF_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_ESCIE_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_ESCID_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_ESCIC_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_ESCIB_HALT_DIS_U32           ((uint32)0x00000000U)
    #define SIU_HLT1_ESCIA_HALT_DIS_U32           ((uint32)0x00000000U)

    #define SIU_HLT1_CORE0_HALT_EN_U32           (SIU_HLT1_CORE0_MASK32)
    #define SIU_HLT1_CORE1_HALT_EN_U32           (SIU_HLT1_CORE1_MASK32)
    #define SIU_HLT1_CSE_HALT_EN_U32             (SIU_HLT1_CSE_MASK32)
    #define SIU_HLT1_ETPUC_HALT_EN_U32           (SIU_HLT1_ETPUC_MASK32)
    #define SIU_HLT1_ETPUA_HALT_EN_U32           (SIU_HLT1_ETPUA_MASK32)
    #define SIU_HLT1_NPC_HALT_EN_U32             (SIU_HLT1_NPC_MASK32)
    #define SIU_HLT1_EBI_HALT_EN_U32             (SIU_HLT1_EBI_MASK32)
    #define SIU_HLT1_EQADCB_HALT_EN_U32          (SIU_HLT1_EQADCB_MASK32)
    #define SIU_HLT1_EQADCA_HALT_EN_U32          (SIU_HLT1_EQADCA_MASK32)
    #define SIU_HLT1_EMIOS0_HALT_EN_U32          (SIU_HLT1_EMIOS0_MASK32)
    #define SIU_HLT1_DECFIL_HALT_EN_U32          (SIU_HLT1_DECFIL_MASK32)
    #define SIU_HLT1_EMIOS1_HALT_EN_U32          (SIU_HLT1_EMIOS1_MASK32)
    #define SIU_HLT1_PIT_HALT_EN_U32             (SIU_HLT1_PIT_MASK32)
    #define SIU_HLT1_FLEXCAND_HALT_EN_U32        (SIU_HLT1_FLEXCAND_MASK32)
    #define SIU_HLT1_FLEXCANC_HALT_EN_U32        (SIU_HLT1_FLEXCANC_MASK32)
    #define SIU_HLT1_FLEXCANB_HALT_EN_U32        (SIU_HLT1_FLEXCANB_MASK32)
    #define SIU_HLT1_FLEXCANA_HALT_EN_U32        (SIU_HLT1_FLEXCANA_MASK32)
    #define SIU_HLT1_DSPID_HALT_EN_U32           (SIU_HLT1_DSPID_MASK32)
    #define SIU_HLT1_DSPIC_HALT_EN_U32           (SIU_HLT1_DSPIC_MASK32)
    #define SIU_HLT1_DSPIB_HALT_EN_U32           (SIU_HLT1_DSPIB_MASK32)
    #define SIU_HLT1_DSPIA_HALT_EN_U32           (SIU_HLT1_DSPIA_MASK32)
    #define SIU_HLT1_DSPIE_HALT_EN_U32           (SIU_HLT1_DSPIE_MASK32)
    #define SIU_HLT1_ESCIF_HALT_EN_U32           (SIU_HLT1_ESCIF_MASK32)
    #define SIU_HLT1_ESCIE_HALT_EN_U32           (SIU_HLT1_ESCIE_MASK32)
    #define SIU_HLT1_ESCID_HALT_EN_U32           (SIU_HLT1_ESCID_MASK32)
    #define SIU_HLT1_ESCIC_HALT_EN_U32           (SIU_HLT1_ESCIC_MASK32)
    #define SIU_HLT1_ESCIB_HALT_EN_U32           (SIU_HLT1_ESCIB_MASK32)
    #define SIU_HLT1_ESCIA_HALT_EN_U32           (SIU_HLT1_ESCIA_MASK32)


    /***********************************/
    /*         SIU_RSTVEC             */
    /***********************************/

    /** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
    #define SIU_RSTVEC_RSTVEC_U32(value)     ((uint32)((value) & SIU_RSTVEC0_RSTVEC_MASK32))

    #define SIU_RSTVEC_RST_ENABLE_U32         (SIU_RSTVEC0_RST_MASK32)
    #define SIU_RSTVEC_RST_DISABLE_U32        (0x00000000U)

    #define SIU_RSTVEC_VLE_BOOK_E_U32         (0x00000000U)
    #define SIU_RSTVEC_VLE_VLE_U32            (SIU_RSTVEC0_VLE_MASK32)

    /***********************************/
    /*            SIU_HLT2             */
    /***********************************/
    #define SIU_HLT2_FEC_HALT_DIS_U32         ((uint32)0x00000000U)
    #define SIU_HLT2_SDD_HALT_DIS_U32         ((uint32)0x00000000U)
    #define SIU_HLT2_SDC_HALT_DIS_U32         ((uint32)0x00000000U)
    #define SIU_HLT2_SDB_HALT_DIS_U32         ((uint32)0x00000000U)
    #define SIU_HLT2_SDA_HALT_DIS_U32         ((uint32)0x00000000U)
    #define SIU_HLT2_SIPI_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT2_CRC_HALT_DIS_U32         ((uint32)0x00000000U)
    #define SIU_HLT2_STCU_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT2_SRX1_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT2_SRX0_HALT_DIS_U32        ((uint32)0x00000000U)
    #define SIU_HLT2_PSI5B_HALT_DIS_U32       ((uint32)0x00000000U)
    #define SIU_HLT2_PSI5A_HALT_DIS_U32       ((uint32)0x00000000U)
    #define SIU_HLT2_MCANB_HALT_DIS_U32       ((uint32)0x00000000U)
    #define SIU_HLT2_MCANA_HALT_DIS_U32       ((uint32)0x00000000U)

    #define SIU_HLT2_FEC_HALT_EN_U32         (SIU_HLT2_FEC_MASK32)
    #define SIU_HLT2_SDD_HALT_EN_U32         (SIU_HLT2_SDD_MASK32)
    #define SIU_HLT2_SDC_HALT_EN_U32         (SIU_HLT2_SDC_MASK32)
    #define SIU_HLT2_SDB_HALT_EN_U32         (SIU_HLT2_SDB_MASK32)
    #define SIU_HLT2_SDA_HALT_EN_U32         (SIU_HLT2_SDA_MASK32)
    #define SIU_HLT2_SIPI_HALT_EN_U32        (SIU_HLT2_SIPI_MASK32)
    #define SIU_HLT2_CRC_HALT_EN_U32         (SIU_HLT2_CRC_MASK32)
    #define SIU_HLT2_STCU_HALT_EN_U32        (SIU_HLT2_STCU_MASK32)
    #define SIU_HLT2_SRX1_HALT_EN_U32        (SIU_HLT2_SRX1_MASK32)
    #define SIU_HLT2_SRX0_HALT_EN_U32        (SIU_HLT2_SRX0_MASK32)
    #define SIU_HLT2_PSI5B_HALT_EN_U32       (SIU_HLT2_PSI5B_MASK32)
    #define SIU_HLT2_PSI5A_HALT_EN_U32       (SIU_HLT2_PSI5A_MASK32)
    #define SIU_HLT2_MCANB_HALT_EN_U32       (SIU_HLT2_MCANB_MASK32)
    #define SIU_HLT2_MCANA_HALT_EN_U32       (SIU_HLT2_MCANA_MASK32)

#endif /* (IPV_SIU == IPV_SIU_00_02_09_00) */

/***********************************/
/*         SIU_SDCLKCFG            */
/***********************************/
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_SDCLKCFG_SDDIV_U32(value)              ((uint32)((value) & SIU_SDCLKCFG_SDDIV_MASK32))

/***********************************/
/*         SIU_LFCLKCFG            */
/***********************************/
#define SIU_LFCLKSEL_SOURCE_XOSC_U32                 ((uint32)0x00000000U)
#define SIU_LFCLKSEL_SOURCE_SIPI_REFCLK_U32          ((uint32)0x00002000U)
#define SIU_LFCLKSEL_SOURCE_PER_CLK_UNDIV_U32        ((uint32)0x00004000U)

/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_LFCLKCFG_LFDDIV_U32(value)              ((uint32)((value) & SIU_LFCLKCFG_LFDIV_MASK32))

/***********************************/
/*         SIU_PSCLKCFG            */
/***********************************/
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_PSCLKCFG_PSDIV_U32(value)           ((uint32)((uint32)((value) << SIU_PSCLKCFG_PSDIV_SHIFT32) & SIU_PSCLKCFG_PSDIV_MASK32))

/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_PSCLKCFG_PSDIV1M_U32(value)         ((uint32)((value) & SIU_PSCLKCFG_PSDIV1M_MASK32))

/********************************/
/*         SIU_RCR             */
/*******************************/
/** @violates @ref Mcu_SIU_Types_h_REF_2 MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define SIU_RCR_RET_U32(value)              ((uint32)((value) & SIU_RCR_RET_MASK32))

/**********************************/
/*         SIU_PCSER              */
/*********************************/
#define SIU_PCSER_PCSE_INTERRUPT_DISABLE_U32        ((uint32)0x00000000U)
#define SIU_PCSER_PCSE_INTERRUPT_ENABLE_U32         (SIU_PCSER_PCSE_MASK32)


/* Mcu_SIU_GetResetRawValue defines */
#define SIU_RAWRESET_SFER_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32) 0U))
#define SIU_RAWRESET_SSRS_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x1U) << (uint32) 0U))
#define SIU_RAWRESET_STCURS_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32) 0U))
#define SIU_RAWRESET_FCCURS_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32) 0U))
#define SIU_RAWRESET_FOSURS_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32) 0U))
#define SIU_RAWRESET_CPURS_MASK32           ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32) 0U))
#define SIU_RAWRESET_ERS_MASK32             ((uint32)(((uint32)0x01 << (uint32)0x6U) << (uint32) 0U))
#define SIU_RAWRESET_PORS_MASK32            ((uint32)(((uint32)0x01 << (uint32)0x7U) << (uint32) 0U))
#define SIU_RAWRESET_WORD_LO_MASK32         ((uint32)0x0000FFFFU)
#define SIU_RAWRESET_WORD_HI_MASK32         ((uint32)0xFFFF0000U)
#define SIU_RAWRESET_SHIFT16_MASK32         ((uint32)0x10U)

#if (IPV_SIU == IPV_SIU_00_02_09_00)
    #define SIU_RAWRESET_SERF_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x0U) << (uint32) 0U))
    #define SIU_RAWRESET_SWTRS_MASK32         ((uint32)(((uint32)0x01 << (uint32)0x2U) << (uint32) 0U))
    #define SIU_RAWRESET_WDRS_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x3U) << (uint32) 0U))
    #define SIU_RAWRESET_LCRS_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x4U) << (uint32) 0U))
    #define SIU_RAWRESET_LLRS_MASK32          ((uint32)(((uint32)0x01 << (uint32)0x5U) << (uint32) 0U))
#endif

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            Reset type to be performed through the Mcu_PerformReset() API.
* @details          Software system reset:
*                       The software system reset is processed as a synchronous reset.
*
*                   Software external Reset:
*                       Used to generate a Software External Reset. Writing 1 to this bit 
*                       asserts RSTOUT for 2480 clock cycles, but the internal reset is not 
*                       asserted. After a software external reset has been initiated, 
*                       RSTOUT negates if this bit is cleared before the 2480 clock cycles 
*                       period expires.
*/
typedef enum
{
    MCU_SOFT_SYSTEM_RESET = 0x5AU,       /**< @brief Software System Reset type. */
    MCU_SOFT_EXTERNAL_RESET = 0x3CU      /**< @brief Destructive Reset type. */
    
} Mcu_SIU_ResetType;

#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

/**
* @brief            Power Modes encoding.
* @details          Supported power modes for SIU IP.
*/
typedef enum
{
#if (MCU_ENTER_LOW_POWER_MODE == STD_ON)
    MCU_WAIT_MODE,   /**< @brief WAIT Mode. */
#endif /* (MCU_ENTER_LOW_POWER_MODE == STD_ON) */
    MCU_HALT_MODE    /**< @brief HALT Mode. */

} Mcu_PowerModeType;


#if ((MCU_GET_PERIPH_STATE_API == STD_ON) || (defined MCU_GET_INTERNAL_STATE))
/**
* @brief            List of peripherals that can be interogated for state: frozen/active.
* @details          Result is reported from ME_PS0..3 registers.
*/
typedef enum
{
    S_ESCI_A = 0U,
    S_ESCI_B = 1U,
    S_ESCI_C = 2U,
    S_DSPI_A = 8U,
    S_DSPI_B = 9U,
    S_DSPI_C = 10U,
    S_DSPI_D = 11U,
    S_FLEXCAN_A = 12U,
    S_FLEXCAN_B = 13U,
    S_FLEXCAN_C = 14U,
    S_FLEXCAN_D = 15U,
    S_PIT = 18U,
    S_DECFILT = 20U,
    S_EMIOS = 21U,
    S_EQADC = 23U,
    S_EBI = 24U,
    S_NPC = 25U,
    S_ETPU = 26U

} Mcu_PeripheralId;

#endif /* (MCU_GET_PERIPH_STATE_API == STD_ON) */

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            MIDR configuration
*
*/
typedef struct
{
    VAR(uint32, AUTOMATIC) u32Midr;   /**< @brief SIU_MIDR1 Configuration register. */
} Mcu_MidrReturnType;


/**
* @brief            Definition of a MCU mode section in the configuration structure.
* @details          Specifies the system behaviour during the selected target mode.
*                   Data set and configured by Mcu_SetMode call.
*/
typedef struct
{
    /**< @brief The ID for Power Mode configuration. */
    VAR( Mcu_ModeType, MCU_VAR) Mcu_ModeConfigId;
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /**< @brief The register value for SIU_HLT. */
    VAR( uint32, MCU_VAR) Mcu_HaltRegisterValue;
#else
    /**< @brief The register value for SIU_HLT1. */
    VAR( uint32, MCU_VAR) Mcu_Core0ResetVectorRegisterValue;
    /**< @brief The register value for SIU_HLT1. */
    VAR( uint32, MCU_VAR) Mcu_Core1ResetVectorRegisterValue;
    /**< @brief The register value for SIU_HLT1. */
    VAR( uint32, MCU_VAR) Mcu_Halt1RegisterValue;
    /**< @brief The register value for SIU_HLT2. */
    VAR( uint32, MCU_VAR) Mcu_Halt2RegisterValue;    
#endif
} Mcu_ModeConfigType;

/**
* @brief            Configuration of SIU_RCR.
* @details          This data configuration is set at module initialization phase.
*/
typedef struct
{
#if (MCU_PERFORM_RESET_API == STD_ON)
    /**< @brief RESET type: MCU_SOFTWARE_SYSTEM_RESET vs MCU_SOFTWARE_EXTERNAL_RESET. Used by McuPerformReset() API. */
    VAR( Mcu_SIU_ResetType, MCU_VAR) Mcu_eResetType;
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

    /* Reset Escalation Threshold */
    /**< @brief Reset Escalation Threshold. SIU_RCR */
    VAR( uint32, MCU_VAR) u8ThresholdReset;

} Mcu_SIU_ResetConfigType;

#if (MCU_INIT_CLOCK == STD_ON)


/**
* @brief       PCS and SIU addr and value pair.
* @details     this structure is used to represent a pair of addr and data to be written to hardware
*/
typedef struct
{
   VAR( uint32, MCU_VAR) u32RegisterAddr; /* register addr, added by hand in the code template */
   VAR( uint32, MCU_VAR) u32RegisterData; /* generated value, as it iss already defined */

} Mcu_SIU_RegisterConfigType;


/**
* @brief   SIU IP configuration.
* @details This structure contains information for IRCOSC, XOSC, PLL, Output Clocks
*          The definitions for each Clock setting within the structure Mcu_ConfigType shall contain:
*          - MCU specific properties as, e.g., clock safety features and special clock distribution
*            settings
*          - PLL settings /start lock options
*          - Internal oscillator setting
*/
typedef struct
{
    /**< @brief system clock config SIU_SYSDIV */
    VAR (uint32, MCU_VAR) u32SystemClockConfig;
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /**< @brief external clock config SIU_ECCR */
    VAR (uint32, MCU_VAR) u32ExternalClockConfig;
#else
    /**< @brief Configuration for Progressive Clock Switching (PCS_SDUR[SDUR]). */
    VAR (uint32, MCU_VAR) u32ProgClkSwitch;
    /**< @brief number of prog. sw. registers unde mcu control */
    VAR (uint8, MCU_VAR) u8NoOfProgSwitchUnderMcuControl;
    /**< @brief progressive clock switch */
    CONST( Mcu_SIU_RegisterConfigType, MCU_CONST) (*apPcsClockConfig)[];
    /**< @brief number of aux clock regs under mcu control */
    VAR (uint8, MCU_VAR)  u8NoAuxClockUnderMcuControl;
    /**< @brief configuration for SIU_ECCR, SIU_SDCLKCFG, SIU_LFCLKCFG, SIU_PSCLKCFG */
    CONST( Mcu_SIU_RegisterConfigType, MCU_CONST) (*apAuxClockConfig)[];
#endif
} Mcu_SIU_ClockConfigType;


#endif /* (MCU_INIT_CLOCK == STD_ON) */

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* MCU_SIU_TYPES_H */

/** @} */
