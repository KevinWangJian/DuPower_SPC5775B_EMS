/**
*   @file    Mcu_Cfg.c
*   @implements Mcu_Cfg.c_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Data structures for the Mcu driver.
*   @details Precompile structure configuration for the driver initalization.
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
* @section Mcu_Cfg_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a violation
* since all header files are protected against multiple inclusions
*
* @section Mcu_Cfg_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_Cfg_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcu_Cfg_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between
* a pointer to a function and any type other than an integral type.
* Appears when accessing memory-mapped registers.
*
* @section Mcu_Cfg_c_REF_5
* Violates MISRA 2004 Advisory Rule 11.4, A cast should not be performed
* between a pointer to object type and a different pointer to object type.
*
* @section Mcu_Cfg_c_REF_6
* Violates MISRA 2004 Required Rule 20.2, The names of standard macros, objects and
* functions shall not be reused
*
* @section Mcu_Cfg_c_REF_7
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is requiered.
*
* @section Mcu_Cfg_c_REF_8
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
#include "Mcu.h"

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

/*==================================================================================================
                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_CFG_VENDOR_ID_C                     43
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION_C      4
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_CFG_AR_RELEASE_MINOR_VERSION_C      0
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_CFG_AR_RELEASE_REVISION_VERSION_C   3
#define MCU_CFG_SW_MAJOR_VERSION_C              1
#define MCU_CFG_SW_MINOR_VERSION_C              0
#define MCU_CFG_SW_PATCH_VERSION_C              1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
* @brief            The MCU module's implementer shall avoid the integration of incompatible files.
*/
/* Check if current file and MCU header file are of the same vendor */
#if (MCU_CFG_VENDOR_ID_C != MCU_VENDOR_ID)
    #error "Mcu_Cfg.c and Mcu.h have different vendor ids"
#endif

/* Check if current file and MCU header file are of the same Autosar version */
#if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION_C != MCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_MINOR_VERSION_C != MCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_CFG_AR_RELEASE_REVISION_VERSION_C != MCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_Cfg.c and Mcu.h are different"
#endif

/* Check if current file and MCU header file are of the same Software version */
#if ((MCU_CFG_SW_MAJOR_VERSION_C != MCU_SW_MAJOR_VERSION) || \
     (MCU_CFG_SW_MINOR_VERSION_C != MCU_SW_MINOR_VERSION) || \
     (MCU_CFG_SW_PATCH_VERSION_C != MCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_Cfg.c and Mcu.h are different"
#endif

/* Check if current file and DEM header file are of the same version */
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_CFG_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_CFG_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_Cfg.c and Dem.h are different"
    #endif
#endif
#endif


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Mcu_Cfg_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_Cfg_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/





#if (MCU_PRECOMPILE_SUPPORT == STD_ON)





#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief        DEM error reporting configuration
* @details      Set the state and id for Mcal_DemErrorType.
*/
static CONST( Mcu_DemConfigType, MCU_CONST) Mcu_Dem_ConfigPC0 =
{

    /* DEM error reporting MCU_E_TIMEOUT_FAILURE */
    {(uint32)STD_OFF, 0U},

    /* DEM error reporting MCU_E_SSCM_CER_FAILURE */
    {(uint32)STD_OFF, 0U}

};
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */






/**
* @brief        Definition of RAM sections within the configuration structure.
* @details      Blocks of memory are initialized with a default data.
*               Configuration set by calling Mcu_InitClock() API.
*
*/
static CONST(Mcu_RamConfigType, MCU_CONST) Mcu_Ram_ConfigPC0[1] =
{

    {
        /* The ID for Ram Sector configuration. */
        (uint8)0U,

        /* RAM section base address: Start of Mcu_RamConfig[0]. */
        /** @violates @ref Mcu_Cfg_c_REF_4 MISRA 2004 Required Rule 11.1, conversion from pointer to integer */
        /** @violates @ref Mcu_Cfg_c_REF_5 MISRA 2004 Advisory Rule 11.4, cast between pointer and object */
        /** @violates @ref Mcu_Cfg_c_REF_8 MISRA 2004 Required Rule 11.3, a cast should not be performed between */
        (uint8 (*)[1U])0x40000000U,

        /* RAM section size: Section base address (must be aligned to 4 bytes). */
        (uint32)0x00000400U,

        /* RAM default value: Section size in bytes (must be multiple of 4). */
        (uint8)0xbaU
    } /* End of Mcu_Ram_ConfigPC[0]. */
                
};




/**
* @brief        Definition of MCU mode sections in the configuration structure.
* @details      Specifies the system behaviour during the selected target mode.
*               Configuration set by calling Mcu_SetMode() API.
*/
static CONST( Mcu_ModeConfigType, MCU_CONST) Mcu_Mode_ConfigPC0[1] =
{

    /* Start of Mcu_ModeConfig[0]*/
    {
        /* The ID for Power Mode configuration. */
        (uint8)0U,
        
        /* Core 0 Reset Vector Register Configuration */
        (
            SIU_RSTVEC_RSTVEC_U32(0xfffffffcU) |
            SIU_RSTVEC_RST_DISABLE_U32 |
            SIU_RSTVEC_VLE_BOOK_E_U32
        ),
        
        /* Core 1 Reset Vector Register Configuration */
        (
            SIU_RSTVEC_RSTVEC_U32(0xfffffffcU) |
            SIU_RSTVEC_RST_DISABLE_U32 |
            SIU_RSTVEC_VLE_BOOK_E_U32
        ),    
        
        
        /* SIU_HLT1 register value */
        (
                            
            SIU_HLT1_CORE0_HALT_DIS_U32                                                         | 
            SIU_HLT1_CORE1_HALT_EN_U32                                         | 
            SIU_HLT1_CSE_HALT_DIS_U32                                             | 
            SIU_HLT1_DECFIL_HALT_DIS_U32                                             | 
            SIU_HLT1_DSPIA_HALT_DIS_U32                                             | 
            SIU_HLT1_DSPIB_HALT_DIS_U32                                             | 
            SIU_HLT1_DSPIC_HALT_DIS_U32                                             | 
            SIU_HLT1_DSPID_HALT_DIS_U32                                             | 
            SIU_HLT1_DSPIE_HALT_DIS_U32                                             | 
            SIU_HLT1_EBI_HALT_DIS_U32                                             | 
            SIU_HLT1_EMIOS0_HALT_DIS_U32                                             | 
            SIU_HLT1_EMIOS1_HALT_DIS_U32                                             | 
            SIU_HLT1_EQADCA_HALT_DIS_U32                                             | 
            SIU_HLT1_EQADCB_HALT_DIS_U32                                             | 
            SIU_HLT1_ESCIA_HALT_DIS_U32                                             | 
            SIU_HLT1_ESCIB_HALT_DIS_U32                                             | 
            SIU_HLT1_ESCIC_HALT_DIS_U32                                             | 
            SIU_HLT1_ESCID_HALT_DIS_U32                                             | 
            SIU_HLT1_ESCIE_HALT_DIS_U32                                             | 
            SIU_HLT1_ESCIF_HALT_DIS_U32                                             | 
            SIU_HLT1_ETPUA_HALT_DIS_U32                                             | 
            SIU_HLT1_ETPUC_HALT_DIS_U32                                             | 
            SIU_HLT1_FLEXCANA_HALT_DIS_U32                                             | 
            SIU_HLT1_FLEXCANB_HALT_DIS_U32                                             | 
            SIU_HLT1_FLEXCANC_HALT_DIS_U32                                             | 
            SIU_HLT1_FLEXCAND_HALT_DIS_U32                                             | 
            SIU_HLT1_NPC_HALT_DIS_U32                                             | 
            SIU_HLT1_PIT_HALT_DIS_U32                                    ),
        
        
        /* SIU_HLT2 register value */
        (
                            
            SIU_HLT2_CRC_HALT_DIS_U32
                                             | 
            SIU_HLT2_FEC_HALT_DIS_U32
                                             | 
            SIU_HLT2_MCANA_HALT_DIS_U32
                                             | 
            SIU_HLT2_MCANB_HALT_DIS_U32
                                             | 
            SIU_HLT2_PSI5A_HALT_DIS_U32
                                             | 
            SIU_HLT2_PSI5B_HALT_DIS_U32
                                             | 
            SIU_HLT2_SDA_HALT_DIS_U32
                                             | 
            SIU_HLT2_SDB_HALT_DIS_U32
                                             | 
            SIU_HLT2_SDC_HALT_DIS_U32
                                             | 
            SIU_HLT2_SDD_HALT_DIS_U32
                                             | 
            SIU_HLT2_SIPI_HALT_DIS_U32
                                             | 
            SIU_HLT2_SRX0_HALT_DIS_U32
                                             | 
            SIU_HLT2_SRX1_HALT_DIS_U32
                                             | 
            SIU_HLT2_STCU_HALT_DIS_U32
                                    )
    }/* end of Mcu_Mode_ConfigPC0[0]. */

};




#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief        Timing configuration for FLASH hw IP.
* @details      Set the Pipeline/Write/Read wait states for FLASH controller.
*               Configuration set by calling Mcu_InitClock API.
*/
static CONST( Mcu_FLASH_ClockConfigType, MCU_CONST) FLASH_Clock_ConfigPC0_0 =
{
    /* Flash Controller timing settings.
       PFCR1 configuration register: Address Pipelining Control & Read Wait State Control. */
    (
        MCU_FLASH_ADDR_PIPELINE_WS_U32(1U) |
        MCU_FLASH_READ_WS_U32(3U)
    )
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
static CONST( Mcu_SIU_RegisterConfigType, MCU_CONST) PcsClock_ConfigPC0_0[MCU_NUMBER_OF_PCS_REGS] =
{

    /* PCS Divider Change Register 1. */
    {
        PCS_DIVC1_ADDR32,
        PCS_DIVC_U32
        (
            PCS_DIVC_INIT_U32((uint32)0x000003e7U) |
            PCS_DIVC_RATE_U32((uint32)0x00000000U)
        )
    },
    /* PCS Divider Start Register 1. */
    {
        PCS_DIVS1_ADDR32,
        PCS_DIVS_U32((uint32)0x000003e7U)
    },
    /* PCS Divider End Register 1. */
    {
        PCS_DIVE1_ADDR32,
        PCS_DIVE_U32((uint32)0x000003e7U)
    },

    /* PCS Divider Change Register 2. */
    {
        PCS_DIVC2_ADDR32,
        PCS_DIVC_U32
        (
            PCS_DIVC_INIT_U32((uint32)0x000003e7U) |
            PCS_DIVC_RATE_U32((uint32)0x00000000U)
        )
    },
    /* PCS Divider Start Register 2. */
    {
        PCS_DIVS2_ADDR32,
        PCS_DIVS_U32((uint32)0x000003e7U)
    },
    /* PCS Divider End Register 2. */
    {
        PCS_DIVE2_ADDR32,
        PCS_DIVE_U32((uint32)0x000003e7U)
    },

    /* PCS Divider Change Register 3. */
    {
        PCS_DIVC3_ADDR32,
        PCS_DIVC_U32
        (
            PCS_DIVC_INIT_U32((uint32)0x000003e7U) |
            PCS_DIVC_RATE_U32((uint32)0x00000000U)
        )
    },
    /* PCS Divider Start Register 3. */
    {
        PCS_DIVS3_ADDR32,
        PCS_DIVS_U32((uint32)0x000003e7U)
    },
    /* PCS Divider End Register 3. */
    {
        PCS_DIVE3_ADDR32,
        PCS_DIVE_U32((uint32)0x000003e7U)
    }

};
#endif /* (MCU_INIT_CLOCK == STD_ON) */




#if (MCU_INIT_CLOCK == STD_ON)
static CONST( Mcu_SIU_RegisterConfigType, MCU_CONST) SIU_AuxClock_ConfigPC0_0[4] =
{

        /* External Clock Register Configuration. */
    {
        SIU_ECCR_ADDR32,
        (
            SIU_ECCR_ENGDIV_U32((uint32)(50U)) |
            SIU_ECCR_ECCS_SOURCE_PLAT_CLK_U32 |
            SIU_ECCR_EBTS_ZERO_HOLD_TIMES_U32 |
            SIU_ECCR_EBDF_U32((uint32)(3U))
        )
    }

    ,    /* Sigma Delta Clock Config Register. */
    {
        SIU_SDCLKCFG_ADDR32,
        SIU_SDCLKCFG_SDDIV_U32((uint32)(1U))
    }

    ,    /* LFAST Clock Config Register. */
    {
        SIU_LFCLKCFG_ADDR32,
        (
                                                SIU_LFCLKSEL_SOURCE_PER_CLK_UNDIV_U32 |
        SIU_LFCLKCFG_LFDDIV_U32((uint32)(1U))
        )
    }

    ,    /* PSI5 Clock Config Register. */
    {
        SIU_PSCLKCFG_ADDR32,
        (
            SIU_PSCLKCFG_PSDIV_U32((uint32)(1U)) |
            SIU_PSCLKCFG_PSDIV1M_U32((uint32)(1U))
        )
    }

};
#endif /* (MCU_INIT_CLOCK == STD_ON) */




#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            SIU clock configuration.
* @details          This structure contains information for XOSC, PLL, Output Clocks, CMUs
*
*/
static CONST( Mcu_SIU_ClockConfigType, MCU_CONST) SIU_Clock_ConfigPC0_0 =
{
    /* system clock configuration */
        (
                                                    SIU_SYSDIV_SYSCLKSEL_SOURCE_PLL1_PHI_U32 |
        SIU_SYSDIV_SYSCLKDIV_U32((uint32)(4U)) |
        SIU_SYSDIV_PLL0SEL_SOURCE_XOSC_U32 |
        SIU_SYSDIV_PLL1SEL_SOURCE_PLL0_PHI1_U32 |
        SIU_SYSDIV_FMPERDIV_U32((uint32)(0U)) |
        SIU_SYSDIV_PERCLKSEL_SOURCE_PLL0_PHI_U32 |
        SIU_SYSDIV_PERDIV_U32((uint32)(0U)) |
        SIU_SYSDIV_ETPUDIV_DIVIDE_BY_2_U32 |
        SIU_SYSDIV_MCANSEL_SOURCE_XOSC_U32 |
        SIU_PCSEN_PCS_ENABLED_U32
    )
    ,
    
    /* Progressive Clock Switching (CGM_PCS_SDUR[SDUR]) */
    PCS_SDUR_U32((uint32)0x00U),

    /* number of pcs registers unde mcu control */
    MCU_NUMBER_OF_PCS_REGS,

    /* pcs registers */
    &PcsClock_ConfigPC0_0,

    /* number of configurable aux clock regs */
    ((uint8)4U),

    /* auxiliary clock dividers */
     &SIU_AuxClock_ConfigPC0_0
    

};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            PLLDIG Registers configuration.
* @details          This structure contains configuration for PLLDIG Registers.
*
*/
/** @violates @ref Mcu_Cfg_c_REF_3 MISRA 2004 Required Rule 1.4, 31 characters limit.*/
static CONST( Mcu_PLLDIG_RegisterConfigType, MCU_CONST) Mcu_PLLDIG_Registers_Config_PC0_0[8] =
{
    
    /* turn off PLL1 */
    {
        PLLDIG_PLL1CR_ADDR32,
        MCU_PLLDIG_PLL1CR_U32
        (
            PLLDIG_PLL1CR_CLKCFG_BO_U32
        )
    },
    /* turn off PLL0 */
    {
        PLLDIG_PLL0CR_ADDR32,
        MCU_PLLDIG_PLL0CR_U32
        (
            PLLDIG_PLL0CR_CLKCFG_BO_U32
        )
    },
    /* PLL0 dividers */
    {
        PLLDIG_PLL0DV_ADDR32,
        MCU_PLLDIG_PLL0DV_U32
        (
            MCU_PLLDIG_PLL0DV_RFDPHI1_U32( (uint32)10U ) |
            MCU_PLLDIG_PLL0DV_RFDPHI_U32( (uint32)5U ) |
            MCU_PLLDIG_PLL0DV_PREDIV_U32( (uint32)5U ) |
            MCU_PLLDIG_PLL0DV_MFD_U32( (uint32)50U )
        )
    },
    /* PLL0 configuration */
    {
        PLLDIG_PLL0CR_ADDR32,
        MCU_PLLDIG_PLL0CR_U32
        (
            PLLDIG_PLL0CR_CLKCFG_NR_U32 |
            MCU_PLLDIG_PLL0CR_LOLIE_DIS_U32
        )
    },
    /* PLL1 dividers */
    {
        PLLDIG_PLL1DV_ADDR32,
        MCU_PLLDIG_PLL1DV_U32
        (
            MCU_PLLDIG_PLL1DV_RFDPHI_U32( (uint32)2U ) |
            MCU_PLLDIG_PLL1DV_MFD_U32( (uint32)22U )
        )
    },
    /* PLL1 frequency modulation */
    {
        PLLDIG_PLL1FM_ADDR32,
        MCU_PLLDIG_PLL1FM_U32( MCU_PLLDIG_PLL1FM_MODEN_DIS_U32 )
    },
    /* PLL1 fractional divider */
    {
        PLLDIG_PLL1FD_ADDR32,
        MCU_PLLDIG_PLL1FD_U32( MCU_PLLDIG_PLL1FD_FDEN_DIS_U32 )
    },
    /* PLL1 configuration */
    {
        PLLDIG_PLL1CR_ADDR32,
        MCU_PLLDIG_PLL1CR_U32
        (
            PLLDIG_PLL1CR_CLKCFG_NR_U32 |
            MCU_PLLDIG_PLL1CR_LOLIE_DIS_U32
        )
    }
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            PLLDIG clock configuration.
* @details          This structure contains information for PLLDIG PLL0 and FMPLL1.
*
*/
static CONST( Mcu_PLLDIG_ConfigType, MCU_CONST) MC_PLLDIG_pClockConfigPC0_0 =
{
    /* number of pll regs under mcu control */
    0x08U,
    /* configuration for PLLDIG registers */
    &Mcu_PLLDIG_Registers_Config_PC0_0
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            




#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_EMIOS_SUPPORT == STD_ON)
/**
* @brief            eMios Module Configuration.
* @details          This structure contains information for eMios0 and eMios1.
*
*/
/** @violates @ref Mcu_Cfg_c_REF_6 This is not a standard library macro. */
static CONST(Mcu_eMios_ConfigType, MCU_CONST) EMIOS_Module_ConfigPC0_0 = 
{
    {
        /* eMios0 configuration */
        EMIOS_MCR_U32
        (
            EMIOS_MCR_MDIS_DIS_U32 |
            EMIOS_MCR_FRZ_ENA_U32 |
            EMIOS_MCR_GTBE_ENA_U32 |
            EMIOS_MCR_ETB_DIS_U32 |
            EMIOS_MCR_GPREN_ENA_U32 |
            EMIOS_MCR_GPRE_U32((uint32)200U)
        ),
        /* eMios1 configuration */
        EMIOS_MCR_U32
        (
            EMIOS_MCR_MDIS_DIS_U32 |
            EMIOS_MCR_FRZ_ENA_U32 |
            EMIOS_MCR_GTBE_ENA_U32 |
            EMIOS_MCR_ETB_DIS_U32 |
            EMIOS_MCR_GPREN_ENA_U32 |
            EMIOS_MCR_GPRE_U32((uint32)200U)
        )
    }
};
#endif /* (MCU_EMIOS_SUPPORT == STD_ON) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */




#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            CMU configuration.
* @details          This structure contains information for CMU[n].
*                   The number of CMU's is defined in the resource files,
*
*/
static CONST( Mcu_CMU_ConfigType, MCU_CONST) CMU_ConfigPC0_0 =
{
    {

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_8_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         ),

        CMU_CSR_U32
        (
            CMU_CSR_CMU_DIS_U32 |
            CMU_CSR_RCDIV_1_U32
         )

    },
    {

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_HFREFR_VALUE_U32
        (
            (uint32)0U
        )

    },
    {

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        ),

        CMU_LFREFR_VALUE_U32
        (
            (uint32)0U
        )

    }
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */




#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief        Timing configuration for SRAMC hw IP.
* @details      Set the Read wait states for RAM.
*               Configuration set by calling Mcu_InitClock API.
*/
static CONST( Mcu_PRAM_ClockConfigType, MCU_CONST) SRAMC_pClockConfigPC0_0 =
{
    /* PRAMC_0 Controller timing settings. PRCR1 configuration register. */
    PRAMC_PRCR1_VALUE_U32
    (
        PRAMC_PRCR1_P0_BO_ENA_U32 |
        PRAMC_PRCR1_FT_ENA_U32
    ),
    /* PRAMC_1 Controller timing settings. PRCR1 configuration register. */
    PRAMC_PRCR1_VALUE_U32
    (
        PRAMC_PRCR1_P0_BO_ENA_U32 |
        PRAMC_PRCR1_FT_ENA_U32
    )
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
            



#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief          Initialization clock data.
* @details        Static configuration realized by calling Mcu_InitClock() API.
*
*/
static CONST( Mcu_ClockConfigType, MCU_CONST) Mcu_Clock_ConfigPC0[1] =
{
    
    /* Start of Mcu_ClockConfig[0]. */
    {
            
        /* ID Clock Configuration. */
        (uint8)0U,

        /* Globally enable/disable SCM, loss of clock and loss of lock notification. */
        (MCU_CLK_NOTIF_DIS),
        
        /* SIU IP Clock settings. */
        &SIU_Clock_ConfigPC0_0,

        /* PLLDIG IP Clock settings. */
        &MC_PLLDIG_pClockConfigPC0_0,
        
#if (MCU_EMIOS_SUPPORT == STD_ON)
        /* eMios Module settings. */
        &EMIOS_Module_ConfigPC0_0,
#endif
        /* CMU IP Clock settings. */
        &CMU_ConfigPC0_0,

#if (MCU_SRAMC_SUPPORT == STD_ON)
        /* SRAMC IP Clock settings. */
        &SRAMC_pClockConfigPC0_0,
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */

        /* FLASH IP Clock settings. */
        &FLASH_Clock_ConfigPC0_0,

        (MCU_IPW_PLL0_UNDER_MCU_CONTROL |
         MCU_IPW_PLL1_UNDER_MCU_CONTROL)

    } /* end of Mcu_ClockConfig[0] */
            
};
#endif /* (MCU_INIT_CLOCK == STD_ON) */
        



/**
* @brief          Initialization data for MC_RGM hw IP.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
static CONST(Mcu_SIU_ResetConfigType, MCU_CONST) SIU_ResetConfigPC0 =
{
#if (MCU_PERFORM_RESET_API == STD_ON)
    /* Reset type: software system vs software external. */
    (MCU_SOFT_SYSTEM_RESET),
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

    /* Reset escalation threshold */
    SIU_RCR_RET_U32((uint32)(8U))
};




/**
* @brief            Platform FLASH hw IP configuration.
* @details          Configure prefetch mechanism, buffers, access protection.
*                   Configuration set by calling Mcu_Init API.
*/
static CONST( Mcu_FLASH_ConfigType, MCU_CONST) FLASH_ConfigPC0 =
{
    /* Platform Flash Configuration Register 1 (PFCR1). */
    MCU_FLASH_PFCR1_U32
    (
        MCU_FLASH_P0_MASTER15_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER14_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER13_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER12_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER11_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER10_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER9_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER8_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER7_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER6_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER5_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER4_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER3_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER2_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER1_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_MASTER0_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_DATA_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_INSTR_PREFETCH_DIS_U32 |
        MCU_FLASH_P0_PFLIM_U32( (uint32)0U ) |
        MCU_FLASH_P0_BUFFER_EN_U32
    ),

    /* Platform Flash Configuration Register 2 (PFCR2). */
    MCU_FLASH_PFCR2_U32
    (
        MCU_FLASH_P1_MASTER15_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER14_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER13_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER12_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER11_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER10_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER9_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER8_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER7_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER6_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER5_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER4_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER3_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER2_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER1_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_MASTER0_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_DATA_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_INSTR_PREFETCH_DIS_U32 |
        MCU_FLASH_P1_PFLIM_U32( (uint32)0U ) |
        MCU_FLASH_P1_BUFFER_EN_U32
    ),

    /* Platform Flash Configuration Register 3 (PFCR3). */
    MCU_FLASH_PFCR3_U32
    (
        MCU_FLASH_BFEN_LOCK_U32 |
        MCU_FLASH_P0_WCFG_U32( (uint32)0U ) |
        MCU_FLASH_P1_WCFG_U32( (uint32)0U ) |
        MCU_FLASH_ARBM_WCFG_U32( (uint32)0U ) |
        MCU_FLASH_DERR_SUP_DIS_U32
    ),

    /* Platform Flash Access Protection Register (PFAPR). */
    MCU_FLASH_PFAPR_U32
    (
        MCU_FLASH_M0AP_U32( (uint32)3U ) |
        MCU_FLASH_M1AP_U32( (uint32)3U ) |
        MCU_FLASH_M2AP_U32( (uint32)3U ) |
        MCU_FLASH_M3AP_U32( (uint32)3U ) |
        MCU_FLASH_M4AP_U32( (uint32)3U ) |
        MCU_FLASH_M5AP_U32( (uint32)3U ) |
        MCU_FLASH_M6AP_U32( (uint32)3U ) |
        MCU_FLASH_M7AP_U32( (uint32)3U ) |
        MCU_FLASH_M8AP_U32( (uint32)3U ) |
        MCU_FLASH_M9AP_U32( (uint32)3U ) |
        MCU_FLASH_M10AP_U32( (uint32)3U ) |
        MCU_FLASH_M11AP_U32( (uint32)3U ) |
        MCU_FLASH_M12AP_U32( (uint32)3U ) |
        MCU_FLASH_M13AP_U32( (uint32)3U ) |
        MCU_FLASH_M14AP_U32( (uint32)3U ) |
        MCU_FLASH_M15AP_U32( (uint32)3U )
    )
};
        



/**
* @brief          Initialization data for PMC hw IP.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
static CONST( Mcu_PMC_ConfigType, MCU_CONST) PMC_ConfigPC0 =
{
    /* Reset event interrupt enable register. PMC_TS_IER register. */
    PMC_TS_IER_CONFIG_U32
    (
        PMC_TS_IER_TS1_2IE_DIS_U32 |
        PMC_TS_IER_TS1_0IE_DIS_U32 |
        PMC_TS_IER_TS0_2IE_DIS_U32 |
        PMC_TS_IER_TS0_0IE_DIS_U32
    ),

    /* Temperature reset event enable register. PMC_REE_TD register. */
    PMC_REE_TD_CONFIG_U32
    (
        PMC_REE_TD_TEMP1_2_ENA_U32 |
        PMC_REE_TD_TEMP1_0_ENA_U32 |
        PMC_REE_TD_TEMP0_2_ENA_U32 |
        PMC_REE_TD_TEMP0_0_ENA_U32
    ),

    /* Temperature reset event selection register. PMC_RES_TD register. */
    PMC_RES_TD_CONFIG_U32
    (
        PMC_RES_TD_TEMP1_2_POR_GENERATED_U32 |
        PMC_RES_TD_TEMP1_0_POR_GENERATED_U32 |
        PMC_RES_TD_TEMP0_2_POR_GENERATED_U32 |
        PMC_RES_TD_TEMP0_0_POR_GENERATED_U32
    ),

    /* Temperature detector configuration register. PMC_CTL_TD register. */
    PMC_CTL_TD_CONFIG_U32
    (
        PMC_CTL_TD_TS1_ENA_U32 |
        PMC_CTL_TD_TS0_ENA_U32
    ),

     /* LVD/HVD Interrupt Enable Control Register. PMC_LVD_HVD_INTR_ENB register. */
     PMC_LVD_HVD_INTR_ENB_U32
     (
        PMC_HVD_FLASH_INT_DISABLED_U32 |
        PMC_HVD_HV_INT_DISABLED_U32 |
        PMC_HVD_CORE_INT_DISABLED_U32 |
        PMC_LVD_CORE_COLD_INT_DISABLED_U32
    ),
    
     /* ADC Channel Select Register. PMC_ADC_CS register. */
     PMC_ADC_CS_ADC_CHANNEL_OFF_U32,
     
     /* Reset Event Enable Register. PMC_REE register. */
     PMC_REE_U32
     (
        PMC_HVD_FLASH_RESET_DISABLED_U32 |
        PMC_HVD_HV_RESET_DISABLED_U32 |
        PMC_HVD_CORE_RESET_DISABLED_U32 |
        PMC_LVD_CORE_COLD_RESET_DISABLED_U32
     )
};
        



/**
* @brief          Initialization data for SSCM hw IP.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
static CONST( Mcu_SSCM_ConfigType, MCU_CONST) SSCM_ConfigPC0 =
{
    /* SSCM configuration */
    SSCM_ERROR_U16(
        SSCM_ERROR_PAE_ENABLE_U16
    )

};




/**
* @brief          Initialization data for different hw IPs.
* @details        Static configuration realized at statup by calling Mcu_Init() API.
*
*/
static CONST( Mcu_HwIPsConfigType, MCU_CONST) Mcu_HwIPs_ConfigPC0 =
{
    /* Configuration for SIU Reset. */
    &SIU_ResetConfigPC0,

    /* Configuration for PMC (Power Management Control) hardware IP. */
    &PMC_ConfigPC0,

    /* Configuration for FLASH (Flash Memory) hardware IP. */
    &FLASH_ConfigPC0,

    /* Configuration for SSCM hardware IP. */
    &SSCM_ConfigPC0
};




/**
* @brief          Initialization data for the MCU driver.
* @details        A pointer to such a structure is provided to the MCU initialization routines for configuration.
*
*/
/** @violates @ref Mcu_Cfg_c_REF_7 MISRA 2004 Required Rule 8.10, external linkage ... */
CONST(Mcu_ConfigType, MCU_CONST) Mcu_Config_PC = 
{
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    /* Pointer to DEM error reporting configurations. */
    &Mcu_Dem_ConfigPC0,
#endif

    /* Number of RAM Sections configurations. */
    (Mcu_RamSectionType)1U,

    /* Number of Power Modes configurations. */
    (Mcu_ModeType)1U,

#if (MCU_INIT_CLOCK == STD_ON)
    /* Number of Clock Setting configurations. */
    (Mcu_ClockType)1U,
#endif /* (MCU_INIT_CLOCK == STD_ON) */

    /* Pointer to RAM Section configurations. */
    &Mcu_Ram_ConfigPC0,

    /* Pointer to Power Mode configurations. */
    &Mcu_Mode_ConfigPC0,

#if (MCU_INIT_CLOCK == STD_ON)
    /* Pointer to Clock configurations. */
    &Mcu_Clock_ConfigPC0,
#endif /* (MCU_INIT_CLOCK == STD_ON) */

    /* Pointer to Low Level Mcu driver configuration. */
    &Mcu_HwIPs_ConfigPC0
};



#endif /* (MCU_PRECOMPILE_SUPPORT == STD_ON) */


#define MCU_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Mcu_Cfg_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_Cfg_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

