/**
*   @file    Mcu_Reg_eSys_SIU.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Macros for memory access.
*   @details Macros/Defines used for registry and memory read/write.
*
*   @addtogroup MCU
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : M4_SRC_FAMILY
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

#ifndef MCU_REG_ESYS_SIU_H
#define MCU_REG_ESYS_SIU_H


#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_Reg_eSys_SIU_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_Reg_eSys_SIU_h_REF_2
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/** @violates @ref Mcu_Reg_eSys_SIU_h_REF_1 Repeated include files.*/
#include "Reg_eSys.h"

/** @violates @ref Reg_eSys_PMC_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files.*/
#include "Mcu_SIU_IPVersion.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/** @violates @ref Mcu_Reg_eSys_SIU_h_REF_2 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIU_VENDOR_ID                       43
/** @violates @ref Mcu_Reg_eSys_SIU_h_REF_2 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIU_AR_RELEASE_MAJOR_VERSION        4
/** @violates @ref Mcu_Reg_eSys_SIU_h_REF_2 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIU_AR_RELEASE_MINOR_VERSION        0
/** @violates @ref Mcu_Reg_eSys_SIU_h_REF_2 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIU_AR_RELEASE_REVISION_VERSION     3
/** @violates @ref Mcu_Reg_eSys_SIU_h_REF_2 Violates MISRA 2004 Required Rule 1.4 */
#define MCU_REG_ESYS_SIU_SW_MAJOR_VERSION                1
#define MCU_REG_ESYS_SIU_SW_MINOR_VERSION                0
#define MCU_REG_ESYS_SIU_SW_PATCH_VERSION                1


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Reg_eSys header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_REG_ESYS_SIU_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_REG_ESYS_SIU_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_Reg_eSys_SIU.h and Reg_eSys.h are different"
    #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/* PCS Switch Duration Register */
#define PCS_SDUR_ADDR32               ((uint32)( PCS_BASEADDR + 0x00000700U ))
/* PCS Divider Change Register for XOSC */
#define PCS_DIVC1_ADDR32              ((uint32)( PCS_BASEADDR + 0x00000704U ))
/* PCS Divider End Register for XOSC */
#define PCS_DIVE1_ADDR32              ((uint32)( PCS_BASEADDR + 0x00000708U ))
/* PCS Divider Start Register for XOSC */
#define PCS_DIVS1_ADDR32              ((uint32)( PCS_BASEADDR + 0x0000070CU ))
/* PCS Divider Change Register for PLL1 */
#define PCS_DIVC2_ADDR32              ((uint32)( PCS_BASEADDR + 0x00000710U ))
/* PCS Divider End Register for PLL1 */
#define PCS_DIVE2_ADDR32              ((uint32)( PCS_BASEADDR + 0x00000714U ))
/* PCS Divider Start Register for PLL1 */
#define PCS_DIVS2_ADDR32              ((uint32)( PCS_BASEADDR + 0x00000718U ))
/* PCS Divider Change Register for PLL0 */
#define PCS_DIVC3_ADDR32              ((uint32)( PCS_BASEADDR + 0x0000071CU ))
/* PCS Divider End Register for PLL0 */
#define PCS_DIVE3_ADDR32              ((uint32)( PCS_BASEADDR + 0x00000720U ))
/* PCS Divider Start Register for PLL0 */
#define PCS_DIVS3_ADDR32              ((uint32)( PCS_BASEADDR + 0x00000724U ))

/* MCU Identification Register */
#define SIU_MIDR_ADDR32               ((uint32)( SIU_BASEADDR + 0x00000004U ))
/* Reset Status Register */
#define SIU_RSR_ADDR32                ((uint32)( SIU_BASEADDR + 0x0000000CU ))
/* System Reset Control Register */
#define SIU_SRCR_ADDR32               ((uint32)( SIU_BASEADDR + 0x00000010U ))
/* External Clock Control Register */
#define SIU_ECCR_ADDR32               ((uint32)( SIU_BASEADDR + 0x00000984U ))
/* System Clock Register */
#define SIU_SYSDIV_ADDR32             ((uint32)( SIU_BASEADDR + 0x000009A0U ))

#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /* Halt Register 1 */
    #define SIU_HLT_ADDR32               ((uint32)( SIU_BASEADDR + 0x000009A4U ))
    /* Halt Acknowledge Register 1 */
    #define SIU_HLTACK_ADDR32            ((uint32)( SIU_BASEADDR + 0x000009A8U ))
#else
    /* Halt Register 1 */
    #define SIU_HLT1_ADDR32               ((uint32)( SIU_BASEADDR + 0x000009A4U ))
    /* Halt Acknowledge Register 1 */
    #define SIU_HLTACK1_ADDR32            ((uint32)( SIU_BASEADDR + 0x000009A8U ))
    /* Core0 Reset Vector Register */
    #define SIU_RSTVEC0_ADDR32            ((uint32)( SIU_BASEADDR + 0x000009ACU ))
    /* Core1 Reset Vector Register */
    #define SIU_RSTVEC1_ADDR32            ((uint32)( SIU_BASEADDR + 0x000009B0U ))
    /* Halt Register 2 */
    #define SIU_HLT2_ADDR32               ((uint32)( SIU_BASEADDR + 0x000009BCU ))
    /* Halt Acknowledge Register 2 */
    #define SIU_HLTACK2_ADDR32            ((uint32)( SIU_BASEADDR + 0x000009C0U ))
#endif

/* Sigma-Delta Clock Configuration Register */
#define SIU_SDCLKCFG_ADDR32           ((uint32)( SIU_BASEADDR + 0x000009C4U ))
/* LFAST Clock Configuration Register */
#define SIU_LFCLKCFG_ADDR32           ((uint32)( SIU_BASEADDR + 0x000009C8U ))
/* PSI5 Clock Configuration Register */
#define SIU_PSCLKCFG_ADDR32           ((uint32)( SIU_BASEADDR + 0x000009CCU ))
/* Reset Configuration Register */
#define SIU_RCR_ADDR32                ((uint32)( SIU_BASEADDR + 0x000009D0U ))
/* Progressive Clock Switch Interrupt Enable Register */
#define SIU_PCSER_ADDR32              ((uint32)( SIU_BASEADDR + 0x000009D8U ))
/* Progressive Clock Switch Interrupt Flag Register */
#define SIU_PCSIFR_ADDR32             ((uint32)( SIU_BASEADDR + 0x000009DCU ))

/***********************************/
/*            PCS                  */
/***********************************/
#define PCS_DIVC_RWBITS_MASK32               ((uint32)0xFFFF00FFU)
#define PCS_DIVC_RESBITS_MASK32              ((uint32)0x00000000U)
#define PCS_DIVS_RWBITS_MASK32               ((uint32)0x000FFFFFU)
#define PCS_DIVS_RESBITS_MASK32              ((uint32)0x00000000U)
#define PCS_DIVE_RWBITS_MASK32               ((uint32)0x000FFFFFU)
#define PCS_DIVE_RESBITS_MASK32              ((uint32)0x00000000U)

#define PCS_SDUR_SDUR_MASK32                 ((uint32)0xFF000000U)
#define PCS_SDUR_SDUR_SHIFT32                ((uint32)0x00000018U)

/* PCS_DIVCn[INIT] field mask. */
#define PCS_DIVC_INIT_MASK32                ((uint32)0xFFFF0000U)
#define PCS_DIVC_SHIFT_MASK32               ((uint32)0x00000010U)

/* PCS_DIVCn[RATE] field mask. */
#define PCS_DIVC_RATE_MASK32                ((uint32)0x000000FFU)

/* MC_CGM_DIVSn[DIVS] field mask. */
#define PCS_DIVS_RATE_MASK32                 ((uint32)0x000FFFFFU)

/* MC_CGM_DIVEn[DIVE] field mask. */
#define PCS_DIVE_RATE_MASK32                ((uint32)0x000FFFFFU)

/***********************************/
/*            SIU_RSR              */
/***********************************/
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    #define SIU_RSR_RESET_STATUS_MASK32 ((uint32)0xFA030000U)
    #define SIU_RSR_RWBITS_MASK32       ((uint32)0x00010000U)

    #define SIU_RSR_PORS_MASK32         ((uint32)0x80000000U)
    #define SIU_RSR_ERS_MASK32          ((uint32)0x40000000U)
    #define SIU_RSR_LLRS_MASK32         ((uint32)0x20000000U)
    #define SIU_RSR_LCRS_MASK32         ((uint32)0x10000000U)
    #define SIU_RSR_WDRS_MASK32         ((uint32)0x08000000U)
    #define SIU_RSR_SWTRS_MASK32        ((uint32)0x02000000U)
    #define SIU_RSR_SSRS_MASK32         ((uint32)0x00020000U)
    #define SIU_RSR_SERF_MASK32         ((uint32)0x00010000U)
#else
    #define SIU_RSR_RESET_STATUS_MASK32 ((uint32)0xC05F0000U)
    #define SIU_RSR_RWBITS_MASK32       ((uint32)0x00010000U)

    #define SIU_RSR_PORS_MASK32         ((uint32)0x80000000U)
    #define SIU_RSR_ERS_MASK32          ((uint32)0x40000000U)
    #define SIU_RSR_CPURS_MASK32        ((uint32)0x00400000U)
    #define SIU_RSR_FOSURS_MASK32       ((uint32)0x00100000U)
    #define SIU_RSR_FCCURS_MASK32       ((uint32)0x00080000U)
    #define SIU_RSR_STCURS_MASK32       ((uint32)0x00040000U)
    #define SIU_RSR_SSRS_MASK32         ((uint32)0x00020000U)
    #define SIU_RSR_SERF_MASK32         ((uint32)0x00010000U)
#endif /* (IPV_SIU == IPV_SIU_00_02_09_00) */


/***********************************/
/*            SIU_SRCR             */
/***********************************/
#define SIU_SRCR_SSR_MASK32          ((uint32)0x80000000U)
#define SIU_SRCR_SER_MASK32          ((uint32)0x40000000U)


/***********************************/
/*            SIU_ECCR             */
/***********************************/
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    #define SIU_ECCR_RWBITS_MASK32       ((uint32)0x0000FF8BU)
    #define SIU_ECCR_RESBITS_MASK32      ((uint32)0x00000000U)
#endif
#define SIU_ECCR_ENGDIV_MASK32       ((uint32)0x0000FF00U)
#define SIU_ECCR_ENGDIV_SHIFT32      ((uint32)0x00000008U)
#define SIU_ECCR_ECCS_MASK32         ((uint32)0x00000080U)
#define SIU_ECCR_ECSS_MASK32         ((uint32)0x00000080U)
#define SIU_ECCR_EBTS_MASK32         ((uint32)0x00000008U)
#define SIU_ECCR_EBDF_MASK32         ((uint32)0x00000003U)
#define SIU_ECCR_ENGDIV_SHIFT32      ((uint32)0x00000008U)
#define SIU_ECCR_EBDF_SHIFT32        ((uint32)0x00000000U)

#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /***********************************/
    /*            SIU_SYSDIV           */
    /***********************************/
    #define SIU_SYSDIV_RWBITS_MASK32            ((uint32)0x0000031CU)
    #define SIU_SYSDIV_RESBITS_MASK32           ((uint32)0x00000000U)

    #define SIU_SYSDIV_IPCLKDIV_MASK32          ((uint32)0x00000300U)
    #define SIU_SYSDIV_BYPASS_MASK32            ((uint32)0x00000010U)
    #define SIU_SYSDIV_SYSCLKDIV_MASK32         ((uint32)0x0000000CU)
    #define SIU_SYSDIV_IPCLKDIV_SHIFT32         ((uint32)0x00000008U)
    #define SIU_SYSDIV_SYSCLKDIV_SHIFT32        ((uint32)0x00000002U)

    /***********************************/
    /*            SIU_HLT              */
    /***********************************/
    #define SIU_HLT_RWBITS_MASK32               ((uint32)0x87B4FF07U)
    #define SIU_HLT_RESBITS_MASK32              ((uint32)0x00000000U)

    #define SIU_HLT_CORE_MASK32                 ((uint32)0x80000000U)
    #define SIU_HLT_PERIPHERAL_MASK32           ((uint32)0x07B4FF07U)
    #define SIU_HLT_ETPU_MASK32                 ((uint32)0x04000000U)
    #define SIU_HLT_NPC_MASK32                  ((uint32)0x02000000U)
    #define SIU_HLT_EBI_MASK32                  ((uint32)0x01000000U)
    #define SIU_HLT_EQADC_MASK32                ((uint32)0x00800000U)
    #define SIU_HLT_EMIOS_MASK32                ((uint32)0x00200000U)
    #define SIU_HLT_DECFILT_MASK32              ((uint32)0x00100000U)
    #define SIU_HLT_PIT_MASK32                  ((uint32)0x00040000U)
    #define SIU_HLT_FLEXCAN_D_MASK32            ((uint32)0x00008000U)
    #define SIU_HLT_FLEXCAN_C_MASK32            ((uint32)0x00004000U)
    #define SIU_HLT_FLEXCAN_B_MASK32            ((uint32)0x00002000U)
    #define SIU_HLT_FLEXCAN_A_MASK32            ((uint32)0x00001000U)
    #define SIU_HLT_DSPI_D_MASK32               ((uint32)0x00000800U)
    #define SIU_HLT_DSPI_C_MASK32               ((uint32)0x00000400U)
    #define SIU_HLT_DSPI_B_MASK32               ((uint32)0x00000200U)
    #define SIU_HLT_DSPI_A_MASK32               ((uint32)0x00000100U)
    #define SIU_HLT_ESCI_C_MASK32               ((uint32)0x00000004U)
    #define SIU_HLT_ESCI_B_MASK32               ((uint32)0x00000002U)
    #define SIU_HLT_ESCI_A_MASK32               ((uint32)0x00000001U)

    /***********************************/
    /*            SIU_HLTACK           */
    /***********************************/
    #define SIU_HLT_RWBITS_MASK32               ((uint32)0x87B4FF07U)
    #define SIU_HLT_RESBITS_MASK32              ((uint32)0x00000000U)

    #define SIU_HLTACK_CORE_MASK32              ((uint32)0x80000000U)
    #define SIU_HLTACK_PERIPHERAL_MASK32        ((uint32)0x07B4FF07U)
    #define SIU_HLTACK_ETPU_MASK32              ((uint32)0x04000000U)
    #define SIU_HLTACK_NPC_MASK32               ((uint32)0x02000000U)
    #define SIU_HLTACK_EBI_MASK32               ((uint32)0x01000000U)
    #define SIU_HLTACK_EQADC_MASK32             ((uint32)0x00800000U)
    #define SIU_HLTACK_EMIOS_MASK32             ((uint32)0x00200000U)
    #define SIU_HLTACK_DECFILT_MASK32           ((uint32)0x00100000U)
    #define SIU_HLTACK_PIT_MASK32               ((uint32)0x00040000U)
    #define SIU_HLTACK_FLEXCAN_D_MASK32         ((uint32)0x00008000U)
    #define SIU_HLTACK_FLEXCAN_C_MASK32         ((uint32)0x00004000U)
    #define SIU_HLTACK_FLEXCAN_B_MASK32         ((uint32)0x00002000U)
    #define SIU_HLTACK_FLEXCAN_A_MASK32         ((uint32)0x00001000U)
    #define SIU_HLTACK_DSPI_D_MASK32            ((uint32)0x00000800U)
    #define SIU_HLTACK_DSPI_C_MASK32            ((uint32)0x00000400U)
    #define SIU_HLTACK_DSPI_B_MASK32            ((uint32)0x00000200U)
    #define SIU_HLTACK_DSPI_A_MASK32            ((uint32)0x00000100U)
    #define SIU_HLTACK_ESCI_C_MASK32            ((uint32)0x00000004U)
    #define SIU_HLTACK_ESCI_B_MASK32            ((uint32)0x00000002U)
    #define SIU_HLTACK_ESCI_A_MASK32            ((uint32)0x00000001U)
#else
    /***********************************/
    /*            SIU_SYSDIV           */
    /***********************************/
    #define SIU_SYSDIV_LCK_MASK32           ((uint32)0x80000000U)
    #define SIU_SYSDIV_PLL0SEL_MASK32       ((uint32)0x10000000U)
    #define SIU_SYSDIV_PLL1SEL_MASK32       ((uint32)0x04000000U)
    #define SIU_SYSDIV_PERCLKSEL_MASK32     ((uint32)0x01000000U)
    #define SIU_SYSDIV_FMPERDIV_MASK32      ((uint32)0x00300000U)
    #define SIU_SYSDIV_FMPERDIV_SHIFT32     ((uint32)0x00000014U)
    #define SIU_SYSDIV_PERDIV_MASK32        ((uint32)0x00030000U)
    #define SIU_SYSDIV_PERDIV_SHIFT32       ((uint32)0x00000010U)
    #define SIU_SYSDIV_MCANSEL_MASK32       ((uint32)0x00008000U)
    #define SIU_SYSDIV_SYSCLKSEL_MASK32     ((uint32)0x00003000U)
    #define SIU_SYSDIV_SYSCLKSEL_SHIFT32    ((uint32)0x0000000CU)
    #define SIU_SYSDIV_ETPUDIV_MASK32       ((uint32)0x00000100U)
    #define SIU_SYSDIV_SYSCLKDIV_MASK32     ((uint32)0x0000001CU)
    #define SIU_SYSDIV_SYSCLKDIV_SHIFT32    ((uint32)0x00000002U)
    #define SIU_SYSDIV_PCSEN_MASK32         ((uint32)0x00000001U)

    /***********************************/
    /*            SIU_HLT1             */
    /***********************************/
    #define SIU_HLT1_CORE0_MASK32           ((uint32)0x80000000U)
    #define SIU_HLT1_CORE1_MASK32           ((uint32)0x40000000U)
    #define SIU_HLT1_CSE_MASK32             ((uint32)0x10000000U)
    #define SIU_HLT1_ETPUC_MASK32           ((uint32)0x08000000U)
    #define SIU_HLT1_ETPUA_MASK32           ((uint32)0x04000000U)
    #define SIU_HLT1_NPC_MASK32             ((uint32)0x02000000U)
    #define SIU_HLT1_EBI_MASK32             ((uint32)0x01000000U)
    #define SIU_HLT1_EQADCB_MASK32          ((uint32)0x00800000U)
    #define SIU_HLT1_EQADCA_MASK32          ((uint32)0x00400000U)
    #define SIU_HLT1_EMIOS0_MASK32          ((uint32)0x00200000U)
    #define SIU_HLT1_DECFIL_MASK32          ((uint32)0x00100000U)
    #define SIU_HLT1_EMIOS1_MASK32          ((uint32)0x00080000U)
    #define SIU_HLT1_PIT_MASK32             ((uint32)0x00040000U)
    #define SIU_HLT1_FLEXCAND_MASK32        ((uint32)0x00008000U)
    #define SIU_HLT1_FLEXCANC_MASK32        ((uint32)0x00004000U)
    #define SIU_HLT1_FLEXCANB_MASK32        ((uint32)0x00002000U)
    #define SIU_HLT1_FLEXCANA_MASK32        ((uint32)0x00001000U)
    #define SIU_HLT1_DSPID_MASK32           ((uint32)0x00000800U)
    #define SIU_HLT1_DSPIC_MASK32           ((uint32)0x00000400U)
    #define SIU_HLT1_DSPIB_MASK32           ((uint32)0x00000200U)
    #define SIU_HLT1_DSPIA_MASK32           ((uint32)0x00000100U)
    #define SIU_HLT1_DSPIE_MASK32           ((uint32)0x00000080U)
    #define SIU_HLT1_ESCIF_MASK32           ((uint32)0x00000020U)
    #define SIU_HLT1_ESCIE_MASK32           ((uint32)0x00000010U)
    #define SIU_HLT1_ESCID_MASK32           ((uint32)0x00000008U)
    #define SIU_HLT1_ESCIC_MASK32           ((uint32)0x00000004U)
    #define SIU_HLT1_ESCIB_MASK32           ((uint32)0x00000002U)
    #define SIU_HLT1_ESCIA_MASK32           ((uint32)0x00000001U)

    /***********************************/
    /*            SIU_HLTACK1          */
    /***********************************/
    #define SIU_HLTACK1_CORE0_MASK32           ((uint32)0x80000000U)
    #define SIU_HLTACK1_CORE1_MASK32           ((uint32)0x40000000U)
    #define SIU_HLTACK1_CSE_MASK32             ((uint32)0x10000000U)
    #define SIU_HLTACK1_ETPUC_MASK32           ((uint32)0x08000000U)
    #define SIU_HLTACK1_ETPUA_MASK32           ((uint32)0x04000000U)
    #define SIU_HLTACK1_NPC_MASK32             ((uint32)0x02000000U)
    #define SIU_HLTACK1_EBI_MASK32             ((uint32)0x01000000U)
    #define SIU_HLTACK1_EQADCB_MASK32          ((uint32)0x00800000U)
    #define SIU_HLTACK1_EQADCA_MASK32          ((uint32)0x00400000U)
    #define SIU_HLTACK1_EMIOS0_MASK32          ((uint32)0x00200000U)
    #define SIU_HLTACK1_DECFIL_MASK32          ((uint32)0x00100000U)
    #define SIU_HLTACK1_EMIOS1_MASK32          ((uint32)0x00080000U)
    #define SIU_HLTACK1_PIT_MASK32             ((uint32)0x00040000U)
    #define SIU_HLTACK1_FLEXCAND_MASK32        ((uint32)0x00008000U)
    #define SIU_HLTACK1_FLEXCANC_MASK32        ((uint32)0x00004000U)
    #define SIU_HLTACK1_FLEXCANB_MASK32        ((uint32)0x00002000U)
    #define SIU_HLTACK1_FLEXCANA_MASK32        ((uint32)0x00001000U)
    #define SIU_HLTACK1_DSPID_MASK32           ((uint32)0x00000800U)
    #define SIU_HLTACK1_DSPIC_MASK32           ((uint32)0x00000400U)
    #define SIU_HLTACK1_DSPIB_MASK32           ((uint32)0x00000200U)
    #define SIU_HLTACK1_DSPIA_MASK32           ((uint32)0x00000100U)
    #define SIU_HLTACK1_DSPIE_MASK32           ((uint32)0x00000080U)
    #define SIU_HLTACK1_ESCIF_MASK32           ((uint32)0x00000020U)
    #define SIU_HLTACK1_ESCIE_MASK32           ((uint32)0x00000010U)
    #define SIU_HLTACK1_ESCID_MASK32           ((uint32)0x00000008U)
    #define SIU_HLTACK1_ESCIC_MASK32           ((uint32)0x00000004U)
    #define SIU_HLTACK1_ESCIB_MASK32           ((uint32)0x00000002U)
    #define SIU_HLTACK1_ESCIA_MASK32           ((uint32)0x00000001U)

    /***********************************/
    /*         SIU_RSTVEC0             */
    /***********************************/
    #define SIU_RSTVEC0_RSTVEC_MASK32           ((uint32)0xFFFFFFFCU)
    #define SIU_RSTVEC0_RSTVEC_SHIFT32          ((uint32)0x00000002U)
    #define SIU_RSTVEC0_RST_MASK32              ((uint32)0x00000002U)
    #define SIU_RSTVEC0_VLE_MASK32              ((uint32)0x00000001U)

    /***********************************/
    /*         SIU_RSTVEC1             */
    /***********************************/
    #define SIU_RSTVEC1_RSTVEC_MASK32           ((uint32)0xFFFFFFFCU)
    #define SIU_RSTVEC1_RSTVEC_SHIFT32          ((uint32)0x00000002U)
    #define SIU_RSTVEC1_RST_MASK32              ((uint32)0x00000002U)
    #define SIU_RSTVEC1_VLE_MASK32              ((uint32)0x00000001U)

    /***********************************/
    /*            SIU_HLT2             */
    /***********************************/
    #define SIU_HLT2_FEC_MASK32         ((uint32)0x80000000U)
    #define SIU_HLT2_SDD_MASK32         ((uint32)0x00080000U)
    #define SIU_HLT2_SDC_MASK32         ((uint32)0x00040000U)
    #define SIU_HLT2_SDB_MASK32         ((uint32)0x00020000U)
    #define SIU_HLT2_SDA_MASK32         ((uint32)0x00010000U)
    #define SIU_HLT2_SIPI_MASK32        ((uint32)0x00008000U)
    #define SIU_HLT2_CRC_MASK32         ((uint32)0x00004000U)
    #define SIU_HLT2_STCU_MASK32        ((uint32)0x00002000U)
    #define SIU_HLT2_SRX1_MASK32        ((uint32)0x00000200U)
    #define SIU_HLT2_SRX0_MASK32        ((uint32)0x00000100U)
    #define SIU_HLT2_PSI5B_MASK32       ((uint32)0x00000020U)
    #define SIU_HLT2_PSI5A_MASK32       ((uint32)0x00000010U)
    #define SIU_HLT2_MCANB_MASK32       ((uint32)0x00000002U)
    #define SIU_HLT2_MCANA_MASK32       ((uint32)0x00000001U)

    /***********************************/
    /*            SIU_HLTACK2             */
    /***********************************/
    #define SIU_HLTACK2_FEC_MASK32         ((uint32)0x80000000U)
    #define SIU_HLTACK2_SDD_MASK32         ((uint32)0x00080000U)
    #define SIU_HLTACK2_SDC_MASK32         ((uint32)0x00040000U)
    #define SIU_HLTACK2_SDB_MASK32         ((uint32)0x00020000U)
    #define SIU_HLTACK2_SDA_MASK32         ((uint32)0x00010000U)
    #define SIU_HLTACK2_SIPI_MASK32        ((uint32)0x00008000U)
    #define SIU_HLTACK2_CRC_MASK32         ((uint32)0x00004000U)
    #define SIU_HLTACK2_STCU_MASK32        ((uint32)0x00002000U)
    #define SIU_HLTACK2_SRX1_MASK32        ((uint32)0x00000200U)
    #define SIU_HLTACK2_SRX0_MASK32        ((uint32)0x00000100U)
    #define SIU_HLTACK2_PSI5B_MASK32       ((uint32)0x00000020U)
    #define SIU_HLTACK2_PSI5A_MASK32       ((uint32)0x00000010U)
    #define SIU_HLTACK2_MCANB_MASK32       ((uint32)0x00000002U)
    #define SIU_HLTACK2_MCANA_MASK32       ((uint32)0x00000001U)
#endif /* (IPV_SIU == IPV_SIU_00_02_09_00) */

/***********************************/
/*         SIU_SDCLKCFG            */
/***********************************/
#define SIU_SDCLKCFG_LCK_MASK32              ((uint32)0x80000000U)
#define SIU_SDCLKCFG_SDDIV_MASK32            ((uint32)0x0000007FU)

/***********************************/
/*         SIU_LFCLKCFG            */
/***********************************/
#define SIU_LFCLKCFG_LCK_MASK32              ((uint32)0x80000000U)
#define SIU_LFCLKCFG_LFCLKSEL_MASK32         ((uint32)0x00003000U)
#define SIU_LFCLKCFG_LFCLKSEL_SHIFT32        ((uint32)0x0000000CU)
#define SIU_LFCLKCFG_LFDIV_MASK32            ((uint32)0x0000007FU)

/***********************************/
/*         SIU_PSCLKCFG            */
/***********************************/
#define SIU_PSCLKCFG_LCK_MASK32             ((uint32)0x80000000U)
#define SIU_PSCLKCFG_PSDIV_MASK32           ((uint32)0x00FF0000U)
#define SIU_PSCLKCFG_PSDIV_SHIFT32          ((uint32)0x00000010U)
#define SIU_PSCLKCFG_PSDIV1M_MASK32         ((uint32)0x000003FFU)

/********************************/
/*         SIU_RCR             */
/*******************************/
#define SIU_RCR_RET_MASK32                  ((uint32)0x0000000FU)


/**********************************/
/*         SIU_PCSER              */
/*********************************/
#define SIU_PCSER_PCSE_MASK32               ((uint32)0x00000001U)


/********************************/
/*         SIU_PCSIFR          */
/*******************************/
#define SIU_PCSIFR_PCSMS_MASK32             ((uint32)0x00000006U)
#define SIU_PCSIFR_PCSI_MASK32              ((uint32)0x00000001U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* MCU_REG_ESYS_SIU_H */

/** @} */

