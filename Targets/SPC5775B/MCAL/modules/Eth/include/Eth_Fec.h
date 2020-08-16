/**
*   @file    Eth_Fec.h
*   @version 1.0.1
*
*   @brief   FEC controller interface header file
*   @details Implementation of the FEC controller interface for
*            the Ethernet driver
*
*   @addtogroup ETH_DRIVER
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : FEC
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
/*==================================================================================================
==================================================================================================*/
#ifndef ETH_FEC_H
#define ETH_FEC_H
#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Eth_Fec_h_REF_1
* Violates MISRA 2004 Required Rule 1.4, A compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers.
* Name length of the macro is unfortunately longer than 31 characters required by the agreed file
* template and cannot be changed. Authors of the template have not taken the MISRA rules into
* account.
*
* @section Eth_Fec_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file. Precautions shall be taken in
* order to prevent the contents of a header file being included twice. This is an approved violation
* of usage MemMap.h file used to create linkage sections.
*
* @section Eth_Fec_h_REF_3
* Violates MISRA 2004 Advisory Rule 19.1, #include statements should only be preceded
* by other preprocessor directives or comments.
* The usage of the MemMap.h file violates this advisory rule, but this
* mechanism is used to properly place the code and variables into their
* sections.
*
* @section Eth_Fec_h_REF_4
* Violates MISRA 2004 Required Rule 5.1,  Identifiers (internal and external)
* shall not rely on the significance of more than 31 characters.
* Name length of the macro is unfortunately longer than 31 characters required
* by the agreed file template and cannot be changed. Authors of the template
* have not taken the MISRA rules into account.
*
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros,
* objects and functions shall not be reused. All defines starting with upper
* letter E are reserved for future use inside <error.h> header file.
* All module define options and enumerations are restricted by JDP coding rules
* 5.6 and 5.8 and must follow format <MSN>_<NAME> where MSN is equal to ETH.
* It was agreed that this violation will not be commented above each line but
* only in header of affected file.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
   
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_VENDOR_ID_FEC                    43
#define ETH_MODULE_ID_FEC                    88
/** @violates @ref Eth_Fec_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_h_REF_4 MISRA rule 5.1 */
#define ETH_AR_RELEASE_MAJOR_VERSION_FEC     4
/** @violates @ref Eth_Fec_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_h_REF_4 MISRA rule 5.1 */
#define ETH_AR_RELEASE_MINOR_VERSION_FEC     0
/** @violates @ref Eth_Fec_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_h_REF_4 MISRA rule 5.1 */
#define ETH_AR_RELEASE_REVISION_VERSION_FEC  3
#define ETH_SW_MAJOR_VERSION_FEC             1
#define ETH_SW_MINOR_VERSION_FEC             0
#define ETH_SW_PATCH_VERSION_FEC             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and ETH configuration header file are of the same vendor */
#if (ETH_VENDOR_ID_FEC != ETH_VENDOR_ID_CFG)
#error "Eth_Fec.h and Eth_Cfg.h have different vendor ids"
#endif
/* Check if current file and ETH configuration header file are of the same Autosar version */
#if ((ETH_AR_RELEASE_MAJOR_VERSION_FEC != ETH_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (ETH_AR_RELEASE_MINOR_VERSION_FEC != ETH_AR_RELEASE_MINOR_VERSION_CFG) || \
     (ETH_AR_RELEASE_REVISION_VERSION_FEC != ETH_AR_RELEASE_REVISION_VERSION_CFG))
#error "AutoSar Version Numbers of Eth_Fec.h and Eth_Cfg.h are different"
#endif
/* Check if current file and ETH configuration header file are of the same software version */
#if ((ETH_SW_MAJOR_VERSION_FEC != ETH_SW_MAJOR_VERSION_CFG) || \
     (ETH_SW_MINOR_VERSION_FEC != ETH_SW_MINOR_VERSION_CFG) || \
     (ETH_SW_PATCH_VERSION_FEC != ETH_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Eth_Fec.h and Eth_Cfg.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
 /***************************************************************************
* Register Offsets Macros 
***************************************************************************/
#define FEC_EIR_ADDR16   0x0004U /**< Interrupt Event Register */
#define FEC_EIMR_ADDR16  0x0008U /**< Interrupt Mask Register */
#define FEC_RDAR_ADDR16  0x0010U /**< Receive Descriptor Active Register */
#define FEC_TDAR_ADDR16  0x0014U /**< Transmit Descriptor Active Register */
#define FEC_ECR_ADDR16   0x0024U /**< Ethernet Control Register */
#define FEC_MMFR_ADDR16  0x0040U /**< MII Management Frame Register */
#define FEC_MSCR_ADDR16  0x0044U /**< MII Speed Control Register */
#define FEC_MIBC_ADDR16  0x0064U /**< MIB Control/Status Register */
#define FEC_RCR_ADDR16   0x0084U /**< Receive Control Register */
#define FEC_TCR_ADDR16   0x00C4U /**< Transmit Control Register */
#define FEC_PALR_ADDR16  0x00E4U /**< MAC Address Low Register */
#define FEC_PAUR_ADDR16  0x00E8U /**< MAC Address Upper Register + Type Field */
#define FEC_OPD_ADDR16   0x00ECU /**< Opcode + Pause Duration Fields */
#define FEC_IAUR_ADDR16  0x0118U /**< Upper 32 bits of Individual Hash Table */
#define FEC_IALR_ADDR16  0x011CU /**< Lower 32 Bits of Individual Hash Table */
#define FEC_GAUR_ADDR16  0x0120U /**< Upper 32 bits of Group Hash Table */
#define FEC_GALR_ADDR16  0x0124U /**< Lower 32 bits of Group Hash Table */
#define FEC_TFWR_ADDR16  0x0144U /**< Transmit FIFO Watermark */
#define FEC_FRBR_ADDR16  0x014CU /**< FIFO Receive Bound Register */
#define FEC_FRSR_ADDR16  0x0150U /**< FIFO Receive FIFO Start Registers */
#define FEC_ERDSR_ADDR16 0x0180U /**< Pointer to Receive Descriptor Ring */
#define FEC_ETDSR_ADDR16 0x0184U /**< Transmit Buffer Descriptor Ring Start Reg. */
#define FEC_EMRBR_ADDR16 0x0188U /**< Receive Buffer Size Register */
/***************************************************************************
* Register Bits Macros 
***************************************************************************/
/* EIR register bits */
#define FEC_EIR_HBERR_U32 0x80000000U /* Heartbeat error */
#define FEC_EIR_BABR_U32  0x40000000U /* Babbling receive error */
#define FEC_EIR_BABT_U32  0x20000000U /* Babbling transmit error */
#define FEC_EIR_GRA_U32   0x10000000U /* Graceful stop complete */
#define FEC_EIR_TXF_U32   0x08000000U /* Transmit frame interrupt */
#define FEC_EIR_TXB_U32   0x04000000U /* Transmit buffer interrupt */
#define FEC_EIR_RXF_U32   0x02000000U /* Receive frame interrupt */
#define FEC_EIR_RXB_U32   0x01000000U /* Receive buffer interrupt */
#define FEC_EIR_MII_U32   0x00800000U /* MII interrupt */
#define FEC_EIR_EBERR_U32 0x00400000U /* Ethernet bus error */
#define FEC_EIR_LC_U32    0x00200000U /* Late collision */
#define FEC_EIR_RL_U32    0x00100000U /* Collision retry limit */
#define FEC_EIR_UN_U32    0x00080000U /* Transmit FIFO underrun */
#define FEC_EIR_ALL_U32   0xFFF80000U /* All bits */

/* EIR register bits for write-1-to-clear operations */
#define FEC_EIR_HBERR_W1C 0x80000000U /* Heartbeat error */
#define FEC_EIR_BABR_W1C  0x40000000U /* Babbling receive error */
#define FEC_EIR_BABT_W1C  0x20000000U /* Babbling transmit error */
#define FEC_EIR_GRA_W1C   0x10000000U /* Graceful stop complete */
#define FEC_EIR_TXF_W1C   0x08000000U /* Transmit frame interrupt */
#define FEC_EIR_TXB_W1C   0x04000000U /* Transmit buffer interrupt */
#define FEC_EIR_RXF_W1C   0x02000000U /* Receive frame interrupt */
#define FEC_EIR_RXB_W1C   0x01000000U /* Receive buffer interrupt */
#define FEC_EIR_MII_W1C   0x00800000U /* MII interrupt */
#define FEC_EIR_EBERR_W1C 0x00400000U /* Ethernet bus error */
#define FEC_EIR_LC_W1C    0x00200000U /* Late collision */
#define FEC_EIR_RL_W1C    0x00100000U /* Collision retry limit */
#define FEC_EIR_UN_W1C    0x00080000U /* Transmit FIFO underrun */
#define FEC_EIR_ALL_W1C   0xFFF80000U /* All bits */

/* EIMR register bits */
#define FEC_EIMR_HBERR_U32 0x80000000U /* Heartbeat error interrupt enable */
#define FEC_EIMR_BABR_U32  0x40000000U /* Babbling receive error int. enable */
#define FEC_EIMR_BABT_U32  0x20000000U /* Babbling transmit error int. enable */
#define FEC_EIMR_GRA_U32   0x10000000U /* Graceful stop complete int. enable */
#define FEC_EIMR_TXF_U32   0x08000000U /* Transmit frame int. enable */
#define FEC_EIMR_TXB_U32   0x04000000U /* Transmit buffer int. enable */
#define FEC_EIMR_RXF_U32   0x02000000U /* Receive frame int. enable */
#define FEC_EIMR_RXB_U32   0x01000000U /* Receive buffer int. enable */
#define FEC_EIMR_MII_U32   0x00800000U /* MII interrupt enable */
#define FEC_EIMR_EBERR_U32 0x00400000U /* Ethernet bus error interrupt enable */
#define FEC_EIMR_LC_U32    0x00200000U /* Late collision interrupt enable */
#define FEC_EIMR_RL_U32    0x00100000U /* Collision retry limit int. enable */
#define FEC_EIMR_UN_U32    0x00080000U /* Transmit FIFO underrun int. enable */
#define FEC_EIMR_ALL_U32   0xFFF80000U /* All bits */
/* RDAR register bit*/
#define FEC_RDAR_R_DES_ACTIVE_U32 0x01000000U /* Empty Rx buffer exists */
/* TDAR register bit*/
#define FEC_TDAR_X_DES_ACTIVE_U32 0x01000000U /* Empty Tx buffer exists */
/* ECR register bits */
#define FEC_ECR_ETHER_EN_U32 0x00000002U /* Enable the controller */
#define FEC_ECR_RESET_U32    0x00000001U /* Reset the controller */
/* MMFR register bitfield masks and default values */
#define FEC_MMFR_ST_U32      0xC0000000U /* Start of frame delimiter */
#define FEC_MMFR_OP_U32      0x30000000U /* Operation */
#define FEC_MMFR_PA_U32      0x0F800000U /* PHY address */
#define FEC_MMFR_RA_U32      0x007C0000U /* Register address */
#define FEC_MMFR_TA_U32      0x00030000U /* Turn around */
#define FEC_MMFR_DATA_U32    0x0000FFFFU /* Data */
#define FEC_MMFR_ST_VAL_U32  0x40000000U /* 802.3 compliant value for ST field 
                                            (22.2.4.5.3 in 2008 version) */
#define FEC_MMFR_OP_READ_U32 0x20000000U /* Operation "read" according to 802.3
                                             (22.2.4.5.4 in 2008 version) */
#define FEC_MMFR_OP_WRITE_U32 0x10000000U /* Operation "write" according to 
                                       802.3 (22.2.4.5.4 in 2008 version) */
#define FEC_MMFR_TA_VAL_U32  0x00020000U /* 802.3 compliant value for TA field
                                            (22.2.4.5.7 in 2008 version)  */
/* MSCR register bit mask and bitfield mask */
#define FEC_MSCR_DIS_PREAMBLE_U32 0x00000080U /* Disable preamble */
#define FEC_MCSR_MII_SPEED_U32    0x0000007EU /* Speed bitfield mask */ 
/* MIB register bits */
#define FEC_MIBC_MIB_DISABLE_U32  0x80000000U /* Disable/enable trigger*/
#define FEC_MIBc_MIB_IDLE_U32     0x40000000U /* Disable/enable indicator */
/* RCR register bits */
#define FEC_RCR_MAX_FL_U32   0x07FF0000U /* */
#define FEC_RCR_FCE_U32      0x00000020U /* */
#define FEC_RCR_BC_REJ_U32   0x00000010U /* Reject broadcast */
#define FEC_RCR_PROM_U32     0x00000008U /* Promiscuous mode */
#define FEC_RCR_MII_MODE_U32 0x00000004U /* */
#define FEC_RCR_DRT_U32      0x00000002U /* */
#define FEC_RCR_LOOP_U32     0x00000001U /* Loopback enable */
#define FEC_RCR_INIT_VAL_U32 0x05EE0001U /* Initial register value */
/* TCR register bits */
#define FEC_TCR_RFC_PAUSE_U32 0x00000010U /* Receive pause frame */
#define FEC_TCR_TFC_PAUSE_U32 0x00000008U /* Transmit pause frame trigger */ 
#define FEC_TCR_FDEN_U32      0x00000004U /* Full duplex enable */
#define FEC_TCR_HBC_U32       0x00000002U /* Heartbeat control */
#define FEC_TCR_GTS_U32       0x00000001U /* Graceful transmit stop */
/* PAUR register bitfields */
#define FEC_PAUR_PADDR2_U32   0xFFFF0000U
#define FEC_PAUR_TYPE_U32     0x0000FFFFU
#define FEC_PAUR_TYPE_INIT_VAL_U32 0x00008808U
/* OPD register bitfields */
#define FEC_OPD_OPCODE_U32    0xFFFF0000U
#define FEC_OPD_PAUSE_DUR_U32 0x0000FFFFU
/* TFWR register bitfield */
#define FEC_TFWR_X_WMRK_U32   0x00000003U
/* FRBR register bitfield */
#define FEC_FRBR_R_BOUND_U32  0x000003FCU
#define FEC_FRBR_RESERVED_U32 0x00000400U /* Reserved bit with value 1 */
/* FRSR register bitfield */
#define FEC_FRSR_R_FSTART_U32 0x000003FCU
#define FEC_FRSR_RESERVED_U32 0x00000400U /* Reserved bit with value 1 */
/* ERDSR register bitfield */
#define FEC_ERDSR_R_DES_START_U32 0xFFFFFFFCU
/* ETDSR register bitfield */
#define FEC_ETDSR_X_DES_START_U32 0xFFFFFFFCU
/* EMRBR register bitfield */
#define FEC_EMRBR_R_BUF_SIZE_U32  0x000007F0U
/***************************************************************************
* Buffer Descriptors Bits
***************************************************************************/
/* RX BDs */
#define FEC_RXBD_E_U32      0x80000000U /* Receive buffer empty */
#define FEC_RXBD_R01_U32    0x40000000U /* User bit 1*/
#define FEC_RXBD_W_U32      0x20000000U /* Last descriptor in the ring */
#define FEC_RXBD_RO2_U32    0x10000000U /* User bit 2 */
#define FEC_RXBD_L_U32      0x08000000U /* Last buffer in the received frame */
#define FEC_RXBD_M_U32      0x01000000U /* Frame received in promiscuous mode 
                               (would not be received if not promiscuous)*/
#define FEC_RXBD_BC_U32     0x00800000U /* Frame received as broadcast */
#define FEC_RXBD_MC_U32     0x00400000U /* Frame received as multicast but 
                                   not broadcast */
#define FEC_RXBD_LG_U32     0x00200000U /* Frame length violation */
#define FEC_RXBD_NO_U32     0x00100000U /* Non octet aligned frame */
#define FEC_RXBD_CR_U32     0x00040000U /* CRC error */
#define FEC_RXBD_OV_U32     0x00020000U /* FIFO overrun during reception */
#define FEC_RXBD_TR_U32     0x00010000U /* Frame was longer than 2047B and 
                                                therefore was truncated */
#define FEC_RXBD_LENGTH_U32 0x0000FFFFU /* Buffer length bitfield mask */
/* TX BDs */
#define FEC_TXBD_R_U32      0x80000000U /* Transmit buffer is ready for
                                        transmission (filled with data) */
#define FEC_TXBD_TO1_U32    0x40000000U /* User bit 1 */
#define FEC_TXBD_W_U32      0x20000000U /* Last descriptor in the ring */
#define FEC_TXBD_TO2_U32    0x10000000U /* User bit 2 */
#define FEC_TXBD_L_U32      0x08000000U /* Last buffer in the transmitted frame */
#define FEC_TXBD_TC_U32     0x04000000U /* Compute and append CRC to the frame */
#define FEC_TXBD_ABC_U32    0x02000000U /* Append the bad CRC to the frame */ 
#define FEC_TXBD_LENGTH_U32 0x0000FFFFU /* Buffer length bitfield mask */

/***************************************************************************
* TX Buffer Status Bits
***************************************************************************/
/** @brief    Status bit for TX buffer flags, TRUE -> buffer is locked */
#define FEC_TXB_LOCK_U8  (8U)
/** @brief    Status bit for TX buffer flags, TRUE -> TxConfirmation pending */
#define FEC_TXB_CONF_U8  (4U)
/** @brief    Status bit for TX buffer flags, TRUE -> buffer linked with BD */
#define FEC_TXB_LINK_U8  (2U)
/** @brief    Status bit for TX buffer flags, TRUE -> first buffer of frame */
#define FEC_TXB_FIRST_U8 (1U)

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/***************************************************************************
* Macros To Access Registers, MIB Counters, Buffers and their Descriptors
***************************************************************************/
/* No such macros */
 
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
/**
* @brief Type used to return receive buffer status
*/
typedef enum
{
    RX_BUF_EMPTY = 0,         /**< Buffer is empty */
    RX_BUF_SINGLE,            /**< Buffer is full and the received frame is within single buffer */
    RX_BUF_MULTI_UNFINISHED,  /**< Buffer is full but the frame reception has not been finished yet */
    RX_BUF_MULTI_FINISHED,    /**< Buffer is full and it is the last buffer in the row of buffers occupied by one frame */
    RX_BUF_OVERFLOW           /**< Some frame occupies all available buffers so there is no space to put its end */ 
} Eth_RxBufferType;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ETH_START_SEC_VAR_INIT_8
/** @violates @ref Eth_Fec_h_REF_3 MISRA rule 19.1 */
/** @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 */
#include "MemMap.h"



extern VAR(volatile uint8, ETH_VAR) Eth_u8ActiveTxBD[ETH_MAXCTRLS_SUPPORTED];
extern VAR(uint8, ETH_VAR) Eth_u8LockedBuffer[ETH_MAXCTRLS_SUPPORTED];
extern VAR(uint8, ETH_VAR) Eth_u8LockedTxBufCount[ETH_MAXCTRLS_SUPPORTED];
#define ETH_STOP_SEC_VAR_INIT_8
/** @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 */
#include "MemMap.h"

#define ETH_START_SEC_VAR_NO_INIT_8
/** @violates @ref Eth_Fec_h_REF_3 MISRA rule 19.1 */
/** @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 */
#include "MemMap.h"
#define ETH_STOP_SEC_VAR_NO_INIT_8
/** @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 */
#include "MemMap.h"


/** @violates @ref Eth_Fec_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_h_REF_4 MISRA rule 5.1 */
#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 */
#include "MemMap.h"
#if VARIANT_PRE_COMPILE != ETH_CONFIG_VARIANT /* Not used for pre-compile variant */
/** @violates @ref Eth_Fec_h_REF_5 MISRA rule 8.8 */
    extern P2CONST(Eth_ConfigType, ETH_VAR, ETH_APPL_CONST) Eth_InternalCfgPtr;
#endif /* VARIANT-PRE-COMPILE */
/** @violates @ref Eth_Fec_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_h_REF_4 MISRA rule 5.1 */
#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
/** 
* @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 
* @violates @ref Eth_Fec_h_REF_3 MISRA rule 19.1
*/
#include "MemMap.h"
/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define ETH_START_SEC_CODE
/** 
* @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 
* @violates @ref Eth_Fec_h_REF_3 MISRA rule 19.1
*/
#include "MemMap.h"
extern FUNC(void, ETH_CODE) Eth_Fec_ResetController(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Fec_CheckAccessToCtrl(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Fec_ReportTransmission(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(Eth_RxStatusType, ETH_CODE) Eth_Fec_ReportReception (CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(boolean, AUTOMATIC) bIrq);
extern FUNC(void, ETH_CODE) Eth_Fec_ClearMIBCounters(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Fec_ConfigureTxBuffers(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Fec_ConfigureRxBuffers(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Fec_ConfigureCtrl(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Fec_EnableController(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Fec_DisableController(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(Eth_ModeType, ETH_CODE) Eth_Fec_CheckCtrlIsActive(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(uint16, ETH_CODE) Eth_Fec_GetPhysAddressHigh(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(uint32, ETH_CODE) Eth_Fec_GetPhysAddressLow(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Fec_SetPhysAddr(CONST(uint8, AUTOMATIC) u8CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr);
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
    extern FUNC(void, ETH_CODE) Eth_Fec_UpdtePhysAddrFiltr  ( \
                            CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                            P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr, \
                            VAR(Eth_FilterActionType, AUTOMATIC) eAction \
                                                            );
#endif /* ETH_UPDATE_PHYS_ADDR_FILTER */
extern FUNC(void, ETH_CODE) Eth_Fec_ClearTxIrqFlag(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Fec_ClearRxIrqFlag(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Fec_IsTxIrqFlagSet(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Fec_IsRxIrqFlagSet(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Fec_IsTxIrqEnabled(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Fec_IsRxIrqEnabled(CONST(uint8, AUTOMATIC) u8CtrlIdx);
#if STD_ON == ETH_DEV_ERROR_DETECT
extern FUNC(boolean, ETH_CODE) Eth_Fec_TooLongFrmRcvd(CONST(uint8, AUTOMATIC) u8CtrlIdx);
#endif /* ETH_DEV_ERROR_DETECT */
extern FUNC(void, ETH_CODE) Eth_Fec_GetCounterState ( \
                    CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                    CONST(uint16, AUTOMATIC) u16Counter, \
                    CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) pValue \
                                                    );
extern FUNC(boolean, ETH_CODE) Eth_Fec_BorrowTxBuffer   ( \
                    CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                    CONSTP2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pBufIdx, \
                    P2P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) pBufPtr, \
                    CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pBufLength \
                                                        );
extern FUNC(boolean, ETH_CODE) Eth_Fec_IsTxBufLockedBT(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(uint8, AUTOMATIC) u8BufIdx);
extern FUNC(void, ETH_CODE) Eth_Fec_Transmit    ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint8, AUTOMATIC) u8BufIdx, \
                        CONST(Eth_FrameType, AUTOMATIC) u16EtherType, \
                        CONST(uint16, AUTOMATIC) u16Length, \
                        CONST(boolean, AUTOMATIC) bConfirm, \
                        P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pDest \
                                                );
    
#if STD_ON == ETH_CTRLENABLE_MII
    extern FUNC(boolean, ETH_CODE) Eth_Fec_DoMiiMMF ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint8, AUTOMATIC) u8Trcv, \
                        CONST(uint8, AUTOMATIC) u8Reg, \
                        CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pData, \
                        CONST(uint32, AUTOMATIC) u32Operation \
                                                    );
#endif /* ETH_CTRLENABLE_MII */
#define ETH_STOP_SEC_CODE
/** 
* @violates @ref Eth_Fec_h_REF_2 MISRA rule 19.15 
* @violates @ref Eth_Fec_h_REF_3 MISRA rule 19.1
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* ETH_FEC_LLD_H */
/** @} */
