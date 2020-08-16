/**
*   @file    Reg_eSys_ESCI.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Lin
*   @details Header file for ESCI Registers and Macros Definitions
*
*   @addtogroup LIN
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : ESCI
*   Dependencies         : 
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
/*=================================================================================================
=================================================================================================*/

#ifndef REG_ESYS_ESCI_H
#define REG_ESYS_ESCI_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Reg_eSys_ESCI_h_REF_1
* Violates MISRA 2004 Required Rule 20.2, Re-use of C90 reserved identifier
* This violation is due to the use of "_" which is required as per Autosar.
*
* @section Reg_eSys_ESCI_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Reg_eSys_ESCI_h_REF_3
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Reg_eSys_ESCI_h_REF_4
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,
* Precautions shall be taken in order to prevent the contents of a header file being included twice.
* This comes from the order of includes in the .c file and from include dependencies.
*
* @section Reg_eSys_ESCI_h_REF_5
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
* This is an Autosar memory management requirement.
*
* @section Reg_eSys_ESCI_h_REF_6
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters.
*
* @section Reg_eSys_ESCI_h_REF_7
* Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to
* a braced initializer, a constant, a string literal, a parenthesized expression,
* a type qualifier, a storage class specifier, or a do-while-zero construct.
*
* @section Reg_eSys_ESCI_h_REF_8
* Violates MISRA 2004 Required Rule 8.12, Array declared with unknown size.
*
* @section Reg_eSys_ESCI_h_REF_9
* Violates MISRA 2004 Required Rule 19.10, Within a definition of a function-like macro,
* the arguments shall be enclosed in parentheses.
*
* @section Reg_eSys_ESCI_h_REF_10
* Violates MISRA 2004 Required Rule 19.10, Within a definition of a function-like macro,
* the arguments shall be enclosed in parentheses.
*/

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/


/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @file           Reg_eSys_ESCI.h
*/

#define LIN_VENDOR_ID_REGESCI                    43
/*
* @violates @ref Reg_eSys_ESCI_h_REF_3 Identifier clash
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_6 Identifiers shall not rely on the significance of more than 31 characters.*/
#define LIN_AR_RELEASE_MAJOR_VERSION_REGESCI     4
/*
* @violates @ref Reg_eSys_ESCI_h_REF_3 Identifier clash
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_6 Identifiers shall not rely on the significance of more than 31 characters.*/
#define LIN_AR_RELEASE_MINOR_VERSION_REGESCI     0
/*
* @violates @ref Reg_eSys_ESCI_h_REF_3 Identifier clash
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_6 Identifiers shall not rely on the significance of more than 31 characters.*/
#define LIN_AR_RELEASE_REVISION_VERSION_REGESCI  3
#define LIN_SW_MAJOR_VERSION_REGESCI             1
#define LIN_SW_MINOR_VERSION_REGESCI             0
#define LIN_SW_PATCH_VERSION_REGESCI             1

/*=================================================================================================
                                       DEFINES AND MACROS
=================================================================================================*/
/**
* @brief        IPV_ESCI macro definition.
* @details      Specific define for IPV_ESCI V07.02.01.01 - platform Mamba.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_7 C macros shall only expand to a braced initializer, .. */
#define IPV_ESCI_07_02_01_01  0x07020101UL
/**
* @brief        IPV_ESCI macro definition.
* @details      Generic define for IPV_ESCI V.7.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_7 C macros shall only expand to a braced initializer, .. */
#define IPV_ESCI_07_00_00_00  0x07000000UL

/**
* @brief        IPV_ESCI macro definition.
* @details      Generic define for IPV_ESCI V.8.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_7 C macros shall only expand to a braced initializer, .. */
#define IPV_ESCI_08_00_00_00  0x08000000UL

/* IPV_ESCI shall be defined in Soc_Ips.h file with the appropriate value                     */
/* because this convention started with Leopard and in order to keep the backward compatibility  */
/* the following 3 lines defines the default value for IPV_ESCI                                */
/* the only rule you need to follow is to include Soc_Ips.h before Reg_eSys_ESCI.h in any     */
/* c source file                                                                                 */
#ifndef IPV_ESCI
    #error "IPV_ESCI not defined"
#endif
/* ========================IPV_ESCI macro definition========================================*/

#define LIN_START_SEC_CONST_32
/*
* @violates @ref Reg_eSys_ESCI_h_REF_4 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_5 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 /* @violates @ref Reg_eSys_ESCI_h_REF_8 Array declared with unknown size. */
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
extern CONST(uint32, LIN_CONST) ESCI_au32BaseAddrs[];

#define LIN_STOP_SEC_CONST_32
/*
* @violates @ref Reg_eSys_ESCI_h_REF_4 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_5 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
/**
* @brief        IPV_ESCI macro definition.
* @details      Macro to get base address of eSCI IPs.
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_9 Within a function-like macro, the arguments shall be enclosed in parentheses. */
/* @violates @ref Reg_eSys_ESCI_h_REF_7 C macros shall only expand to a braced initializer, .. */
#define LIN_GET_BASE_ADDRESS_U32(offset) ((uint32)( ESCI_au32BaseAddrs[(offset)] ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI Baud Rate Register (eSCI_BRR).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_BRR_ADDR32(offset)      ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x00uL))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI Control Register 1 (eSCI_CR1).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x02uL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI Control Register 2 (eSCI_CR2).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x04uL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI SCI Data Register (eSCI_SDR).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x06uL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI Interrupt Flag and Status Register 1 (eSCI_IFSR1).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x08uL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI Interrupt Flag and Status Register 2 (eSCI_IFSR2).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x0AuL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI LIN Control Register 1 (eSCI_LCR1).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x0CuL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI LIN Control Register 2 (eSCI_LCR2).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR2_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x0EuL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI LIN Transmit Register (eSCI_LTR).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x10uL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI LIN Receive Register (eSCI_LRR).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LRR_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x14uL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI LIN CRC Polynomial Register (eSCI_LPR).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LPR_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x18uL ))

/**
* @brief        IPV_ESCI Registers macro definition.
* @details      IPV_ESCI macro to access register eSCI Control Register 3 (eSCI_CR3).
*/
/*
* @violates @ref Reg_eSys_ESCI_h_REF_2 Function-like macro defined.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR3_ADDR32(offset)    ((uint32)((uint32)( ESCI_au32BaseAddrs[(offset)]) + 0x1AuL ))

/* eSCI REGISTERS BITS */

/*-----------------------------------------------------------------------------------------------*/
/*                                Baud Rate Register (eSCI_BRR) bits                             */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|     Reserved    |                         SBR                                                */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits.
* @details      Baud Rate Register (eSCI_BRR) bit masks.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_BRR_SBR_MASK_U16                ((uint16)0x1FFFU)

/**
* @brief        IPV_ESCI Registers bits.
* @details      Baud Rate Register Resetbit masks.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_BRR_RESET_MASK_U16              ((uint16)0x0004U)

/*-----------------------------------------------------------------------------------------------*/
/*                                    Control Register 1 (eSCI_CR1) bits                         */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|LOOPS|SDZR |RSRC | M   |WAKE | ILT | PE  | PT  | TIE |TCIE | RIE |ILIE | TE  | RE  | RWU | SBK*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Send Break Character bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_SBK_MASK_U16                ((uint16)0x0001U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Receiver Wake-Up Mode bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_RWU_MASK_U16                ((uint16)0x0002U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Receiver Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_RE_MASK_U16                 ((uint16)0x0004U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Transmitter Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_TE_MASK_U16                 ((uint16)0x0008U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Idle Line Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_ILIE_MASK_U16               ((uint16)0x0010U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Receiver Full Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_RIE_MASK_U16                ((uint16)0x0020U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Transmission Complete Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_TCIE_MASK_U16               ((uint16)0x0040U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Transmitter Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_TIE_MASK_U16                ((uint16)0x0080U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Parity Type bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_PT_MASK_U16                 ((uint16)0x0100U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Parity Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_PE_MASK_U16                 ((uint16)0x0200U)

#if (IPV_ESCI < IPV_ESCI_08_00_00_00)
/* eSCI V.7 specific code*/

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Idle Line Type bit mask (eSCI V.7).
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_ILT_MASK_U16        ((uint16)0x0400U)

#endif

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Receiver Wake-up Condition bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_WAKE_MASK_U16               ((uint16)0x0800U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Frame Format Mode bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_M_MASK_U16                  ((uint16)0x1000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Receiver Source Control bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_RSRC_MASK_U16               ((uint16)0x2000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Loop Mode Select bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_LOOPS_MASK_U16              ((uint16)0x8000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 1 bit masks.
* @details      Control Register 1 Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR1_RESET_MASK_U16              ((uint16)0x0000U)

/*-----------------------------------------------------------------------------------------------*/
/*                                   Control Register 2 (eSCI_CR2) bits                          */
/*-----------------------------------------------------------------------------------------------*/
/*-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*BIT 0|BIT 1|BIT 2|BIT 3 |BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*MDIS | FBR |BSTP |BERRIE|RXDMA|TXDMA|BRCL |TXDIR|BESM |BESTP|RXPOL|PMSK |ORIE |NFIE |FFIE |PFIE*/
/*-----|-----|-----|------|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Parity Error Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_PFIE_MASK_U16               ((uint16)0x0001U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Frame Error Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_FEIE_MASK_U16               ((uint16)0x0002U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Noise Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_NFIE_MASK_U16               ((uint16)0x0004U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Overrun Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_ORIE_MASK_U16               ((uint16)0x0008U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Parity Bit Masking bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_PMSK_MASK_U16               ((uint16)0x0010U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      RXD Pin polarity bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_RXPOL_MASK_U16              ((uint16)0x0020U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Transmit Stop on Bit Error bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_BESTP_MASK_U16              ((uint16)0x0040U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Fast Bit Error Detection Sample Mode bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_BESM_MASK_U16              ((uint16)0x0080U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      TXD pin output enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_TXDIR_MASK_U16              ((uint16)0x0100U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Break Character Length bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_BRCL_MASK_U16               ((uint16)0x0200U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Transmit DMA Control bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_TXDMA_MASK_U16              ((uint16)0x0400U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Receive DMA Control bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_RXDMA_MASK_U16              ((uint16)0x0800U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Bit Error Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_BERRIE_MASK_U16             ((uint16)0x1000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      DMA Stop on Bit Error or Physical Bus Error bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_BSTP_MASK_U16               ((uint16)0x2000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Fast Bit Error Detection bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_FBR_MASK_U16                ((uint16)0x4000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Module Disabled Mode bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_MDIS_MASK_U16               ((uint16)0x8000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 2 bit masks.
* @details      Control Register 2 Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR2_RESET_MASK_U16              ((uint16)0x2000U)

/*-----------------------------------------------------------------------------------------------*/
/*                            SCI Data Register (eSCI_SDR) bits                                  */
/*-----------------------------------------------------------------------------------------------*/
/*-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/
/*BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT 9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/
/* RN  |     |ERR  | 0   |     RD [11:8]        |RD[7]|            RD [6:0]                      */
/*-----| TN  |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/
/*     |     |     |     |     |    |      |     |TD[7]|            TD [6:0]                     */
/*-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----*/

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      Received / Transmit bits 6 to 0 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_RD_TD_6_0_MASK_U16          ((uint16)0x007FU)

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      Received / Transmit Bit 7 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_RD_TD_7_MASK_U16            ((uint16)0x0080U)

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      Received / Transmit bits 7 to 0 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_RD_TD_7_0_MASK_U16          ((uint16)0x00FFU)

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      Received Data [11:8] bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_RD_11_8_MASK_U16            ((uint16)0x0F00U)

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      Receive Error Bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_ERR_MASK_U16                ((uint16)0x2000U)

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      Transmit Most Significant Bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_TN_MASK_U16                 ((uint16)0x4000U)

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      Received Most Significant Bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_RN_MASK_U16                 ((uint16)0x8000U)

/**
* @brief        IPV_ESCI Registers bits - SCI Data Register bit masks.
* @details      SCI Data Register Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_SDR_RESET_MASK_U16              ((uint16)0x0000U)

/*-----------------------------------------------------------------------------------------------*/
/*      Interrupt Flag and Status Register 1 (eSCI_IFSR1) bits                                   */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|TDRE | TC  |RDRF |IDLE | OR  | NF  | FE  | PF  |     |     |DACT |BERR |WACT |LACT |TACT |RACT*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Receiver Active bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_RACT_MASK_U16             ((uint16)0x0001U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Transmitter Active bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_TACT_MASK_U16             ((uint16)0x0002U)

#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      LIN Active Flag bit mask (eSCI V.8).
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_LACT_MASK_U16             ((uint16)0x0004U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      LIN WAke-Up Active Flag bit mask (eSCI V.8).
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_WACT_MASK_U16             ((uint16)0x0008U)

#endif

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Bit Error Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_BERR_MASK_U16             ((uint16)0x0010U)

#if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
/* eSCI V.8 specific code*/

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      DMA Active Flag bit mask (eSCI V.8).
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_DACT_MASK_U16             ((uint16)0x0020U)

#endif

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Parity Error Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_PF_MASK_U16               ((uint16)0x0100U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Framing Error Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_FE_MASK_U16               ((uint16)0x0200U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Noise Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_NF_MASK_U16               ((uint16)0x0400U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Overrun Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_OR_MASK_U16               ((uint16)0x0800U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Idle Line Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_IDLE_MASK_U16             ((uint16)0x1000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Receive Data Register Full Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_RDRF_MASK_U16             ((uint16)0x2000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Transmit Complete Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_TC_MASK_U16               ((uint16)0x4000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Transmit Data Register Empty Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_TDRE_MASK_U16             ((uint16)0x8000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 1 bit masks.
* @details      Interrupt Flag and Status Register 1 Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR1_RESET_MASK_U16            ((uint16)0xFF13U)

/*-----------------------------------------------------------------------------------------------*/
/*        Interrupt Flag and Status Register 2 (eSCI_IFSR2) bits                                 */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|RXRDY|TXRDY|LWAKE| STO |PBERR|CERR |CKERR| FRC |     |     |     |     |     |     |UREQ |OVFL*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Overflow Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_OVFL_MASK_U16             ((uint16)0x0001U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Unrequested Data Received Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_UREQ_MASK_U16             ((uint16)0x0002U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Frame Complete Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_FRC_MASK_U16              ((uint16)0x0100U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Checksum Error Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_CKERR_MASK_U16            ((uint16)0x0200U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      CRC Error Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_CERR_MASK_U16             ((uint16)0x0400U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Physical Bus Error Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_PBERR_MASK_U16            ((uint16)0x0800U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Slave Timeout Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_STO_MASK_U16              ((uint16)0x1000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      LIN Wakeup Received Interrupt Flag Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_LWAKE_MASK_U16            ((uint16)0x2000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Transmit Data Ready Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_TXRDY_MASK_U16            ((uint16)0x4000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Receive Data Ready Interrupt Flag bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_RXRDY_MASK_U16            ((uint16)0x8000U)

/**
* @brief        IPV_ESCI Registers bits - Interrupt Flag and Status Register 2 bit masks.
* @details      Interrupt Flag and Status Register 2 Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_IFSR2_RESET_MASK_U16            ((uint16)0xFF03U)

/*-----------------------------------------------------------------------------------------------*/
/*            LIN Control Register 1 (eSCI_LCR1) bits                                            */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|LRES | WU  |    WUD    |     |     |PRTY | LIN |RXIE |TXIE |WUIE |STIE |PBIE | CIE |CKIE |FCIE*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      Frame Complete Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_FCIE_MASK_U16              ((uint16)0x0001U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      Checksum Error Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_CKIE_MASK_U16              ((uint16)0x0002U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      CRC Error Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_CIE_MASK_U16               ((uint16)0x0004U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      Physical Bus Error Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_PBIE_MASK_U16              ((uint16)0x0008U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      Slave Timeout Flag Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_STIE_MASK_U16              ((uint16)0x0010U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Wakeup Received Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_WUIE_MASK_U16              ((uint16)0x0020U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      Transmit Data Ready Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_TXIE_MASK_U16              ((uint16)0x0040U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      Receive Data Ready Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_RXIE_MASK_U16              ((uint16)0x0080U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Mode Control bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_LIN_MASK_U16               ((uint16)0x0100U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      Parity Generation Control bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_PRTY_MASK_U16              ((uint16)0x0200U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Bus Wake-Up Delimiter Time 4 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_WUD_FOUR_BIT_MASK_U16      ((uint16)0x0000U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Bus Wake-Up Delimiter Time 8 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
/* @violates @ref Reg_eSys_ESCI_h_REF_6 Identifiers shall not rely on the significance of more than 31 characters.*/
#define ESCI_LCR1_WUD_EIGHT_BIT_MASK_U16     ((uint16)0x1000U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Bus Wake-Up Delimiter Time 32 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
/* @violates @ref Reg_eSys_ESCI_h_REF_6 Identifiers shall not rely on the significance of more than 31 characters.*/
#define ESCI_LCR1_WUD_THIRTY_TWO_BIT_MASK_U16       ((uint16)0x2000U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Bus Wake-Up Delimiter Time 64 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
/* @violates @ref Reg_eSys_ESCI_h_REF_6 Identifiers shall not rely on the significance of more than 31 characters.*/
#define ESCI_LCR1_WUD_SIXTY_FOUR_BIT_MASK_U16       ((uint16)0x3000U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Bus Wake-Up Trigger bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_WU_MASK_U16                ((uint16)0x4000U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Protocol Engine Reset Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_LRES_MASK_U16              ((uint16)0x8000U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 1 bits masks.
* @details      LIN Control Register 1 Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR1_RESET_MASK_U16             ((uint16)0x0000U)






/*-----------------------------------------------------------------------------------------------*/
/*        LIN Control Register 2 (eSCI_LCR2) bits                                                */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|     |     |     |     |     |     |UQIE |OFIE |     |     |     |     |     |     |     |    */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 2 bits masks.
* @details      Unrequested Data Received Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR2_OFIE_MASK_U16              ((uint16)0x0100U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 2 bits masks.
* @details      Overflow Interrupt Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR2_UQIE_MASK_U16              ((uint16)0x0200U)

/**
* @brief        IPV_ESCI Registers bits - LIN Control Register 2 bits masks.
* @details      LIN Control Register 2 Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LCR2_RESET_MASK_U16             ((uint16)0x0000U)

/*----------------------------------------------------------*/
/* LIN Transmit Register(eSCI_LTR)- LIN TX frame generation */
/*----------------------------------------------------------*/
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |WRITE||BIT 7|BIT 6|BIT 5|BIT 4|BIT 3|BIT 2|BIT 1|BIT 0| */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |1st W||   P [1:0] |    ID [5:0]                       | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |2nd W||        LEN                                    | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |3rd W|| CSM | CSE | CRC |TD(1)|  TO (ignored)         | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |4th  W||        D                                     | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */



/*----------------------------------------------------------*/
/* LIN Transmit Register(eSCI_LTR)- LIN RX frame generation */
/*----------------------------------------------------------*/
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |WRITE||BIT 7|BIT 6|BIT 5|BIT 4|BIT 3|BIT 2|BIT 1|BIT 0| */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |1st W||   P [1:0] |    ID [5:0]                       | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |2nd W||        LEN                                    | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |3rd W|| CSM | CSE | CRC |TD(0)|  TO [11:8]            | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */
/* |4th  W||        TO [7:0]                              | */
/* |-----||-----|-----|-----|-----|-----|-----|-----|-----| */


/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Identifier bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_ID_MASK_U8                 ((uint8)0x3FU)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Identifier Parity bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_P_MASK_U8                  ((uint8)0xC0U)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Frame Length bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_LEN_MASK_U8                ((uint8)0xFFU)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Timeout Value bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_TO_11_8_MASK_U8            ((uint8)0x0FU)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Transfer Direction bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_TD_MASK_U8                 ((uint8)0x10U)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      CRC Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_CRC_MASK_U8                ((uint8)0x20U)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Checksum Enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_CSE_MASK_U8                ((uint8)0x40U)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Checksum Model bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_CSM_MASK_U8                ((uint8)0x80U)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      Transmit Data bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_TO_7_0_MASK_U8             ((uint8)0xFFU)

/**
* @brief        IPV_ESCI Registers bits - LIN Transmit Register bit masks.
* @details      LIN Transmit Register Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LTR_RESET_MASK_U8             ((uint8)0x00U)

/*---------------------------------------------------*/
/*   LIN Receive Register (eSCI_LRR) bits            */
/*---------------------------------------------------*/
/* |-----|-----|-----|-----|-----|-----|-----|-----| */
/* |BIT 7|BIT 6|BIT 5|BIT 4|BIT 3|BIT 2|BIT 1|BIT 0| */
/* |-----|-----|-----|-----|-----|-----|-----|-----| */
/* |           D [7:0]                             | */
/* |-----|-----|-----|-----|-----|-----|-----|-----| */

/**
* @brief        IPV_ESCI Registers bits - LIN Receive Register bit masks.
* @details      Receive Data bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LRR_D_MASK_U8                  ((uint8)0xFFU)

/**
* @brief        IPV_ESCI Registers bits - LIN Receive Register bit masks.
* @details      LIN Receive Register Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LRR_RESET_MASK_U8              ((uint8)0x00U)

/*-----------------------------------------------------------------------------------------------*/
/*          LIN CRC Polynomial Register (eSCI_LPR) bits                                          */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|                                         P [15:0]                                             */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - LIN CRC Polynomial Register bit masks.
* @details      Polynomial bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LPR_P_MASK_U16                  ((uint16)0x00FFU)

/**
* @brief        IPV_ESCI Registers bits - LIN CRC Polynomial Register bit masks.
* @details      LIN CRC Polynomial Register Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_LPR_RESET_MASK_U16              ((uint16)0xC599U)

/*-----------------------------------------------------------------------------------------------*/
/*              Control Register 3 (eSCI_CR3) bits                                               */
/*-----------------------------------------------------------------------------------------------*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|BIT 0|BIT 1|BIT 2|BIT 3|BIT 4|BIT 5|BIT 6|BIT 7|BIT 8|BIT9|BIT10|BIT11|BIT12|BIT13|BIT14|BIT15*/
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/
/*|     |     |     |SYNM |EROE |ERFE |ERPE | M2  |     |     |     |     |     |     |     |    */
/*|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|----*/

/**
* @brief        IPV_ESCI Registers bits - Control Register 3 bit masks.
* @details      Frame Format Mode 2 bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR3_M2_MASK_U16                 ((uint16)0x0100U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 3 bit masks.
* @details      ERR flag parity error enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR3_ERPE_MASK_U16               ((uint16)0x0200U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 3 bit masks.
* @details      ERR flag frame error enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR3_ERFE_MASK_U16               ((uint16)0x0400U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 3 bit masks.
* @details      ERR flag overrun enable bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR3_EROE_MASK_U16               ((uint16)0x0800U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 3 bit masks.
* @details      Synchronization Mode bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR3_SYNM_MASK_U16               ((uint16)0x1000U)

/**
* @brief        IPV_ESCI Registers bits - Control Register 3 bit masks.
* @details      Control Register 3 Reset bit mask.
*/
/* @violates @ref Reg_eSys_ESCI_h_REF_1 Re-use of C90 reserved identifier */
#define ESCI_CR3_RESET_MASK_U16              ((uint16)0x0000U)

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* REG_ESYS_ESCI_H */

/** @} */
