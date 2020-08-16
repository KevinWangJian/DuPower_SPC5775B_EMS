/**
*   @file    Can_Mcan.h
*   @implements MCan.h_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR MCan - MCan module interface.
*   @details Low Level Driver header file for IPV = FlexCan.
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


#ifndef CAN_MCAN_H
#define CAN_MCAN_H


#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section  MCan_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
* @section MCan_h_REF_4
* Violates MISRA 2004 Required Rule 8.8, An external object and funtion shall declared in one and only one file.
* Tools wrongly reported this case.
*
* @section MCan_h_REF_5
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section MCan_h_REF_8
* Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to a braced initialiser, a constant, a
* parenthesised expression, a type qualifier, a storage class specifier, or a do-while-zero construct
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the significance
* of more than 31 characters.
* The long identifiers are maintained for better readability.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*  (CAN222) Imported types: Dem_Types.h, CanIf_Types.h, Std_Types.h, ComStack_Types.h */
/*
* @file           Can_Mcan.h
*/
#include "StdRegMacros.h"
#include "Reg_eSys_MCan.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Can_Mcan.h
*/
#define CAN_VENDOR_ID_MCAN_H                    43
#define CAN_MODULE_ID_MCAN_H                    80
#define CAN_AR_RELEASE_MAJOR_VERSION_MCAN_H     4
#define CAN_AR_RELEASE_MINOR_VERSION_MCAN_H     0
#define CAN_AR_RELEASE_REVISION_VERSION_MCAN_H  3
#define CAN_SW_MAJOR_VERSION_MCAN_H             1
#define CAN_SW_MINOR_VERSION_MCAN_H             0
#define CAN_SW_PATCH_VERSION_MCAN_H             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
extern CONST(uint8, CAN_43_MCAN_CONST) Can_Mcan_u8RealPayloadData[8U];
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/**
* @brief          Can_HandleType
* @details        Used for value received by Tressos interface configuration.
*                 Controller does not provide any bit field to differentiate BASIC-CAN & FULL-CAN.
*                 Controller does not provide any bit field to differentiate BASIC-CAN & FULL-CAN.
*
*/
typedef enum
    {
        CAN_43_MCAN_BASIC = 0U,    /*< @brief Basic-CAN device functions */
        CAN_43_MCAN_FULL           /*< @brief Full-CAN device functions */
    } Can_43_MCAN_HandleType;


/**
* @brief          CAN Interrupts state.
* @details        CAN Interrupts state.
*
*/
typedef enum
    {
        CAN_43_MCAN_INTERRUPT_DISABLED = 0U,  /*< @brief Interrupts disabled */
        CAN_43_MCAN_INTERRUPT_ENABLED         /*< @brief Interrupts enabled */

    } Can_43_MCAN_InterruptStateType;

/**
* @brief          CAN Share Ram initialized state.
* @details        CAN Share Ram initialized state.
*
*/
typedef enum
    {
        MCAN_SRAM_UNINITIALIZED = 0U,  /*< @brief Share ram uninitialized */
        MCAN_SRAM_INITIALIZED        /*< @brief Share ram initialized */

    } Can_SramStateType;



/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          Records the status of a CAN Controller during runtime.
* @details        Records the status of a CAN Controller during runtime.
*
* @note           This structure is not configured by Tresos.
*/
typedef struct
    {
        /*< @brief Guard bits for EXCLUSIVE ACCESS to Tx MBs */
        VAR(uint32, CAN_43_MCAN_VAR)         u32TxGuard;
        /*< @brief Pre-calculated MB INT masks (used in Can_EnableControllerInterrupts) */
        VAR(uint32, CAN_43_MCAN_VAR)         u32MBInterruptMask;
        /*< @brief Storage space for PDU_ID (supplied in call to Can_Write and needed after Tx in CanIf_TxConfirmation) */
        VAR(PduIdType, CAN_43_MCAN_VAR)      u32TxPduId[CAN_43_MCAN_MAX_TX_MB_CONFIG];
        /*< @brief Storage space for Can_DisableControllerInterrupts nesting level */
        volatile VAR(sint8, CAN_43_MCAN_VAR) s8IntDisableLevel;
        /*< @brief Index of MB buffer being cancelled. */
        volatile VAR(Can_HwHandleType, CAN_43_MCAN_VAR) u32CancelMBIndex;
        /*< @brief Global interrupt autorization state */
        VAR(Can_43_MCAN_InterruptStateType, CAN_43_MCAN_VAR) eInterruptMode; /*< @brief Global interrupt autorization state */
        /*< @brief MCAN controller power state */
        VAR(Can_43_MCAN_ControllerStateType, CAN_43_MCAN_VAR) ControllerState;
        /*< @brief Map for every MB the HOH assigned according to configuration. */
        VAR(uint32, CAN_43_MCAN_VAR)         u32MbTxMapping[CAN_43_MCAN_MAX_TX_MB_CONFIG];
        /*< @brief Current controller baudrate */
        VAR(uint8, CAN_43_MCAN_VAR)          u8CurrentBaudRateIndex;
        
        VAR(uint32, CAN_43_MCAN_VAR)         Tx_complete_guard;
    } Can_43_MCAN_ControllerStatusType;

typedef P2CONST( Can_43_MCAN_MBConfigContainerType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_DATA)   Can_43_MCAN_PtrMBConfigContainerType;
typedef P2CONST( Can_43_MCAN_ControlerDescriptorType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_DATA) Can_43_MCAN_PtrControlerDescriptorType;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define CAN_43_MCAN_START_SEC_VAR_NO_INIT_UNSPECIFIED
/*
* @violates @ref MCan_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"


/* @violates @ref MCan_h_REF_4 An external object or function shall be declared in one and only one file */
extern VAR(Can_43_MCAN_ControllerStatusType, CAN_43_MCAN_VAR) Can_43_MCAN_ControllerStatuses[CAN_43_MCAN_MAXCTRL_SUPPORTED];


#define CAN_43_MCAN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/*
* @violates @ref MCan_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define CAN_43_MCAN_START_SEC_CODE
/*
* @violates @ref MCan_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

FUNC (void, CAN_43_MCAN_CODE) Can_MCan_InitVariables( void);


FUNC (void, CAN_43_MCAN_CODE) Can_MCan_Init(VAR(uint8, AUTOMATIC) controller);


FUNC (Can_ReturnType, CAN_43_MCAN_CODE) Can_MCan_ResetController( VAR(uint8, AUTOMATIC) controller);


FUNC (void, CAN_43_MCAN_CODE) Can_MCan_ChangeBaudrate( VAR(uint8, AUTOMATIC) controller);

FUNC (Can_ReturnType, CAN_43_MCAN_CODE) Can_MCan_SetControllerMode( VAR(uint8, AUTOMATIC) controller,
                                                            P2CONST(Can_43_MCAN_ControlerDescriptorType, AUTOMATIC, CAN_43_MCAN_APPL_CONST) pCanControlerDescriptor,
                                                            VAR(Can_StateTransitionType, AUTOMATIC) Transition,
                                                            VAR(boolean, AUTOMATIC) canif_notification_required
                                                          );

FUNC (void, CAN_43_MCAN_CODE) Can_MCan_DisableControllerInterrupts( VAR(uint8, AUTOMATIC) controller );

FUNC (void, CAN_43_MCAN_CODE) Can_MCan_EnableControllerInterrupts( VAR(uint8, AUTOMATIC) controller,
                                                           P2CONST(Can_43_MCAN_ControlerDescriptorType, AUTOMATIC, CAN_43_MCAN_APPL_CONST) pCanControlerDescriptor
                                                         );


#if (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON)

FUNC (void, CAN_43_MCAN_CODE) Can_MCan_Cancel( VAR(uint8, AUTOMATIC) controller,
                                       VAR(uint8, AUTOMATIC) mbindex
                                     );

#endif /* (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON) */

#if ((CAN_43_MCAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON))

FUNC(void, CAN_43_MCAN_CODE) Can_MCan_AbortMb( VAR(Can_HwHandleType, AUTOMATIC) Hth );

#endif


FUNC (Can_ReturnType, CAN_43_MCAN_CODE) Can_MCan_Write( Can_HwHandleType Hth,
                                                P2CONST(Can_PduType, AUTOMATIC, CAN_43_MCAN_APPL_CONST) PduInfo
                                              );


FUNC (void, CAN_43_MCAN_CODE) Can_MCan_ProcessTx( CONST(uint8, AUTOMATIC) controller,
                                          CONST(uint8, AUTOMATIC) mbindex_start,
                                          CONST(uint8, AUTOMATIC) mbindex_end
                                        );


FUNC (void, CAN_43_MCAN_CODE) Can_MCan_ProcessRx( CONST(uint8, AUTOMATIC) controller, CONST(uint8, AUTOMATIC) u8BufferID);
#if (CAN_43_MCAN_TXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_43_MCAN_CODE) Can_MCan_MainFunctionWrite( void);
FUNC (void, CAN_43_MCAN_CODE) Can_MCan_MainFunctionMultipleWritePoll( VAR(uint8, AUTOMATIC) writepoll);

#endif /* (CAN_43_MCAN_TXPOLL_SUPPORTED == STD_ON) */

#if (CAN_43_MCAN_RXPOLL_SUPPORTED == STD_ON)

FUNC (void, CAN_43_MCAN_CODE) Can_MCan_MainFunctionRead( void);
FUNC (void, CAN_43_MCAN_CODE) Can_MCan_MainFunctionMultipleReadPoll( VAR(uint8, AUTOMATIC) readpoll);

#endif /* (CAN_43_MCAN_RXPOLL_SUPPORTED == STD_ON) */


FUNC (void, CAN_43_MCAN_CODE) Can_MCan_ProcessBusOff( CONST(uint8, CAN_43_MCAN_CONST) controller);


FUNC (Std_ReturnType, CAN_43_MCAN_CODE) Can_MCan_CheckBusOff( VAR(uint8, AUTOMATIC) controller);


FUNC (void, CAN_43_MCAN_CODE) Can_MCan_MainFunctionMode( void);



#if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)

FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_MCan_SetClockMode( VAR(uint8, AUTOMATIC) u8Controller, VAR(Can_43_MCAN_ClockModeType, AUTOMATIC) can_clk_mode);

#endif /* CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON */

#ifdef CAN_43_MCAN_SUPPORT_MRAF_EVENT
  #if (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON)
    #if (CAN_43_MCAN_MRAFPOLL_SUPPORTED == STD_ON)
FUNC (void, CAN_43_MCAN_CODE) Can_MCan_MainFunction_CheckMRAF( void);
    #endif
  #endif /* (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_OFF) */
#endif /* defined(CAN_43_MCAN_SUPPORT_MRAF_EVENT) */
#ifdef ERR_IPV_MCAN_0002 
  #if (ERR_IPV_MCAN_0002 == STD_ON)
FUNC (void, CAN_43_MCAN_CODE) Can_MCan_DummyRead(VAR(uint8, AUTOMATIC) u8Controller);
  #endif
#endif

#if (STD_ON == CAN_43_MCAN_INTERRUPT_SUPPORTED)
FUNC (void, CAN_43_MCAN_CODE) Can_MCan_Isr_common_process_interrupt(CONST(uint8, CAN_43_MCAN_CONST) controller);

#endif

#define CAN_43_MCAN_STOP_SEC_CODE
/*
* @violates @ref MCan_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* CAN_MCAN_H */

/** @} */
