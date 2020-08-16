/**
*   @file    Eth_Ipw.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Eth driver implementation header file
*   @details Implementation of the AUTOSAR Ethernet driver
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

#ifndef ETH_IPW_H
    #define ETH_IPW_H
#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Eth_Ipw_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, #include statements should only be preceded
* by other preprocessor directives or comments.
* The usage of the MemMap.h file violates this advisory rule, but this
* mechanism is used to properly place the code and variables into their
* sections.
*
* @section Eth_Ipw_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file. Precautions shall be taken in
* order to prevent the contents of a header file being included twice. This is an approved violation
* of usage MemMap.h file used to create linkage sections.
*
* @section Eth_Ipw_h_REF_3
* Violates MISRA 2004 Required Rule 1.4, A compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers.
* Name length of the macros is unfortunately longer than 31 characters which is required by 
* the agreed macro format and cannot be changed. 
*
* @section Eth_Ipw_h_REF_4
* Violates MISRA 2004 Required Rule 5.1, Identifiers shall not rely on the significance of more
* than 31 characters. Name length of the macros is unfortunately longer than 31 characters 
* which is required by the agreed macros format and cannot be changed. 
*
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros,
* objects and functions shall not be reused. All defines starting with upper
* letter E are reserved for future use inside <error.h> header file.
* All module define options and enumerations are restricted by JDP coding rules
* 5.6 and 5.8 and must follow format <MSN>_<NAME> where MSN is equal to ETH.
* It was agreed that this violation will not be commented above each line but
* only in header of affected file.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Eth_Fec_Counters.h" /* Include the counter */
#include "Eth_Fec.h" /* Lower layer header */
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_VENDOR_ID_ETHIPW_H                    43
#define ETH_MODULE_ID_ETHIPW_H                    88
/** @violates @ref Eth_Ipw_h_REF_3 MISRA rule 1.4 
* @violates @ref Eth_Ipw_h_REF_4 MISRA rule 5.1 */
#define ETH_AR_RELEASE_MAJOR_VERSION_ETHIPW_H     4
/** @violates @ref Eth_Ipw_h_REF_3 MISRA rule 1.4 
* @violates @ref Eth_Ipw_h_REF_4 MISRA rule 5.1 */
#define ETH_AR_RELEASE_MINOR_VERSION_ETHIPW_H     0
/** @violates @ref Eth_Ipw_h_REF_3 MISRA rule 1.4 
* @violates @ref Eth_Ipw_h_REF_4 MISRA rule 5.1 */
#define ETH_AR_RELEASE_REVISION_VERSION_ETHIPW_H  3
#define ETH_SW_MAJOR_VERSION_ETHIPW_H             1
#define ETH_SW_MINOR_VERSION_ETHIPW_H             0
#define ETH_SW_PATCH_VERSION_ETHIPW_H             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and ETH configuration header file are of the same vendor */
#if (ETH_VENDOR_ID_ETHIPW_H != ETH_VENDOR_ID_CFG)
#error "Eth_Ipw.h and Eth_Cfg.h have different vendor ids"
#endif
/* Check if current file and ETH configuration header file are of the same Autosar version */
#if ((ETH_AR_RELEASE_MAJOR_VERSION_ETHIPW_H != ETH_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (ETH_AR_RELEASE_MINOR_VERSION_ETHIPW_H != ETH_AR_RELEASE_MINOR_VERSION_CFG) || \
     (ETH_AR_RELEASE_REVISION_VERSION_ETHIPW_H != ETH_AR_RELEASE_REVISION_VERSION_CFG))
#error "AutoSar Version Numbers of Eth_Ipw.h and Eth_Cfg.h are different"
#endif
/* Check if current file and ETH configuration header file are of the same software version */
#if ((ETH_SW_MAJOR_VERSION_ETHIPW_H != ETH_SW_MAJOR_VERSION_CFG) || \
     (ETH_SW_MINOR_VERSION_ETHIPW_H != ETH_SW_MINOR_VERSION_CFG) || \
     (ETH_SW_PATCH_VERSION_ETHIPW_H != ETH_SW_PATCH_VERSION_CFG))
#error "Software Version Numbers of Eth_Ipw.h and Eth_Cfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/
/* Enable function for platform has only one IRQ src */
#define ETH_COMBINED_IRQ_SCR   (STD_OFF)
/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

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
#define ETH_START_SEC_CODE
/**
 * @violates @ref Eth_Ipw_h_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Ipw_h_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"

/***************************************************************************
* Wrap of ENET functions    
***************************************************************************/
extern FUNC(void, ETH_CODE) Eth_Ipw_ResetController(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Ipw_CheckAccessToController(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Ipw_ConfigureController(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Ipw_ClearCounters(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Ipw_ConfigureRxBuffers(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Ipw_ConfigureTxBuffers(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Ipw_EnableController(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(Eth_ModeType, ETH_CODE) Eth_Ipw_CheckControllerIsActive(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(uint32, ETH_CODE) Eth_Ipw_GetPhysicalAddressLow(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(uint16, ETH_CODE) Eth_Ipw_GetPhysicalAddressHigh(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Ipw_SetPhysAddr  ( \
                CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr \
                                                    );
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
extern FUNC(void, ETH_CODE) Eth_Ipw_UpdatePhysAddrFilter ( \
                    CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                    P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr, \
                    VAR(Eth_FilterActionType, AUTOMATIC) eAction \
                                                         );
#endif
extern FUNC(void, ETH_CODE) Eth_Ipw_GetCounterState ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint16, AUTOMATIC) u16Counter, \
                        CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) pValue \
                                                    );
extern FUNC(boolean, ETH_CODE) Eth_Ipw_ProvideBufferDataArea( \
                                CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                                CONSTP2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pBufIdx, \
                                P2P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) pData, \
                                CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pLength \
                                                            );
extern FUNC(void, ETH_CODE) Eth_Ipw_Transmit    ( 
                            CONST(uint8, AUTOMATIC) u8CtrlIdx, 
                            CONST(uint8, AUTOMATIC) u8Buf, 
                            CONST(Eth_FrameType, AUTOMATIC) u16Type, 
                            CONST(uint16, AUTOMATIC) u16Length, 
                            CONST(boolean, AUTOMATIC) bConfirm, 
                            P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pDest 
#if STD_ON == ETH_BRIDGE_SUPPORT
                          , P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) pSource
#endif /* ETH_BRIDGE_SUPPORT  */
                                                );
extern FUNC(boolean, ETH_CODE) Eth_Ipw_IsTxBufLockedBT(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(uint8, AUTOMATIC) u8Buf);
#if STD_ON == ETH_CTRLENABLE_MII
extern FUNC(boolean, ETH_CODE) Eth_Ipw_WriteMii ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint8, AUTOMATIC) u8Trcv, \
                        CONST(uint8, AUTOMATIC) u8Reg, \
                        CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pData \
                                                );
extern FUNC(boolean, ETH_CODE) Eth_Ipw_ReadMii  ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint8, AUTOMATIC) u8Trcv, \
                        CONST(uint8, AUTOMATIC) u8Reg, \
                        CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pData \
                                                );
#endif /* ETH_CTRLENABLE_MII */
extern FUNC(void, ETH_CODE) Eth_Ipw_MainFunction(VAR(void, AUTOMATIC));
extern FUNC(void, ETH_CODE) Eth_Ipw_ClearRxInterruptFlag (CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(void, ETH_CODE) Eth_Ipw_ClearTxInterruptFlag (CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Ipw_IsTxInterruptFlagSet (CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Ipw_IsRxInterruptFlagSet (CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Ipw_IsTxInterruptEnabled (CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(boolean, ETH_CODE) Eth_Ipw_IsRxInterruptEnabled (CONST(uint8, AUTOMATIC) u8CtrlIdx);
#if STD_ON == ETH_DEV_ERROR_DETECT
extern FUNC(boolean, ETH_CODE) Eth_Ipw_TooLongFrameReceived (CONST(uint8, AUTOMATIC) u8CtrlIdx);
#endif
/***************************************************************************
* ETH_LLD Real Functions Prototypes
***************************************************************************/
extern FUNC(boolean, ETH_CODE) Eth_Ipw_ReportTransmission(CONST(uint8, AUTOMATIC) u8CtrlIdx);
extern FUNC(Eth_RxStatusType, ETH_CODE) Eth_Ipw_ReportReception(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(boolean, AUTOMATIC) bIrq);
extern FUNC(void, ETH_CODE) Eth_Ipw_DisableController(CONST(uint8, AUTOMATIC) u8CtrlIdx);

#define ETH_STOP_SEC_CODE
/**
 * @violates @ref Eth_Ipw_h_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Ipw_h_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"
#ifdef __cplusplus
}
#endif

#endif /* EHT_LLD_H */
/** @} */
