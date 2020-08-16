/**
*   @file    Can_43_MCAN.h
*   @implements Can_43_MCAN.h_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR MCan - module interface.
*   @details API header for CAN driver.
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


#ifndef CAN_43_MCAN_H
#define CAN_43_MCAN_H

#ifdef __cplusplus
extern "C"{
#endif

/*
(CAN043) The file Can_43_MCAN.h contains the declaration of the Can module API.
(CAN037) The file Can_43_MCAN.h only contains 'extern' declarations of constants, global data, type definitions and services
            that are specified in the Can module SWS.
*/

/**
* @file           Can_43_MCAN.h
*/


/**
* @page misra_violations MISRA-C:2004 violations
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section Can_43_MCAN_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to the requirement that request to have empty APIs if polling is not used.
*
* @section Can_43_MCAN_h_REF_2
* Violates MISRA 2004 Required Rule 8.7, Global variables containing the generated configuration
* shall be defined in a separate source file and can't be defined inside a function although it is accessed
* by a single function.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Can_43_MCAN_h_REF_4
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
/**
* @file           Can_43_MCAN.h
*/
#include "ComStack_Types.h"
#include "Can_43_MCAN_Cfg.h"
#include "Can_GeneralTypes.h"
#include "Soc_Ips.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
    Internal micro-dependent versioning. Check of AUTOSAR & Vendor specification version.
*/
/**
* @{
* @file           Can_43_MCAN.h
*/
#define CAN_43_MCAN_VENDOR_ID                   43
#define CAN_43_MCAN_MODULE_ID                   80
#define CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION    4
#define CAN_43_MCAN_AR_RELEASE_MINOR_VERSION    0
#define CAN_43_MCAN_AR_RELEASE_REVISION_VERSION 3
#define CAN_43_MCAN_SW_MAJOR_VERSION            1
#define CAN_43_MCAN_SW_MINOR_VERSION            0
#define CAN_43_MCAN_SW_PATCH_VERSION            1
/**@}*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Can configuration header file are of the same vendor */
#if (CAN_43_MCAN_VENDOR_ID != CAN_43_MCAN_VENDOR_ID_CFG)
#error "Can_43_MCAN.h and Can_43_MCAN_Cfg.h have different vendor ids"
#endif
/* Check if current file and Can configuration header file are of the same Autosar version */
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION != CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION != CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_AR_RELEASE_REVISION_VERSION != CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_CFG_H))
  #error "AutoSar Version Numbers of Can_43_MCAN.h and Can_43_MCAN_Cfg.h are different"
#endif

/* Check if current file and CAN configuration header file are of the same software version */
#if ((CAN_43_MCAN_SW_MAJOR_VERSION != CAN_43_MCAN_SW_MAJOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_SW_MINOR_VERSION != CAN_43_MCAN_SW_MINOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_SW_PATCH_VERSION != CAN_43_MCAN_SW_PATCH_VERSION_CFG_H))
  #error "Software Version Numbers of Can_43_MCAN.h and Can_43_MCAN_Cfg.h are different"
#endif
/* Check if current file and CAN configuration header file are of the same software version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION != COMTYPE_AR_RELEASE_MAJOR_VERSION) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION != COMTYPE_AR_RELEASE_MINOR_VERSION) )
  #error "Software Version Numbers of Can_43_MCAN.h and ComStack_Types.h are different"
#endif
#endif


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @{
* @brief          Development errors.
* @details        (CAN104) The Can module shall be able to detect the following errors and exceptions depending on its configuration (development/production).
*                 (CAN026) Development Errors shall indicate errors that are caused by erroneous usage of the Can module API. This covers API
*                   parameter checks and call sequence errors.
*                 (CAN080) Development error values are of type uint8.
*
*/
#define CAN_43_MCAN_E_PARAM_POINTER      ((uint8)0x01U)
#define CAN_43_MCAN_E_PARAM_HANDLE       ((uint8)0x02U)
#define CAN_43_MCAN_E_PARAM_DLC          ((uint8)0x03U)
#define CAN_43_MCAN_E_PARAM_CONTROLLER   ((uint8)0x04U)
#define CAN_43_MCAN_E_UNINIT             ((uint8)0x05U)
#define CAN_43_MCAN_E_TRANSITION         ((uint8)0x06U)
#define CAN_43_MCAN_E_DATALOST           ((uint8)0x07U)
#define CAN_43_MCAN_E_DEFAULT            ((uint8)0x08U)

#define CAN_43_MCAN_E_PARAM_BAUDRATE     ((uint8)0x09U)
/**@}*/

/**
* @{
* @brief          Service ID (APIs) for Det reporting
* @details        Service ID (APIs) for Det reporting
*
*/
#define CAN_43_MCAN_SID_INIT                          ((uint8)0x00U)
#define CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE           ((uint8)0x01U)
#define CAN_43_MCAN_SID_SET_CONTROLLER_MODE           ((uint8)0x03U)
#define CAN_43_MCAN_SID_DISABLE_CONTROLLER_INTERRUPTS ((uint8)0x04U)
#define CAN_43_MCAN_SID_ENABLE_CONTROLLER_INTERRUPTS  ((uint8)0x05U)
#define CAN_43_MCAN_SID_WRITE                         ((uint8)0x06U)
#define CAN_43_MCAN_SID_GET_VERSION_INFO              ((uint8)0x07U)
#define CAN_43_MCAN_SID_MAIN_FUNCTION_READ            ((uint8)0x08U)
#define CAN_43_MCAN_SID_MAIN_FUNCTION_BUS_OFF         ((uint8)0x09U)
#define CAN_43_MCAN_SID_MAIN_FUNCTION_WAKEUP          ((uint8)0x0AU)
#define CAN_43_MCAN_SID_CBK_CHECK_WAKEUP              ((uint8)0x0BU)
#define CAN_43_MCAN_SID_MAIN_FUNCTION_MODE            ((uint8)0x0CU)
#define CAN_43_MCAN_SID_CHANGE_BAUDRATE               ((uint8)0x0DU)
#define CAN_43_MCAN_SID_CHECK_BAUDRATE                ((uint8)0x0EU)
#define CAN_43_MCAN_SID_SET_BAUDRATE                  ((uint8)0x0FU)
#define CAN_43_MCAN_SID_SETCLOCKMODE                  ((uint8)0x0FU)
#define CAN_43_MCAN_SID_ABORT_MB                      ((uint8)0x10U)

/**@}*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
#ifdef CAN_MSCAN_SPECIFIC
/**
* @brief          Can_43_MCAN_ObjType
* @details        Used for value received by Tressos interface configuration.
*                 Describe the MB configuration.
*
*/
typedef enum
    {
        CAN_43_MCAN_2_32_BITS_FILTER = 0U,   /**< @brief Receive MB */
        CAN_43_MCAN_4_16_BITS_FILTER,        /**< @brief Receive MB */
        CAN_43_MCAN_8_8_BITS_FILTER,         /**< @brief Receive MB */
        CAN_43_MCAN_FILTER_CLOSED            /**< @brief Receive MB */
    } Can_43_MCAN_AcceptanceType;
#endif

/**
* @brief          Can_43_MCAN_ObjType
* @details        Used for value received by Tressos interface configuration.
*                 Describe the MB configuration.
*
*/
typedef enum
    {
        CAN_43_MCAN_RECEIVE = 0U,   /**< @brief Receive MB */
        CAN_43_MCAN_TRANSMIT        /**< @brief Transmit MB */
    } Can_43_MCAN_ObjType;


/**
* @brief          Can_43_MCANIdType
* @details        Used for value received by Tressos interface configuration.
*                 Used to diferentiate Extended, Mixed or Standard Id type.
*
*/
typedef enum
    {
        CAN_43_MCAN_EXTENDED = 0U,  /**< @brief Extended ID (29 bits) */
        CAN_43_MCAN_STANDARD,       /**< @brief Standard ID (11 bits) */
        CAN_43_MCAN_MIXED           /**< @brief Mixed ID (29 bits) */
    } Can_43_MCANIdType;


/**
* @brief          Can_43_MCAN_StatusType
* @details        CAN Driver status used for checking and preventing double driver intialization.
*                 CAN_UNINIT = The CAN controller is not initialized. The CAN Controller is not participating on the CAN bus.
*                              All registers belonging to the CAN module are in reset state, CAN interrupts are disabled.
*                 CAN_READY = Controller has initialized: static variables, including flags;
*                             Common setting for the complete CAN HW unit; CAN controller specific settings for each CAN controller.
*
*/
typedef enum
    {
        CAN_43_MCAN_UNINIT = 0U, /**< @brief Driver not initialized */
        CAN_43_MCAN_READY       /**< @brief Driver ready */
    } Can_43_MCAN_StatusType;

/**
* @brief          CAN Controller states.
* @details        States that defines the controllers.
*
*/
typedef enum
    {
        CAN_43_MCAN_STOPPED = 0U, /**< @brief Controller in state STOPPED */
        CAN_43_MCAN_STARTED,      /**< @brief Controller in state STARTED */
        CAN_43_MCAN_SLEEPED       /**< @brief Controller in state SLEEPED */
    } Can_43_MCAN_ControllerStateType;

/**
* @brief          Can_43_MCAN_ClockModeType
* @details        CAN source clock selection used in Can_SetClockMode Non-Autosar API.
*
*/
typedef enum
    {
        CAN_43_MCAN_NORMAL = 0U, /**< @brief Standard configuration (default) */
        CAN_43_MCAN_ALTERNATE    /**< @brief Second configuration (special) */
    } Can_43_MCAN_ClockModeType;
   
/**
* @brief          Can_43_MCAN_FdType
* @details        Used for value received by Tressos interface configuration.
*                 Describe the MB payload.
*
*/
typedef enum
    {
        CAN_43_MCAN_8_BYTES_PAYLOAD =0U ,    /**< @maximum 8 bytes payload */
#ifdef CAN_43_MCAN_MCAN_SPECIFIC
  #if (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON)
        CAN_43_MCAN_12_BYTES_PAYLOAD,      /**< @maximum 16 bytes payload */
        CAN_43_MCAN_16_BYTES_PAYLOAD,    /**< @maximum 32 bytes payload */
        CAN_43_MCAN_20_BYTES_PAYLOAD,    /**< @maximum 64 bytes payload */
        CAN_43_MCAN_24_BYTES_PAYLOAD,    /**< @maximum 64 bytes payload */
        CAN_43_MCAN_32_BYTES_PAYLOAD,    /**< @maximum 64 bytes payload */
        CAN_43_MCAN_48_BYTES_PAYLOAD,    /**< @maximum 64 bytes payload */
  #else
    #error undefine IPV
  #endif
#else
        CAN_43_MCAN_16_BYTES_PAYLOAD,      /**< @maximum 16 bytes payload */
        CAN_43_MCAN_32_BYTES_PAYLOAD,    /**< @maximum 32 bytes payload */
#endif
        CAN_43_MCAN_64_BYTES_PAYLOAD     /**< @maximum 64 bytes payload */
    } Can_43_MCAN_FdType;

#ifdef CAN_43_MCAN_MCAN_SPECIFIC
 typedef enum
     {
        CAN_43_MCAN_FIFO_0,
        CAN_43_MCAN_FIFO_1
     } Can_43_MCAN_FIFOChannelType;
#endif

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          Configuration of FlexCAN controller.
* @details        This structure is initialized by Tresos considering user settings.
*                 Used by Can_ChangeBaudrate() API to set the default baudrate after initialization.
*                 and to change the baudrate when the FlexCAN is in stopped mode.
*
*/
#if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
typedef struct
    {
        CONST(uint32, CAN_43_MCAN_CONST) u32CanFdEnable;
        CONST(uint32, CAN_43_MCAN_CONST) u32CanFdBaudRate;
        CONST(uint32, CAN_43_MCAN_CONST) u32CanFdCbtRegister;
        CONST(uint32, CAN_43_MCAN_CONST) u32CanControllerTrcvDelayCompensation;
		CONST(boolean,CAN_43_MCAN_CONST) CanControllerTrcvDelayEnabled;
        CONST(uint32, CAN_43_MCAN_CONST) u32CanControllerTxBitRateSwitch;
#if !(defined(CAN_43_MCAN_MCAN_SPECIFIC) || defined(CAN_MSCAN_SPECIFIC))
        #if ( (CAN_43_MCAN_CONTROLLER_FD_ISO_CANFD == STD_ON) || (CAN_43_MCAN_CONTROLLER_FD_PREXCEN == STD_ON) || (CAN_43_MCAN_CONTROLLER_FD_EDFLTDIS == STD_ON))
            CONST(uint32, CAN_43_MCAN_CONST) u32CanFdCTRL2Register;
        #endif
#endif
    } Can_43_MCAN_ControllerFdConfigType;
#endif



/**
* @brief          Configuration of FlexCAN controller.
* @details        This structure is initialized by Tresos considering user settings.
*                 Used by Can_ChangeBaudrate() API to set the default baudrate after initialization.
*                 and to change the baudrate when the FlexCAN is in stopped mode.
*
*/
#if (CAN_43_MCAN_CBT_ENABLE == STD_ON)
typedef struct
    {
        CONST(uint32, CAN_43_MCAN_CONST) u32CanCbtEnable;
        CONST(uint32, CAN_43_MCAN_CONST) u32CanCbtBaudRate;
        CONST(uint32, CAN_43_MCAN_CONST) u32CanCbtRegister;


    } Can_43_MCAN_ControllerCbtConfigType;
#endif
/**
* @brief          Configuration of FlexCAN controller.
* @details        This structure is initialized by Tresos considering user settings.
*                 Used by Can_ChangeBaudrate() API to set the default baudrate after initialization.
*                 and to change the baudrate when the FlexCAN is in stopped mode.
*
*/
typedef struct
    {
#ifndef CAN_MSCAN_SPECIFIC        
        CONST(uint32, CAN_43_MCAN_CONST) u32ControlRegister; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
#else        
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u8CanBtr0Register; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
        
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u8CanBtr1Register; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
        
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u8CanCtl1Register; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
#endif        

#if !(defined(CAN_43_MCAN_MCAN_SPECIFIC) || defined(CAN_MSCAN_SPECIFIC))
        CONST(uint8, CAN_43_MCAN_CONST) u8TxArbitrationStartDelay; /**< @brief The value of the Tx Arbitration Start Delay (TASD) bit field. */
#endif

#if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)
  #ifdef CAN_MSCAN_SPECIFIC
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u32ControlRegisterAlternate; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
  #else
        CONST(uint32, CAN_43_MCAN_CONST) u32ControlRegisterAlternate; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
  #endif
#endif /* (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON) */

        CONST(uint16, CAN_43_MCAN_CONST) u16ControllerBaudRate; /**< @brief Configured BaudRate in kbps. */
#if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        CONST(Can_43_MCAN_ControllerFdConfigType, CAN_43_MCAN_CONST) ControllerFD; /*FD settings */
#endif

#if !(defined(CAN_43_MCAN_MCAN_SPECIFIC) || defined(CAN_MSCAN_SPECIFIC))
  #if (CAN_43_MCAN_CBT_ENABLE == STD_ON)
        CONST(Can_43_MCAN_ControllerCbtConfigType, CAN_43_MCAN_CONST) ControllerCbtRegister; /* CBT settings */
  #endif
#endif
#if (CAN_43_MCAN_SET_BAUDRATE_API == STD_ON)
        CONST(uint16, CAN_43_MCAN_CONST) u16ControllerBaudRateConfigID;
#endif
    } Can_43_MCAN_ControllerBaudrateConfigType;
    
#ifndef CAN_43_MCAN_MCAN_SPECIFIC
/**
* @brief          Configuration of FlexCAN controller.
* @details        This structure is initialized by Tresos considering user settings.
*                 Used by Can_ChangeBaudrate() API to set the default baudrate after initialization.
*                 and to change the baudrate when the FlexCAN is in stopped mode.
*
*/
typedef struct
    {
#ifndef CAN_MSCAN_SPECIFIC         
        CONST(uint32, CAN_43_MCAN_CONST) u32ControlRegister; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
#else  
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u8CanCtl1Register; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u8CanBtr1Register; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
#endif    
#if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)
  #ifdef CAN_MSCAN_SPECIFIC
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u32ControlRegisterAlternate; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
        CONST(Can_HwWidth, CAN_43_MCAN_CONST) u8CanBtr1RegisterAlternate;
  #else
        CONST(uint32, CAN_43_MCAN_CONST) u32ControlRegisterAlternate; /**< @brief Content of the Control Register (CTRL) fields: PRESDIV, RJW, PSEG1, PSEG2, CLKSRC, LPB, SMP, BOFF_REC, LOM, PROPSEG. */
  #endif
#endif /* (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON) */
    } Can_43_MCANStatic_ControllerBaudrateConfigType;
#endif

#ifdef CAN_MSCAN_SPECIFIC  
/**
* @brief          Configuration of filters on MSCAN controller.
* @details        This structure is initialized by Tresos considering user settings.
*                 Used by Can_Mscan_ProcessRx() API to set the filters for receive buffers
*
*/

#ifdef CAN_43_MCAN_EXTENDEDID
    #if (CAN_43_MCAN_EXTENDEDID == STD_ON)
/**
* @{
* @brief          Can_43_MCAN_FilterConfigType
* @details        Type for storing the Identifier Length Type: Normal or Extended.
*                   - used by "Can_MessageBufferConfigObjectType" structure.
*                 The driver does not distinguish between Extended and Mixed transmission modes.
*                 Extended transmission mode of operation behaves the same as Mixed mode.
*/
    typedef  uint32 Can_43_MCAN_FilterConfigType;
    #else /* (CAN_43_MCAN_EXTENDEDID == STD_OFF) */
    typedef  uint16 Can_43_MCAN_FilterConfigType;
    #endif /* (CAN_43_MCAN_EXTENDEDID == STD_ON/STD_OFF) */
#else
    typedef  uint16 Can_43_MCAN_FilterConfigType;
#endif

/*
* @{
* @brief          Can_43_MCAN_FilterConfigType
* @details        Type for storing pointer to the Identifier Filter Mask.
*                 
*
*/
typedef CONSTP2CONST(Can_43_MCAN_FilterConfigType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) Can_43_MCAN_FilterConfigPtrType;
/**@}*/    
    
#endif    
    
/*
* @{
* @brief          Can_43_MCAN_IdPtrType
* @details        Type for storing pointer to the Identifier Lenght Type.
*                 - used by "Can_43_MCAN_ConfigType" structure (pointer to the FilterMasks).
*
*/
typedef CONSTP2CONST(Can_IdType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) Can_43_MCAN_IdPtrType;
/**@}*/

/**
* @brief          Type for pointer to function.
* @details        Type for pointer to function. Used for user handlers from plugin.
*
*/
typedef void (*Can_43_MCAN_PCallBackType)( void);


#ifndef CAN_43_MCAN_MCAN_SPECIFIC
#if (CAN_RXFIFO_ENABLE == STD_ON)
/**
* @brief          Rx Fifo Table IDs and Filter Masks
* @details        Rx Fifo Table IDs and Filter Masks
*
*/
typedef struct
    {
        CONST(uint32, CAN_43_MCAN_CONST) u32TableId; /**< @brief Table with the IDs specific for Rx Fifo */

        CONST(uint32, CAN_43_MCAN_CONST) u32TableFilterMask; /**< @brief Table with the Filter masks */

    } Can_43_MCAN_RxFiFoTableIdConfigType;

#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
#endif

#ifdef CAN_43_MCAN_MCAN_SPECIFIC
#if (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON)
/**
* @brief          Rx Filter Table
* @details        Rx Filter Table Type
*/
typedef struct
    {
        CONST(uint8, CAN_43_MCAN_CONST)     u8ControllerOffset; /**< @brief Hardware Offset for Can controller: FLEXCAN_A = Offset[0], FLEXCAN_B = Offset[1], ... */
        CONST(Can_43_MCANIdType, CAN_43_MCAN_CONST) eRxFilterMbType; /**< @brief Table Count */
        CONST(uint8, CAN_43_MCAN_CONST)     u8RxFilterOffset; /**< @brief Table Count */
        CONST(uint8, CAN_43_MCAN_CONST)     u8RxFilterConfig; /**< @brief Table Count */
        CONST(uint8, CAN_43_MCAN_CONST)     u8RxFilterType; /**< @brief Table Count */
        CONST(uint32, CAN_43_MCAN_CONST)    u32RxFilterId1Value; /**< @brief Table Count */
        CONST(uint32, CAN_43_MCAN_CONST)    u32RxFilterId2Value; /**< @brief Table Count */
    } Can_43_MCAN_RxFilterTableType;

/**
* @brief          Controller Rx Fifo Configuration
* @details        Controller Rx Fifo Configuration
*/
typedef struct
    {
        /* Selects the receive FIFO (FIFO 0, FIFO 1). */
        CONST(Can_43_MCAN_FIFOChannelType, CAN_43_MCAN_CONST) FIFOChannel;
        /* Configures the FIFO depth. */
        CONST(uint8, CAN_43_MCAN_CONST)  FIFODepth;
        /* WaterMask level */
        CONST(uint8, CAN_43_MCAN_CONST) FIFOWaterMaskLevel;
        /* WaterMask Processing Type */
        CONST(boolean, CAN_43_MCAN_CONST) FIFOWaterMaskPolling;
        /* FIFO WaterMask Notification */
        CONST(Can_43_MCAN_PCallBackType, CAN_43_MCAN_CONST) Can_RxFifoWarningNotification;
        /* OverFlow Processing Type */
        CONST(boolean, CAN_43_MCAN_CONST) FIFOOverflowPolling;
        /* OverFlow Notification */
        CONST(Can_43_MCAN_PCallBackType, CAN_43_MCAN_CONST) Can_RxFifoOverflowNotification;  
    } Can_43_MCAN_ControllerRxFifoConfigType;
        
/**
* @brief          Controller Sections Address Offset
* @details        Controller Sections Address Offset
*/
typedef struct
    {
        CONST(uint16, CAN_43_MCAN_CONST) StandardFilterOffset;
        CONST(uint16, CAN_43_MCAN_CONST) ExtendedFilterOffset;
        CONST(uint16, CAN_43_MCAN_CONST) RxFifo0Offset;
        CONST(uint16, CAN_43_MCAN_CONST) RxFifo1Offset;
        CONST(uint16, CAN_43_MCAN_CONST) RxBufferOffset;
        CONST(uint16, CAN_43_MCAN_CONST) TxBufferOffset;
    } Can_43_MCAN_ControllerSectionOffsetType;
#endif /* (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON) */
#endif

/**
* @brief          Can_43_MCAN_MBConfigObjectType
* @details        Type for storing information about Message Buffers (CAN hardware objs).
*                 Used by Can_43_MCAN_MBConfigContainerType.
*
*/
typedef struct
    {
#ifndef CAN_43_MCAN_MCAN_SPECIFIC
        VAR(Can_HwHandleType, CAN_43_MCAN_VAR) uIdMaskIndex; /**< @brief Index into array of Can_FilterMaskType values (uint8/uint16), Current MB and the coresponding filter mask. */
#endif

        CONST(uint8, CAN_43_MCAN_CONST) u8ControllerId; /**< @brief Controller ID (index into controller address array containing Can_ControllerPtrType). */

        VAR(Can_43_MCANIdType, CAN_43_MCAN_VAR) uIdType; /**< @brief ID type: CAN_EXTENDED, CAN_STANDARD, CAN_MIXED. */

        VAR(Can_43_MCAN_ObjType, CAN_43_MCAN_VAR) eMBType; /**< @brief Receive/Transmit */

        VAR(Can_IdType, CAN_43_MCAN_VAR) uMessageId; /**< @brief (extended identifier) (uint16/uint32). configurable by CanHardwareObject/CanIdValue. */

        CONST(uint8, CAN_43_MCAN_CONST) u8LocalPriority; /**< @brief Local priority bits used for arbitration. */

        VAR(uint32, CAN_43_MCAN_VAR) u32HWObjID; /**< @brief HW Obiect ID */
        
#if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        VAR(uint8, CAN_43_MCAN_VAR) u8FdPaddingValue; /**< @brief Padding value for MB > 8 bytes */
#endif

#ifdef CAN_43_MCAN_MCAN_SPECIFIC
#if (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON)
        CONST(uint8, CAN_43_MCAN_CONST) u8StoredRxMb; /**< @brief read write period reference */
#endif
#endif

        CONST(uint8, CAN_43_MCAN_CONST) u32CanMainFuncRWPeriodRef; /**< @brief read write period reference */
        CONST(uint16, CAN_43_MCAN_CONST) u16MBOffsetAddr;          /**< @brief offset address of MB */
        CONST(uint8, CAN_43_MCAN_CONST)  u8MBPayloadLength;        /**< @brief MB data size */
        CONST(uint8, CAN_43_MCAN_CONST)  u8HWMBIndex;              /**< @brief The index of MB in message buffer memory */


    } Can_43_MCAN_MBConfigObjectType;


/**
* @brief          Type for storing Message Buffer configurations.
* @details        The MessageBufferConfigs array is sorted according to:
*                 - HRHs first, HTHs next (AutoSAR requirement)
*                 - Controller ID (HRHs and HTHs belonging to all controllers must be grouped together)
*                 - Message ID (to ensure top priority IDs are first which means they will be serviced first)
*
*/
typedef struct
    {
        CONSTP2CONST(Can_43_MCAN_MBConfigObjectType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pMessageBufferConfigsPtr; /**< @brief Pointer to the MB array . */

        CONST(Can_HwHandleType, CAN_43_MCAN_CONST) uMessageBufferConfigCount; /**< @brief Number of elements in the array -( having 6 controllers with 64MBs each uint8 is not enough to store this value -> the type is extended to uint16). */

    } Can_43_MCAN_MBConfigContainerType;


/**
* @brief          Structure for describing individual FlexCAN controllers on the chip.
* @details        HRH = Hardware Receive Handle (HRH) is defined and provided by the CAN driver.
*                       Each HRH represents exactly one hardware object.
*                       The HRH can be used to optimize software filtering.
*                 HTH = The Hardware Transmit Handle (HTH) is defined and provided by the CAN driver.
*                       Each HTH represents one or several hardware objects, that are
*                       configured as hardware transmit pool.
*
*/
typedef struct
    {
#ifdef CAN_MSCAN_SPECIFIC
          CONST(Can_43_MCAN_AcceptanceType, CAN_43_MCAN_CONST) CanFilterAcceptance;
#endif           

#ifndef CAN_43_MCAN_MCAN_SPECIFIC
        CONST(uint8, CAN_43_MCAN_CONST) u8MaxMBCount; /**< @brief Max Message Buffer number. */
#else
#if (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON)
        CONST(uint8, CAN_43_MCAN_CONST) u8MaxMbRxCount; /**< @brief Max Rx Message Buffer number. */

        CONST(uint8, CAN_43_MCAN_CONST) u8MaxMbTxCount; /**< @brief Max Message Buffer number for Tx Buffer. */
        
        CONSTP2CONST(Can_43_MCAN_ControllerRxFifoConfigType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pControllerRxFifo0ConfigsPtr;
        
        CONSTP2CONST(Can_43_MCAN_ControllerRxFifoConfigType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pControllerRxFifo1ConfigsPtr;
        
        CONSTP2CONST(Can_43_MCAN_ControllerSectionOffsetType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pControllerSectionOffsetPtr;        
#endif
#endif
        CONST(uint8, CAN_43_MCAN_CONST) u8MaxBaudRateCount; /**< @brief Max BaudRate number. */
        CONST(uint8, CAN_43_MCAN_CONST) u8DefaultBaudRateIndex; /**< @brief Default baudrate index. */
        CONSTP2CONST(Can_43_MCAN_ControllerBaudrateConfigType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pControllerBaudrateConfigsPtr; /**< @brief Pointer to the Configuration of Baudrate timing parameter for FlexCAN baudrate controller ( CTRL value register). */

#ifndef CAN_43_MCAN_MCAN_SPECIFIC
  #if (CAN_RXFIFO_ENABLE == STD_ON)
        CONST(uint32, CAN_43_MCAN_CONST) u32RxFifoGlobalMask; /**< @brief Rx Fifo Global mask value */

        CONST(uint8, CAN_43_MCAN_CONST) u8RxFiFoUsedMb; /**< @brief Number of MBs used by Rx Fifo */
        
        CONST(Can_43_MCAN_PCallBackType, CAN_43_MCAN_CONST) Can_RxFifoOverflowNotification; /**< @brief Pointer to RX FIFO Overflow notification function. */

        CONST(Can_43_MCAN_PCallBackType, CAN_43_MCAN_CONST) Can_RxFifoWarningNotification; /**< @brief Pointer to RX FIFO Warning notification function. */
        
  #endif  /* (CAN_RXFIFO_ENABLE == STD_ON) */
  #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        CONST(uint32, CAN_43_MCAN_CONST) u32MBBlockSize; /**< @brief This parameter is used to configure for three MBDSR fields in CAN_FDCTRL register */
  #endif
#endif/* CAN_43_MCAN_MCAN_SPECIFIC */
        
        CONST(uint32, CAN_43_MCAN_CONST) u32Options; /**< @brief Interrupt line */
 
    } Can_43_MCAN_ControlerDescriptorType;
    

    /**
* @brief          Structure for describing individual FlexCAN controllers on the chip.
* @details        HRH = Hardware Receive Handle (HRH) is defined and provided by the CAN driver.
*                       Each HRH represents exactly one hardware object.
*                       The HRH can be used to optimize software filtering.
*                 HTH = The Hardware Transmit Handle (HTH) is defined and provided by the CAN driver.
*                       Each HTH represents one or several hardware objects, that are
*                       configured as hardware transmit pool.
*
*/
typedef struct
    {
        CONST(uint8, CAN_43_MCAN_CONST) u8ControllerOffset; /**< @brief Hardware Offset for Can controller: FLEXCAN_A = Offset[0], FLEXCAN_B = Offset[1], ... */

#ifndef CAN_43_MCAN_MCAN_SPECIFIC
        CONSTP2CONST(Can_43_MCANStatic_ControllerBaudrateConfigType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pStaticControllerBaudrateConfigsPtr; /**< @brief Pointer to the Configuration of Baudrate timing parameter for FlexCAN baudrate controller ( CTRL value register). */
#endif
  
#ifdef CAN_43_MCAN_MCAN_SPECIFIC
  #if (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON)
    #ifdef CAN_43_MCAN_SUPPORT_MRAF_EVENT
      #if (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON)
        CONST(Can_43_MCAN_PCallBackType, CAN_43_MCAN_CONST) Can_SupportMRAFNotification; /*< @brief Pointer to RX FIFO Overflow notification function. */
      #endif /* (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON) */
    #endif /* define CAN_43_MCAN_SUPPORT_MRAF_EVENT */
  #endif /* define CAN_43_MCAN_MCAN_SPECIFIC */
#endif /* CAN_43_MCAN_MCAN_SPECIFIC */ 

#if ((CAN_43_MCAN_ERROR_NOTIFICATION_ENABLE == STD_ON) && (CPU_BYTE_ORDER==HIGH_BYTE_FIRST))
        CONST(Can_43_MCAN_PCallBackType, CAN_43_MCAN_CONST) Can_ErrorNotification; /*< @brief Pointer to Error interrupt notification function (ESR[ERR_INT]). */
#elif(CPU_BYTE_ORDER==LOW_BYTE_FIRST) /* (CAN_43_MCAN_ERROR_NOTIFICATION_ENABLE == STD_ON) */
        CONST(Can_43_MCAN_PCallBackType, CAN_43_MCAN_CONST) Can_ErrorNotification; /*< @brief Pointer to Error interrupt notification function (ESR[ERR_INT]). */
#endif

#ifndef CAN_43_MCAN_MCAN_SPECIFIC
#if (CAN_MIX_MB_SUPPORT == STD_ON)
        CONST(uint8, CAN_43_MCAN_CONST) u8NumberOfMB; /*< @brief Number of message Buffers available for FlexCan unit. */
#endif /* (CAN_MIX_MB_SUPPORT == STD_ON) */
#endif /* CAN_43_MCAN_MCAN_SPECIFIC */
        CONST(uint32, CAN_43_MCAN_CONST) u32Options; /*< @brief BusOff Sw Recovery, RXFifo En, IDAM Type,  Event Trigger Mode TxProcessing/RxProcessing/BusoffProcessing. */
    } Can_43_MCANStatic_ControlerDescriptorType;
    
/**
* @brief          Top Level structure containing all Driver configuration.
* @details        A pointer to this structure is transmitted to Can_Init() to initalize the driver at startup.
*                 The application selects one of the configurations by using a pointer to one of the elements
*                 of this array as a parameter of the Can_Init function.
*
*/
typedef struct
    {
        VAR(uint8, CAN_43_MCAN_VAR) u8ControllersConfigured; /**< @brief Number of Can Controllers configured in Tresos plugin. */

        P2CONST(Can_43_MCANStatic_ControlerDescriptorType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) StaticControlerDescriptors; /**< @brief Pointer to the first FlexCAN Controller description. */
        
    } Can_43_MCANStatic_ConfigType;
    
    
/**
* @brief          Top Level structure containing all Driver configuration.
* @details        A pointer to this structure is transmitted to Can_Init() to initalize the driver at startup.
*                 The application selects one of the configurations by using a pointer to one of the elements
*                 of this array as a parameter of the Can_Init function.
*
*/
typedef struct
    {
        
#ifdef CAN_MSCAN_SPECIFIC        
        VAR(Can_43_MCAN_FilterConfigPtrType, CAN_43_MCAN_VAR) pConfigFilterMask;
#endif
#ifndef CAN_43_MCAN_MCAN_SPECIFIC
        VAR(Can_43_MCAN_IdPtrType, CAN_43_MCAN_VAR) pFilterMasks; /**< @brief Pointer to the first FilterMask value - any controller can have many filter masks for Can messages. */
#endif
        CONST(Can_43_MCAN_MBConfigContainerType, CAN_43_MCAN_CONST) MBConfigContainer; /**< @brief Pointer to the first MB configuration of this Controller. */
        P2CONST(Can_43_MCAN_ControlerDescriptorType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) ControlerDescriptors; /**< @brief Pointer to the first FlexCAN Controller description. */
        
#ifndef CAN_43_MCAN_MCAN_SPECIFIC
#if (CAN_RXFIFO_ENABLE == STD_ON)
        CONSTP2CONST(Can_43_MCAN_RxFiFoTableIdConfigType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pRxFiFoTableIdConfig; /**< @brief Pointer to the Table IDs for the RxFifo. */
#endif /* (CAN_RXFIFO_ENABLE == STD_ON) */
#endif /* (CAN_43_MCAN_MCAN_SPECIFIC) */

#ifdef CAN_43_MCAN_MCAN_SPECIFIC
#if (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON)
        CONST(uint8, CAN_43_MCAN_CONST) u8NumberRxFilterTable; /**< @brief: the number of filter element in the Rx Filter Table */
        CONSTP2CONST(Can_43_MCAN_RxFilterTableType, CAN_43_MCAN_CONST, CAN_43_MCAN_APPL_CONST) pRxFilterTableConfig; /**< @brief: The Rx Filter Table */
#endif /* (CAN_43_MCAN_MCAN_SPECIFIC == STD_ON) */
#endif/*CAN_43_MCAN_MCAN_SPECIFIC*/
        /*Maximum Object IDs configured */
        VAR(uint32, CAN_43_MCAN_VAR) u32CanMaxObjectId;
#ifndef CAN_43_MCAN_MCAN_SPECIFIC
        /* The index of the first HTH configured */
        CONST(Can_HwHandleType, CONST) uCanFirstHTHIndex;
#endif/*CAN_43_MCAN_MCAN_SPECIFIC*/
        /*Controller ID mapping*/
        CONST(uint8, CAN_43_MCAN_CONST) u8ControllerIdMapping[CAN_43_MCAN_MAX_OBJECT_ID];

        /*Can Object Type mapping*/
        CONST(Can_43_MCAN_ObjType, CAN_43_MCAN_CONST) eObjectTypeMapping[CAN_43_MCAN_MAX_OBJECT_ID];

    } Can_43_MCAN_ConfigType;    

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define CAN_43_MCAN_START_SEC_VAR_INIT_UNSPECIFIED
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

/*
    Holds current status/run-time of CAN driver: CAN_UNINIT or CAN_READY (declared as global variable in "Can.c" file).
    (CAN103) After power-up/reset, the Can module shall be in the state CAN_UNINIT.
    Covers CAN103
*/

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)

extern VAR(Can_43_MCAN_StatusType, CAN_43_MCAN_VAR) Can_43_MCAN_eDriverStatus;

#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
#define CAN_43_MCAN_STOP_SEC_VAR_INIT_UNSPECIFIED
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"


#define CAN_43_MCAN_START_SEC_VAR_INIT_UNSPECIFIED
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

/* Pointer to the current Driver Configuration (passed to the driver during initialization). Initialized by Can_Init(). */
extern P2CONST(Can_43_MCAN_ConfigType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCAN_pCurrentConfig;
extern P2CONST(Can_43_MCAN_ControlerDescriptorType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCAN_pControlerDescriptors;

extern P2CONST(Can_43_MCANStatic_ConfigType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCANStatic_pCurrentConfig;
extern P2CONST(Can_43_MCANStatic_ControlerDescriptorType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCANStatic_pControlerDescriptors;
#define CAN_43_MCAN_STOP_SEC_VAR_INIT_UNSPECIFIED
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

#define CAN_43_MCAN_START_SEC_CONFIG_DATA_UNSPECIFIED
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

/* Extern declarations for CanController Configuration and CanConfigType. Exports the PC or PB Can_43_MCAN_ConfigType structures. */
#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_ON)
    /* Export Driver configuration */
    /* @violates @ref Can_43_MCAN_h_REF_2 Violates MISRA 2004 Required Rule 8.7, Required*/
    CAN_43_MCAN_INIT_CONFIG_PC_DEFINES
#endif /* #if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_ON) */

#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_OFF)
    /* Export Driver configuration */
    /* @violates @ref Can_43_MCAN_h_REF_2 Violates MISRA 2004 Required Rule 8.7, Required*/
    CAN_43_MCAN_INIT_CONFIG_PB_DEFINES
#endif /* #if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_OFF) */

/* @violates @ref Can_43_MCAN_h_REF_2 Violates MISRA 2004 Required Rule 8.7, Required*/
extern CONST(Can_43_MCANStatic_ConfigType, CAN_43_MCAN_CONST) Can_43_MCANStatic_ConfigSet;

#define CAN_43_MCAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#define CAN_43_MCAN_START_SEC_CODE
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"


extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_Init( P2CONST(Can_43_MCAN_ConfigType, AUTOMATIC, CAN_43_MCAN_APPL_CONST) Config);



#if (CAN_43_MCAN_VERSION_INFO_API == STD_ON)

extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_43_MCAN_APPL_DATA) versioninfo);

#endif /* (CAN_43_MCAN_VERSION_INFO_API == STD_ON) */
#if (CAN_43_MCAN_SET_BAUDRATE_API == STD_ON)
extern FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_SetBaudrate( VAR(uint8, AUTOMATIC) Controller,
                                                       CONST(uint16, AUTOMATIC) BaudRateConfigID
                                                     );
#endif /* (CAN_43_MCAN_SET_BAUDRATE_API == STD_ON) */
#if (CAN_43_MCAN_CHANGE_BAUDRATE_API == STD_ON)

extern FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_ChangeBaudrate( VAR(uint8, AUTOMATIC) Controller,
                                                          CONST(uint16, AUTOMATIC) Baudrate
                                                        );



extern FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_CheckBaudrate( VAR(uint8, AUTOMATIC) Controller,
                                                         CONST(uint16, AUTOMATIC) Baudrate
                                                       );

#endif /* (CAN_43_MCAN_CHANGE_BAUDRATE_API == STD_ON) */


extern FUNC(Can_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_SetControllerMode( VAR(uint8, AUTOMATIC) Controller,
                                                             VAR(Can_StateTransitionType, AUTOMATIC) Transition
                                                           );



extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_DisableControllerInterrupts( VAR(uint8, AUTOMATIC) Controller);



extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_EnableControllerInterrupts( VAR(uint8, AUTOMATIC) Controller);



extern FUNC(Can_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_Write( VAR(Can_HwHandleType, AUTOMATIC) Hth,
                                                 P2CONST(Can_PduType, AUTOMATIC, CAN_43_MCAN_APPL_CONST) PduInfo
                                               );

extern FUNC (Can_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_CheckWakeup( VAR(uint8, AUTOMATIC) controller);




#if (CAN_43_MCAN_TXPOLL_SUPPORTED == STD_ON)

extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write( void );

#ifdef CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE
#if (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE==STD_ON)

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_0
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_0( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_1
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_1( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_2
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_2( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_3
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_3( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_4
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_4( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_5
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_5( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_6
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_6( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_7
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_7( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_8
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_8( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_9
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_9( void );
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_10
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_10( void );
#endif


#endif /* (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE==STD_ON) */
#endif /* (ifdef CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE) */

#else /* (CAN_43_MCAN_TXPOLL_SUPPORTED == STD_OFF) */

/* @violates @ref Can_43_MCAN_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define Can_43_MCAN_MainFunction_Write()

#endif /* (CAN_43_MCAN_TXPOLL_SUPPORTED == STD_OFF) */

#if (CAN_43_MCAN_RXPOLL_SUPPORTED == STD_ON)


extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read( void);

#ifdef CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ
#if (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ == STD_ON)
    
#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_0  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_0( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_1  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_1( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_2  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_2( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_3  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_3( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_4  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_4( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_5  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_5( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_6  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_6( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_7  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_7( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_8  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_8( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_9  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_9( void); 
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_10  
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_10( void); 
#endif

#endif /* (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ == STD_ON) */
#endif /* ifdef CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ */

#else /* (CAN_43_MCAN_RXPOLL_SUPPORTED == STD_OFF) */
/* @violates @ref Can_43_MCAN_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define Can_43_MCAN_MainFunction_Read()

#endif /* (CAN_43_MCAN_RXPOLL_SUPPORTED == STD_OFF) */



#if (CAN_43_MCAN_BUSOFFPOLL_SUPPORTED == STD_ON)

extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_BusOff( void);

#else /* (CAN_43_MCAN_BUSOFFPOLL_SUPPORTED == STD_OFF) */

/* @violates @ref Can_43_MCAN_h_REF_1 Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.*/
#define Can_43_MCAN_MainFunction_BusOff()

#endif /* (CAN_43_MCAN_BUSOFFPOLL_SUPPORTED == STD_OFF) */
  
#ifdef CAN_43_MCAN_SUPPORT_MRAF_EVENT
  #if (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON)
    #if (CAN_43_MCAN_MRAFPOLL_SUPPORTED == STD_ON)
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_CheckMRAF( void);
    #else /* (CAN_43_MCAN_MRAFPOLL_SUPPORTED == STD_OFF) */
#define Can_43_MCAN_MainFunction_CheckMRAF()
    #endif
  #endif /* (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_OFF) */
#endif /* defined(CAN_43_MCAN_SUPPORT_MRAF_EVENT) */
#ifdef ERR_IPV_MCAN_0002 
  #if (ERR_IPV_MCAN_0002 == STD_ON)
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_DummyRead(VAR(uint8, AUTOMATIC) u8Controller);
  #endif
#endif
extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Mode( void);


#if (CAN_43_MCAN_API_ENABLE_ABORT_MB == STD_ON)


extern FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_AbortMb( VAR(Can_HwHandleType, AUTOMATIC) Hth);

#endif /* (CAN_43_MCAN_API_ENABLE_ABORT_MB == STD_ON) */

#if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)


extern FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_SetClockMode( VAR(uint8, AUTOMATIC) can_controller, VAR(Can_43_MCAN_ClockModeType, AUTOMATIC) can_clk_mode);

#endif /* CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON */


#define CAN_43_MCAN_STOP_SEC_CODE
/*
* @violates @ref Can_43_MCAN_h_REF_4 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /*CAN_43_MCAN_H*/

/** @} */
