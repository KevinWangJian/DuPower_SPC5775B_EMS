/**
*   @file    Reg_eSys_MCan.h
*   @version 1.0.1
*
*   @brief   AUTOSAR MCan - MPC560xB FlexCan Registers and Macros Definitions.
*   @details Header file for MPC560xB FlexCan Registers and Macros Definitions.
*
*   @addtogroup CAN_DRIVER
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MCAN
*   Dependencies         : 
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_HF1_ASR_REL_4_0_REV_0003_20170606
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/


#ifndef REG_ESYS_MCAN_H
#define REG_ESYS_MCAN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section Reg_eSys_MCan_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Reg_eSys_MCan_h_REF_2
* Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* The respective code could not be made static because of layers architecture design of the driver.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Reg_eSys_MCan_h_REF_4
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Reg_eSys.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @{
* @brief Internal micro-dependent versioning.
*/
#define CAN_VENDOR_ID_REGM                    43
#define CAN_MODULE_ID_REGM                    80
#define CAN_AR_RELEASE_MAJOR_VERSION_REGM     4
#define CAN_AR_RELEASE_MINOR_VERSION_REGM     0
#define CAN_AR_RELEASE_REVISION_VERSION_REGM  3
#define CAN_SW_MAJOR_VERSION_REGM             1
#define CAN_SW_MINOR_VERSION_REGM             0
#define CAN_SW_PATCH_VERSION_REGM             1
/**@}*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
#ifdef  MCAN1_BASEADDR
        #define MCAN1_AVAILABLE    1U
#else    
        #define MCAN1_AVAILABLE    0U    
#endif /* MCAN1_AVAILABLE */

#ifdef  MCAN2_BASEADDR
        #define MCAN2_AVAILABLE    1U
#else    
        #define MCAN2_AVAILABLE    0U    
#endif /* MCAN2_AVAILABLE */

#ifdef  MCAN3_BASEADDR
        #define MCAN3_AVAILABLE    1U
#else    
        #define MCAN3_AVAILABLE    0U    
#endif /* MCAN3_AVAILABLE */

#ifdef  MCAN4_BASEADDR
        #define MCAN4_AVAILABLE    1U
#else    
        #define MCAN4_AVAILABLE    0U    
#endif /* MCAN4_AVAILABLE */

#ifdef  TTCAN0_BASEADDR
        #define TTCAN0_AVAILABLE    1U
#else    
        #define TTCAN0_AVAILABLE    0U    
#endif /* TTCAN0_BASEADDR */
/*Calculate the controllers number available on this platform*/
#define MCAN_CONTROLLERS_NO    (MCAN1_AVAILABLE + MCAN2_AVAILABLE + MCAN3_AVAILABLE + MCAN4_AVAILABLE + TTCAN0_AVAILABLE)
extern CONST(uint32, CAN_43_MCAN_CONST) MCAN_BASE_ADDRS[MCAN_CONTROLLERS_NO];
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define IPV_MCAN_01_00_01_61                   (0x01000161UL)     /* for XPC574XM platform */
#define IPV_MCAN_00_01_00_03                   (0x00010003UL)     /* for XPC577XM platform */
#define IPV_MCAN_00_00_00_21                   (0x00000021UL)   
/*Work around for BASE */
#ifndef IPV_MCAN
  #define IPV_MCAN      0x00010003UL
#endif

/**
* @brief Define used for Can_ControlerDescriptorType.u8ControllerOffset when controller is not enabled.
*/
#define MCAN_NULL_OFFSET_U8       ((uint8)0xFFU)

/**
* @brief Maximum number of Data Bytes that CAN frame accomidate
*/
#define MCAN_MB_DATABYTES_U8          ((uint8)CAN_43_MCAN_REAL_PAYLOAD_U8)
#define MCAN_MASK_32BITS_U32          ((uint32)0xFFFFFFFFU)
#define MCAN_NOT_MASK_32BITS_U32      ((uint32)0x00000000U)
#define MCAN_MBC_ID_IDE_U32           ((uint32)0x80000000U)
#define MCAN_TX_MB_MAX_U32            ((uint32)32U)

/**
* @brief Offset of the Standard ID in the ID reg of MB.
*/
#define MCAN_STANDARD_ID_SHIFT_U32 ((uint32)18U)

#if ((IPV_MCAN) == (IPV_MCAN_01_00_01_61))
#define MCAN_SRAM_SIZE            ((uint32)0x00003E00U)
#endif

#if ((IPV_MCAN) == (IPV_MCAN_00_01_00_03))
#define MCAN_SRAM_SIZE            ((uint32)0x00005000U)
#endif

#if ((IPV_MCAN) == (IPV_MCAN_00_00_00_21))
#define MCAN_SRAM_SIZE            ((uint32)0x00004000U)
#endif
/* start address share ram CAN */

#define IPV_MCAN_START_ADDRESS_OFFSET_SHARE_RAM_U32    0U

#define IPV_MCAN_END_ADDRESS_OFFSET_SHARE_RAM_U32      0x3FFFU

#define IPV_MCAN_END_ADDRESS_OFFSET_USEABLE_SHARE_RAM_U32      0x4FFFU

/* Area memory M_TTCAN */

#define IPV_MCAN_START_ADDRESS_OFFSET_TTCAN_U32    0x2D00U

#define IPV_MCAN_END_ADDRESS_OFFSET_TTCAN_U32      0x2EFFU

#ifdef IPV_MCAN
#if ((IPV_MCAN == IPV_MCAN_00_01_00_03) || (IPV_MCAN == IPV_MCAN_01_00_01_61))
/**
* @brief CME bit8: Enable FD
*/
#define MCAN_CCCR_CME_FDN_U32   ((uint32)0x100U)
/**
* @brief FDRATE bit9: Enable values bit rate switch
*/
#define MCAN_CCCR_CME_BRS_U32   ((uint32)0x200U)
#define MCAN_CCCR_CMR_BRS_U32   ((uint32)0x00000800U)
#define MCAN_CCCR_CMR_NOT_BRS_U32   ((uint32)0x00000400U)
#define MCAN_CCCR_CMR_FSTD_U32  ((uint32)0x00000C00U)
#define MCAN_CCCR_FDO_CONFIGURATION ((uint32)0x1000U)
#endif

#if(IPV_MCAN == IPV_MCAN_00_00_00_21)
/**
* @brief FDOE bit8: Enable FD
*/
#define MCAN_CCCR_FDOE_U32   ((uint32)0x100U)
/**
* @brief BRSE bit9: Enable values bit rate switch
*/
#define MCAN_CCCR_BRSE_U32   ((uint32)0x200U)
#endif
#endif

#if (IPV_MCAN_00_00_00_21 == IPV_MCAN_00_00_00_21)  
#define CAN_8_BYTES_PAYLOAD CAN_43_MCAN_8_BYTES_PAYLOAD
#define CAN_12_BYTES_PAYLOAD CAN_43_MCAN_12_BYTES_PAYLOAD
#define CAN_16_BYTES_PAYLOAD CAN_43_MCAN_16_BYTES_PAYLOAD
#define CAN_20_BYTES_PAYLOAD CAN_43_MCAN_20_BYTES_PAYLOAD
#define CAN_24_BYTES_PAYLOAD CAN_43_MCAN_24_BYTES_PAYLOAD
#define CAN_32_BYTES_PAYLOAD CAN_43_MCAN_32_BYTES_PAYLOAD
#define CAN_48_BYTES_PAYLOAD CAN_43_MCAN_48_BYTES_PAYLOAD
#define CAN_64_BYTES_PAYLOAD CAN_43_MCAN_64_BYTES_PAYLOAD
#endif

/* The MB data lengths */
#define MCAN_8_BYTES_U8               ((uint8)0x08U)
#define MCAN_12_BYTES_U8              ((uint8)0x0CU)
#define MCAN_16_BYTES_U8              ((uint8)0x10U)
#define MCAN_20_BYTES_U8              ((uint8)0x14U)
#define MCAN_24_BYTES_U8              ((uint8)0x18U)
#define MCAN_32_BYTES_U8              ((uint8)0x20U)
#define MCAN_48_BYTES_U8              ((uint8)0x30U)
#define MCAN_64_BYTES_U8              ((uint8)0x40U)

/* Offset of the data length code bits for RX and TX element */
#define MCAN_MB_DLC_SHIFT_U32         ((uint32)16U)

/* Define for configuration the data field size for Rx buffer/FIFO element */
#define MCAN_RXESC_8_BYTES_DATA_SIZE_U32            ((uint32)0x000U)
#define MCAN_RXESC_12_BYTES_DATA_SIZE_U32          ((uint32)0x111U)
#define MCAN_RXESC_16_BYTES_DATA_SIZE_U32          ((uint32)0x222U)
#define MCAN_RXESC_20_BYTES_DATA_SIZE_U32          ((uint32)0x333U)
#define MCAN_RXESC_24_BYTES_DATA_SIZE_U32          ((uint32)0x444U)
#define MCAN_RXESC_32_BYTES_DATA_SIZE_U32          ((uint32)0x555U)
#define MCAN_RXESC_48_BYTES_DATA_SIZE_U32          ((uint32)0x666U)
#define MCAN_RXESC_64_BYTES_DATA_SIZE_U32          ((uint32)0x777U)

/* Define for configuration the data field size for Tx buffer element*/
#define MCAN_TXESC_8_BYTES_DATA_SIZE_U32            ((uint32)0x00U)
#define MCAN_TXESC_12_BYTES_DATA_SIZE_U32          ((uint32)0x01U)
#define MCAN_TXESC_16_BYTES_DATA_SIZE_U32          ((uint32)0x02U)
#define MCAN_TXESC_20_BYTES_DATA_SIZE_U32          ((uint32)0x03U)
#define MCAN_TXESC_24_BYTES_DATA_SIZE_U32          ((uint32)0x04U)
#define MCAN_TXESC_32_BYTES_DATA_SIZE_U32          ((uint32)0x05U)
#define MCAN_TXESC_48_BYTES_DATA_SIZE_U32          ((uint32)0x06U)
#define MCAN_TXESC_64_BYTES_DATA_SIZE_U32          ((uint32)0x07U)

#ifdef CAN_43_MCAN_EXTENDEDID
    #if (CAN_43_MCAN_EXTENDEDID == STD_ON)
        #define CAN_43_MCAN_FD_ID_DESCRIPTOR                ((uint32)0x40000000U)
    #else /* (CAN_43_MCAN_EXTENDEDID == STD_OFF) */
        #define CAN_43_MCAN_FD_ID_DESCRIPTOR                ((uint16)0x4000U)
    #endif /* (CAN_43_MCAN_EXTENDEDID == STD_ON/STD_OFF) */
#endif 

#define CAN_43_MCAN_DBTP_TDC_MASK_U32  ((uint32) 0x00800000U)

/*Offset bits for FD register*/
#define MCAN_FD_OFFSET_U8               ((uint8)8U)
/* #define MCAN_FD_BRS_OFFSET              ((uint8)9U) */
#define MCAN_FD_PRESDIV_OFFSET          ((uint8)16U) 
#define MCAN_FD_PSEG1_OFFSET            ((uint8)8U)
#define MCAN_FD_PSEG2_OFFSET            ((uint8)4U)
#define MCAN_FD_SJW_OFFSET              ((uint8)0U)
#define MCAN_FD_BRS_OFFSET              ((uint8)9U)


/*==================================================================================================
                BIT OFFSETS FOR BTP REGISTER
==================================================================================================*/
#ifdef IPV_MCAN
#if ((IPV_MCAN == IPV_MCAN_00_01_00_03) || (IPV_MCAN == IPV_MCAN_01_00_01_61))
        #define MCAN_BTP_SJW_SHIFT       ((uint32)0U)
        #define MCAN_BTP_TSEG2_SHIFT     ((uint32)4U)
        #define MCAN_BTP_TSEG1_SHIFT     ((uint32)8U)
        #define MCAN_BTP_BRP_SHIFT       ((uint32)16U)
#endif
#if (IPV_MCAN == IPV_MCAN_00_00_00_21)
        #define MCAN_BTP_SJW_SHIFT       ((uint32)25U)
        #define MCAN_BTP_TSEG2_SHIFT     ((uint32)0U)
        #define MCAN_BTP_TSEG1_SHIFT     ((uint32)8U)
        #define MCAN_BTP_BRP_SHIFT       ((uint32)16U)
#endif
#endif
/*==================================================================================================
                CAN CONTOLLER CONFIGURATION MASKS
==================================================================================================*/
#define CAN_43_MCAN_CONTROLLERCONFIG_CCCR_ASM_EN_U32        ((uint32)0x00000001U)
#define CAN_43_MCAN_CONTROLLERCONFIG_CCCR_MON_EN_U32        ((uint32)0x00000002U)
#define CAN_43_MCAN_CONTROLLERCONFIG_CCCR_TEST_EN_U32       ((uint32)0x00000004U)
#define CAN_43_MCAN_CONTROLLERCONFIG_ERR_EN_U32             ((uint32)0x00004000U)
#define CAN_43_MCAN_CTLR_CONFIG_ILE_INTL0_EN_U32            ((uint32)0x00000040U)
#define CAN_43_MCAN_CTLR_CONFIG_ILE_INTL1_EN_U32            ((uint32)0x00000080U)
#define CAN_43_MCAN_CONTROLLERCONFIG_RXPOL_EN_U32           ((uint32)0x00000400U)
#define CAN_43_MCAN_CONTROLLERCONFIG_TXPOL_EN_U32           ((uint32)0x00000800U)
#define CAN_43_MCAN_CONTROLLERCONFIG_BOPOL_EN_U32           ((uint32)0x00001000U)
#define CAN_43_MCAN_CONTROLLERCONFIG_MRAFPOL_EN_U32         ((uint32)0x00002000U)


/*==================================================================================================
                              MCAN Register address calculation Macros
==================================================================================================*/
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define CAN_43_MCAN_GET_BASE_ADDRESS(offset) ((uint32)( MCAN_BASE_ADDRS[(offset)] ))

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_CREL(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_ENDN(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x04U ) )
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_FBTP(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x0CU ) )

#ifdef IPV_MCAN
#if (IPV_MCAN == IPV_MCAN_00_00_00_21)
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_DBTP(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x0CU ) )
#endif
#endif
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TEST(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x10U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RWD(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x14U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_CCCR(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x18U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_BTP(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x1CU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TSCC(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x20U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TSCV(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x24U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TOCC(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x28U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TOCV(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x2CU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_ECR(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x40U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_PSR(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x44U ) )

#ifdef IPV_MCAN
#if (IPV_MCAN == IPV_MCAN_00_00_00_21)
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TDCR(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x48U ) )
#endif
#endif
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_IR(offset)           ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x50U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_IE(offset)           ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x54U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_ILS(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x58U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_ILE(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x5CU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_GFC(offset)          ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x80U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_SIDFC(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x84U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_XIDFC(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x88U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_XIDAM(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x90U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_HPMS(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x94U ) )
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_NDAT1(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x98U ) )
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_NDAT2(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0x9CU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXF0C(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xA0U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXF0S(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xA4U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXF0A(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xA8U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXBC(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xACU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXF1C(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xB0U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXF1S(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xB4U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXF1A(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xB8U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_RXESC(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xBCU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXESC(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xC8U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBC(offset)         ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xC0U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXFQS(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xC4U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBRP(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xCCU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBAR(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xD0U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBCR(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xD4U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBTO(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xD8U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBCF(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xDCU ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBTIE(offset)       ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xE0U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXBCIE(offset)       ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xE4U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXEFC(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xF0U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXEFS(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xF4U ) )

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_TXEFA(offset)        ( (uint32)( CAN_43_MCAN_GET_BASE_ADDRESS(offset) + 0xF8U ) )



/*==================================================================================================
               MCAN REGISTER AND BIT ACCESS MACROS
==================================================================================================*/
#ifdef IPV_MCAN
#if ((IPV_MCAN == IPV_MCAN_00_01_00_03) || (IPV_MCAN == IPV_MCAN_01_00_01_61))
#define MCAN_CCCR_MASK_U32  ((uint32)0x00004FF7U)
#endif
#if (IPV_MCAN == IPV_MCAN_00_00_00_21)
#define MCAN_CCCR_MASK_U32  ((uint32)0x0000F3F7U)
#endif
#endif

#ifdef IPV_MCAN
#if ((IPV_MCAN == IPV_MCAN_00_01_00_03) || (IPV_MCAN == IPV_MCAN_01_00_01_61))
#define MCAN_BTP_MASK_U32   ((uint32)0x03FF3FFFU)
#endif
#if (IPV_MCAN == IPV_MCAN_00_00_00_21)
#define MCAN_BTP_MASK_U32   ((uint32)0xFFFFFF7FU)
#endif
#endif

#define MCAN_GFC_MASK_U32   ((uint32)0x0000003FU)
#define MCAN_SIDFC_MASK_U32 ((uint32)0x00FFFFFCU)
#define MCAN_XIDFC_MASK_U32 ((uint32)0x007FFFFCU)
#define MCAN_XIDAM_MASK_U32 ((uint32)0x1FFFFFFFU)
/* Note: The F0WM field in the has 7 bits*/
#define MCAN_RXF0C_MASK_U32 ((uint32)0x7F7FFFFCU)
#define MCAN_RXF0A_MASK_U32 ((uint32)0x0000003FU)
#define MCAN_RXF1C_MASK_U32 ((uint32)0x7F7FFFFCU)
#define MCAN_RXF1A_MASK_U32 ((uint32)0x0000003FU)
#define MCAN_RXESC_MASK_U32 ((uint32)0x0000777FU)
#define MCAN_TXESC_MASK_U32 ((uint32)0x0000007FU)
#define MCAN_TXBC_MASK_U32  ((uint32)0x7F3FFFFCU)
#define MCAN_ILE_MASK_U32   ((uint32)0x00000003U)

#ifdef IPV_MCAN
#if ((IPV_MCAN == IPV_MCAN_00_01_00_03) || (IPV_MCAN == IPV_MCAN_01_00_01_61))
#define MCAN_FBTP_MASK_U32  ((uint32)0x001F0F73U)
#endif
#if(IPV_MCAN == IPV_MCAN_00_00_00_21)
#define MCAN_FBTP_MASK_U32  ((uint32)0x009F1FFFU)
#endif
#endif

#ifdef IPV_MCAN
#if ((IPV_MCAN == IPV_MCAN_00_01_00_03) || (IPV_MCAN == IPV_MCAN_01_00_01_61))
#define MCAN_FBTP_TDCO_MASK_U32  ((uint32)0x1F000000U)
#endif
#if(IPV_MCAN == IPV_MCAN_00_00_00_21)
#define MCAN_TDCR_TDCO_MASK_U32  ((uint32)0x00007F00U)
#endif
#endif
/*==================================================================================================
                BIT MASKS FOR TEST REGISTER: TEST (Base+0x0010)
==================================================================================================*/

#define MCAN_TEST_LBCK_U32      ((uint32)0x00000010U)

/*==================================================================================================
                BIT MASKS FOR CC CONTROL REGISTER: CCCR (Base+0x0018)
==================================================================================================*/

#define MCAN_CCCR_INIT_U32      ((uint32)0x00000001U)
#define MCAN_CCCR_CCE_U32       ((uint32)0x00000002U)
#define MCAN_CCCR_ASM_U32       ((uint32)0x00000004U)
#define MCAN_CCCR_CSA_U32       ((uint32)0x00000008U)
#define MCAN_CCCR_CSR_U32       ((uint32)0x00000010U)
#define MCAN_CCCR_MON_U32       ((uint32)0x00000020U)
#define MCAN_CCCR_DAR_U32       ((uint32)0x00000040U)
#define MCAN_CCCR_TEST_U32      ((uint32)0x00000080U)


/*==================================================================================================
                BIT MASKS FOR BIT TIMING AND PRESCALAR REGISTER: BTP (Base+0x001C)
==================================================================================================*/

#ifdef IPV_MCAN
   
        #define MCAN_BTP_SJW_U32       ((uint32)0xFE000000U)
        #define MCAN_BTP_TSEG2_U32     ((uint32)0x0000007FU)
        #define MCAN_BTP_TSEG1_U32     ((uint32)0x0000FF00U)
        #define MCAN_BTP_BRP_U32       ((uint32)0x01FF0000U)
 
#endif

/*==================================================================================================
                BIT MASKS FOR ERROR COUNTER REGISTER: ECR (Base+0x0040)
==================================================================================================*/

#define MCAN_ECR_TEC_U32      ((uint32)0x000000FFU)
#define MCAN_ECR_REC_U32      ((uint32)0x00007F00U)
#define MCAN_ECR_RP_U32       ((uint32)0x00008000U)
#define MCAN_ECR_CEL_U32      ((uint32)0x00FF0000U)

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_ECR_READ(offset)                (REG_READ32( MCAN_ECR(offset)))

/*==================================================================================================
                BIT MASKS FOR PROTOCOL STATUS REGISTER: PSR (Base+0x0044)
==================================================================================================*/


#define MCAN_PSR_LEC_U32      ((uint32)0x00000007U)
#define MCAN_PSR_ACT_U32      ((uint32)0x00000018U)
#define MCAN_PSR_EP_U32       ((uint32)0x00000020U)
#define MCAN_PSR_EW_U32       ((uint32)0x00000040U)
#define MCAN_PSR_BO_U32       ((uint32)0x00000080U)


/*==================================================================================================
         BIT MASKS FOR INTERRUPT REGISTER,             : IR  (Base+0x0050)
         BIT MASKS FOR INTERRUPT ENABLE REGISTER,      : IE  (Base+0x0054)
         BIT MASKS FOR INTERRUPT LINE SELECT REGISTER, : ILS (Base+0x0058)
         BIT MASKS FOR INTERRUPT LINE ENABLE REGISTER, : ILE (Base+0x005C)
==================================================================================================*/
#define MCAN_INTERRUPT_RF0N_U32      ((uint32)0x00000001U)
#define MCAN_INTERRUPT_RF0W_U32      ((uint32)0x00000002U)
#define MCAN_INTERRUPT_RF0F_U32      ((uint32)0x00000004U)
#define MCAN_INTERRUPT_RF0L_U32      ((uint32)0x00000008U)
#define MCAN_INTERRUPT_RF1N_U32      ((uint32)0x00000010U)
#define MCAN_INTERRUPT_RF1W_U32      ((uint32)0x00000020U)
#define MCAN_INTERRUPT_RF1F_U32      ((uint32)0x00000040U)
#define MCAN_INTERRUPT_RF1L_U32      ((uint32)0x00000080U)
#define MCAN_INTERRUPT_HPM_U32       ((uint32)0x00000100U)
#define MCAN_INTERRUPT_TC_U32        ((uint32)0x00000200U)
#define MCAN_INTERRUPT_TCF_U32       ((uint32)0x00000400U)
#define MCAN_INTERRUPT_TFE_U32       ((uint32)0x00000800U)
#define MCAN_INTERRUPT_TEFN_U32      ((uint32)0x00001000U)
#define MCAN_INTERRUPT_TEFW_U32      ((uint32)0x00002000U)
#define MCAN_INTERRUPT_TEFF_U32      ((uint32)0x00004000U)
#define MCAN_INTERRUPT_TEFL_U32      ((uint32)0x00008000U)
#define MCAN_INTERRUPT_TSW_U32       ((uint32)0x00010000U)
#define MCAN_INTERRUPT_MRAF_U32       ((uint32)0x00020000U)
#define MCAN_INTERRUPT_TOO_U32       ((uint32)0x00040000U)
#define MCAN_INTERRUPT_DRX_U32       ((uint32)0x00080000U)
#define MCAN_INTERRUPT_BEC_U32       ((uint32)0x00100000U)
#define MCAN_INTERRUPT_BEU_U32       ((uint32)0x00200000U)
#define MCAN_INTERRUPT_ELO_U32       ((uint32)0x00400000U)
#define MCAN_INTERRUPT_EP_U32        ((uint32)0x00800000U)
#define MCAN_INTERRUPT_EW_U32        ((uint32)0x01000000U)
#define MCAN_INTERRUPT_BO_U32        ((uint32)0x02000000U)
#define MCAN_INTERRUPT_WDI_U32       ((uint32)0x04000000U)

#ifdef IPV_MCAN
#if ((IPV_MCAN == IPV_MCAN_00_01_00_03) || (IPV_MCAN == IPV_MCAN_01_00_01_61))
#define MCAN_INTERRUPT_CRCE_U32      ((uint32)0x08000000U)
#define MCAN_INTERRUPT_BE_U32        ((uint32)0x10000000U)
#define MCAN_INTERRUPT_ACKE_U32      ((uint32)0x20000000U)
#define MCAN_INTERRUPT_FOE_U32       ((uint32)0x40000000U)
#define MCAN_INTERRUPT_STE_U32       ((uint32)0x80000000U)
#define MCAN_ERR_INTERRUPT_U32       ((uint32)0xF0000000U)
#endif
#if (IPV_MCAN == IPV_MCAN_00_00_00_21)
#define MCAN_INTERRUPT_FEA_U32       ((uint32)0x08000000U)
#define MCAN_INTERRUPT_FED_U32       ((uint32)0x10000000U)
#define MCAN_INTERRUPT_ARA_U32       ((uint32)0x20000000U)
#define MCAN_ERR_INTERRUPT_U32       ((uint32)0x38000000U)
#define MCAN_INTERRUPT_MASK_U32      ((uint32)0x3FFFFFFFU)
#endif
#endif


/*==================================================================================================
         BIT MASKS FOR INTERRUPT LINE ENABLE REGISTER, : ILE (Base+0x005C)
==================================================================================================*/

#define MCAN_ILE_EINT0_U32      ((uint32)0x00000001U)
#define MCAN_ILE_EINT1_U32      ((uint32)0x00000002U)


/*==================================================================================================
         BIT MASKS FOR GLOBAL FILTER CONFIGURATION REGISTER, : GFC (Base+0x0080)
==================================================================================================*/

#define MCAN_GFC_RRFE_U32      ((uint32)0x00000001U)
#define MCAN_GFC_RRFS_U32      ((uint32)0x00000002U)
#define MCAN_GFC_ANFE_U32      ((uint32)0x0000000CU)
#define MCAN_GFC_ANFS_U32      ((uint32)0x00000030U)

/*==================================================================================================
         BIT MASKS FOR STANDARD ID FILTER CONFIGURATION REGISTER, : SIDFC (Base+0x0084)
==================================================================================================*/

#define MCAN_SIDFC_FLSSA_SHIFT_U32      ((uint32)2U)
#define MCAN_SIDFC_LSS_SHIFT_U32        ((uint32)16U)



/*==================================================================================================
         BIT MASKS FOR STANDARD ID EXTENDED CONFIGURATION REGISTER, : XIDFC (Base+0x0088)
==================================================================================================*/

#define MCAN_XIDFC_FLESA_SHIFT_U32      ((uint32)2U)
#define MCAN_XIDFC_LSE_SHIFT_U32        ((uint32)16U)



/*==================================================================================================
         BIT MASKS FOR EXTENDED ID AND MASK REGISTER, : XIDAM (Base+0x0090)
==================================================================================================*/

#define MCAN_XIDAM_EIDM_U32        ((uint32)0x1FFFFFFFU)



/*==================================================================================================
         BIT MASKS FOR HIGH PRIORITY MESSAGE STATUS REGISTER, : HPMS (Base+0x0094)
==================================================================================================*/

#define MCAN_HPMS_BIDX_U32        ((uint32)0x0000003FU)
#define MCAN_HPMS_MSI_U32         ((uint32)0x000000C0U)
#define MCAN_HPMS_FIDX_U32        ((uint32)0x00007F00U)
#define MCAN_HPMS_FLST_U32        ((uint32)0x00008000U)


/*==================================================================================================
         BIT MASKS FOR Rx FIFO 0 CONFIGURATION REGISTER, : RXF0C (Base+0x00A0)
         BIT MASKS FOR Rx FIFO 1 CONFIGURATION REGISTER, : RXF1C (Base+0x00B0)
==================================================================================================*/

#define MCAN_RXF0C_F0SA_SHIFT_U32    ((uint32)2U)
#define MCAN_RXF0C_F0S_SHIFT_U32     ((uint32)16U)
#define MCAN_RXF0C_F0WM_SHIFT_U32    ((uint32)24U)
#define MCAN_RXF0C_F0WM_MASK_U32     ((uint32)0x7F000000U)
#define MCAN_RXF1C_F1SA_SHIFT_U32    ((uint32)2U)
#define MCAN_RXF1C_F1S_SHIFT_U32     ((uint32)16U)
#define MCAN_RXF1C_F1WM_SHIFT_U32    ((uint32)24U)
#define MCAN_RXF1C_F1WM_MASK_U32     ((uint32)0x7F000000U)

/*==================================================================================================
         BIT MASKS FOR Rx FIFO 0 ACKNOWLEDGE REGISTER, : RXF0A (Base+0x00A8)
==================================================================================================*/

#define MCAN_RXF0A_F0AI_U32       ((uint32)0x0000003FU)



/*==================================================================================================
         BIT MASKS FOR Rx FIFO 0 STATUS REGISTER, : RXF0S (Base+0x00A4)
==================================================================================================*/

#define MCAN_RXF0S_F0FL_U32        ((uint32)0x0000007FU)
#define MCAN_RXF0S_F0GI_U32        ((uint32)0x00003F00U)
#define MCAN_RXF0S_F0GI_SHIFT_U32  ((uint32)8U)
#define MCAN_RXF0S_F0F_U32         ((uint32)0x01000000U)
#define MCAN_RXF0S_RF0L_U32        ((uint32)0x02000000U)





/*==================================================================================================
         BIT MASKS FOR Rx FIFO 1 STATUS REGISTER, : RXF1S (Base+0x00B4)
==================================================================================================*/

#define MCAN_RXF1S_F1FL_U32        ((uint32)0x0000007FU)
#define MCAN_RXF1S_F1GI_U32        ((uint32)0x00003F00U)
#define MCAN_RXF1S_F1GI_SHIFT_U32  ((uint32)8U)
#define MCAN_RXF1S_F1F_U32         ((uint32)0x01000000U)
#define MCAN_RXF1S_RF1L_U32        ((uint32)0x02000000U)
#define MCAN_RXF1S_DMS_U32         ((uint32)0xC0000000U)





/*==================================================================================================
         BIT MASKS FOR Rx FIFO 1 ACKNOWLEDGE REGISTER, : RXF1A (Base+0x00B8)
==================================================================================================*/

#define MCAN_RXF1A_F1AI_U32       ((uint32)0x0000003FU)

/*==================================================================================================
         BIT MASKS FOR Rx BUFFER CONFIGURATION REGISTER, : RXBC (Base+0x00AC)
==================================================================================================*/

#define MCAN_RXBC_RBSA_SHIFT_U32     ((uint32)2U)

/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXBC (Base+0x00B8)
==================================================================================================*/

#define MCAN_TXBC_TBSA_SHIFT_U32     ((uint32)2U)
#define MCAN_TXBC_NDTB_SHIFT_U32     ((uint32)16U)

/*==================================================================================================
         BIT MASKS FOR RXESC REGISTER
==================================================================================================*/
#define MCAN_RXESC_RBDS_MASK_U32     ((uint32)0x00000700U)  
#define MCAN_RXESC_RBDS_SHIFT_U32    ((uint32)8U)  
#define MCAN_RXESC_F0DS_MASK_U32     ((uint32)0x00000007U)  
#define MCAN_RXESC_F0DS_SHIFT_U32    ((uint32)0U)  
#define MCAN_RXESC_F1DS_MASK_U32     ((uint32)0x00000070U) 
#define MCAN_RXESC_F1DS_SHIFT_U32    ((uint32)4U)  
/*==================================================================================================
         BIT MASKS FOR TXESC REGISTER
==================================================================================================*/
#define MCAN_TXESC_TBDS_SHIFT_U32  ((uint32)0U)



/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXFQS
==================================================================================================*/



/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXBAR
==================================================================================================*/




/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXBCR
==================================================================================================*/





/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXBTIE
==================================================================================================*/



/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXBCIE
==================================================================================================*/



/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXBTO
==================================================================================================*/


/*==================================================================================================
         BIT MASKS FOR Tx BUFFER CONFIGURATION REGISTER, : TXBCF
==================================================================================================*/
/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/
#define MCAN_MB_TXBCF_READ(offset,mbindex)   ((uint32)(REG_READ32( MCAN_TXBCF(offset)) & (uint32)((uint32)(1U) << (uint32)(mbindex))) )

/*==================================================================================================
         SRAM
==================================================================================================*/
#define MCAN_MB_TYPE_XTD_U32            0x40000000U
#define MCAN_MB_TYPE_STD_U32            0x1FFC0000U
#define MCAN_MB_RTR_MASK_U32           0x20000000U

#define MCAN_TX_MB_ID_MASK_U32         0x1FFFFFFFU
#define MCAN_TX_MB_XTD_MASK_U32        0x40000000U
#define MCAN_TX_MB_DLC_MASK_U32        0x000F0000U
#define MCAN_TX_MB_DLC_FD_MASK_U32     0x003F0000U
#define MCAN_TX_MB_DLC_SHIFT_U32       ((uint32)16U)
#define MCAN_FD_WITH_BITRATE_SWITCHING_U32      (0x00300000U)
#define MCAN_FD_WITHOUT_BITRATE_SWITCHING_U32   (0x00200000U)
#define MCAN_CLASSIC_U32                        (0x00000000U)

#define MCAN_RX_MB_FIDX_MASK_U32       0x7F000000U
#define MCAN_RX_MB_ANMF_MASK_U32       0x80000000U
#define MCAN_RX_MB_ID_MASK_U32         0x1FFFFFFFU
#define MCAN_RX_MB_XTD_MASK_U32        0x40000000U
#define MCAN_RX_MB_DLC_MASK_U32        0x000F0000U
#define MCAN_RX_MB_DLC_SHIFT_U32       ((uint32)16U)

#define MCAN_WARNING_MASK_U32          0x00000040U
#define MCAN_EDL_MASK_U32              0x00200000U

#define MCAN_RANGE_FILTER_U8         0x00U
#define MCAN_DUAL_ID_FILTER_U8       0x01U
#define MCAN_CLASSIC_FILTER_U8       0x02U

#define MCAN_STORE_RX_FIFO0_U8       0xFCU
#define MCAN_STORE_RX_FIFO1_U8       0xFDU
#define MCAN_STORE_TX_BUFFER_U8      0xFFU

/*==================================================================================================
         STANDARD MESSAGE ID FILTER ELEMENT
==================================================================================================*/

#define MCAN_SRAM_STD_FTR_LENGTH_U32    ((uint32)4U)
#define MCAN_SRAM_EXD_FTR_LENGTH_U32    ((uint32)8U)

/*==================================================================================================
         EXTENDED MESSAGE ID FILTER ELEMENT
==================================================================================================*/

/*
* @violates @ref Reg_eSys_MCan_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
*/

#define MCAN_SRAM_SMIDFE_SFID2_MASK_U32      0x000007FFU
#define MCAN_SRAM_SMIDFE_SFID1_MASK_U32      0x07ff0000U
#define MCAN_SRAM_SMIDFE_SFID1_SHIFT_U32    ((uint32)16U)
#define MCAN_SRAM_SMIDFE_SFEC_MASK_U32       0x38000000U
#define MCAN_SRAM_SMIDFE_SFEC_SHIFT_U32     ((uint32)27U)
#define MCAN_SRAM_SMIDFE_SFT_MASK_U32        0xC0000000U
#define MCAN_SRAM_SMIDFE_SFT_SHIFT_U32      ((uint32)30U)
#define MCAN_SRAM_EMIDFE_EFID_MASK_U32       0x1FFFFFFFU
#define MCAN_SRAM_EMIDFE_EFEC_MASK_U32       0xE0000000U
#define MCAN_SRAM_EMIDFE_EFEC_SHIFT_U32     ((uint32)29U)
#define MCAN_SRAM_EMIDFE_EFT_SHIFT_U32      ((uint32)30U)
#define MCAN_SRAM_EMIDFE_EFT_MASK_U32        0xC0000000U
#define MCAN_RXFIFO0_OVFL_MASK_U32           0x0000000CU
#define MCAN_RXFIFO1_OVFL_MASK_U32           0x000000C0U



/*==================================================================================================
*                                          TX MESSAGE BUFFERS
==================================================================================================*/




/*==================================================================================================
*                                          RECEIVE FIFO 0
==================================================================================================*/



/*==================================================================================================
*                                          RECEIVE FIFO 1
==================================================================================================*/



/*==================================================================================================
*                                          RECEIVE Rx BUFFER
==================================================================================================*/



/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
#define CAN_43_MCAN_START_SEC_CONST_UNSPECIFIED
/* @violates @ref Reg_eSys_MCan_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */

#include "MemMap.h"

#define CAN_43_MCAN_STOP_SEC_CONST_UNSPECIFIED
/*
* @violates @ref Reg_eSys_MCan_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/

#include "MemMap.h"


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_OFF)
#define CAN_43_MCAN_START_SEC_CONFIG_DATA_UNSPECIFIED
/*
* @violates @ref Reg_eSys_MCan_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

#define CAN_43_MCAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/*
* @violates @ref Reg_eSys_MCan_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"
#endif

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define CAN_43_MCAN_START_SEC_CODE
/*
* @violates @ref Reg_eSys_MCan_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

#define CAN_43_MCAN_STOP_SEC_CODE
/*
* @violates @ref Reg_eSys_MCan_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /*TEMPLATE_H*/

/** @} */
