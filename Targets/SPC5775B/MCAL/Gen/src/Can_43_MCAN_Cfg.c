/**
*   @file    Can_43_MCAN_Cfg.c
*   @version 1.0.1
*
*   @brief   AUTOSAR MCan - module interface
*   @details Configuration Structures for PreCompile.
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

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*
* @section Can_43_MCAN_Cfg_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1,#include preceded by non preproc directives.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Can_43_MCAN_Cfg_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
* @section Can_43_MCAN_Cfg_c_REF_3
* Violates MISRA 2004 Required Rule 8.10,
* All declarations and definitions of objects or functions at file scope shall
* have internal linkage unless external linkage is required.
* State variables may be used by IPW layer.
*
* @section Can_43_MCAN_Cfg_c_REF_5
* Violates MISRA 2004 Advisory Rule 11.4, A cast should not be performed between a pointer to object
* type and a different pointer to object type.
* @section Can_43_MCAN_Cfg_c_REF_6
* Violates MISRA 2004 Required Rule 16.9, A function identifier shall only be used with either a preceding
* &, or with a parenthesised parameter list, which may be empty type and a different pointer to object type.
*
* @section Can_43_MCAN_Cfg_c_REF_7
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
* is passed to  a macro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).
*
* @section Can_43_MCAN_Cfg_c_REF_8
* Violates MISRA 2004 Required Rule 8.8, An external object or function shall be declared in one and only one file
*
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can_43_MCAN.h"
#include "Can_43_MCAN_IPW.h"

/**
* @file           Can_43_MCAN_Cfg.c
*/



/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define CAN_43_MCAN_VENDOR_ID_PCCFG_C                    43
#define CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_PCCFG_C     4
#define CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_PCCFG_C     0
#define CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_PCCFG_C  3
#define CAN_43_MCAN_SW_MAJOR_VERSION_PCCFG_C             1
#define CAN_43_MCAN_SW_MINOR_VERSION_PCCFG_C             0
#define CAN_43_MCAN_SW_PATCH_VERSION_PCCFG_C             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CAN header file are of the same Autosar version */
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_PCCFG_C != CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_PCCFG_C != CAN_43_MCAN_AR_RELEASE_MINOR_VERSION) || \
     (CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_PCCFG_C != CAN_43_MCAN_AR_RELEASE_REVISION_VERSION) \
    )
  #error "AutoSar Version Numbers of Can_43_MCAN_Cfg.c and Can_43_MCAN.h are different"
#endif


/* Check if current file and CAN header file are of the same Software version */
#if ((CAN_43_MCAN_SW_MAJOR_VERSION_PCCFG_C != CAN_43_MCAN_SW_MAJOR_VERSION) || \
     (CAN_43_MCAN_SW_MINOR_VERSION_PCCFG_C != CAN_43_MCAN_SW_MINOR_VERSION) || \
     (CAN_43_MCAN_SW_PATCH_VERSION_PCCFG_C != CAN_43_MCAN_SW_PATCH_VERSION) \
    )
       #error "Software Version Numbers of Can_43_MCAN_Cfg.c and Can_43_MCAN.h are different"
#endif
/* Check if current file and Can_IPW configuration header file are of the same vendor */
#if (CAN_43_MCAN_VENDOR_ID_PCCFG_C  != CAN_43_MCAN_IPW_VENDOR_ID_H)
#error "Can_43_MCAN.h and Can_43_MCAN_Cfg.h have different vendor ids"
#endif
/* Check if current file and CAN_IPW header file are of the same Autosar version */
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_PCCFG_C != CAN_43_MCAN_IPW_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_PCCFG_C != CAN_43_MCAN_IPW_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_PCCFG_C != CAN_43_MCAN_IPW_AR_RELEASE_REVISION_VERSION_H) \
    )
  #error "AutoSar Version Numbers of Can_43_MCAN_Cfg.c and Can_43_MCAN_IPW.h are different"
#endif
/* Check if current file and CAN_IPW header file are of the same Software version */
#if ((CAN_43_MCAN_SW_MAJOR_VERSION_PCCFG_C != CAN_43_MCAN_IPW_SW_MAJOR_VERSION_H) || \
     (CAN_43_MCAN_SW_MINOR_VERSION_PCCFG_C != CAN_43_MCAN_IPW_SW_MINOR_VERSION_H) || \
     (CAN_43_MCAN_SW_PATCH_VERSION_PCCFG_C != CAN_43_MCAN_IPW_SW_PATCH_VERSION_H) \
    )
       #error "Software Version Numbers of Can_43_MCAN_Cfg.c and Can_43_MCAN_IPW.h are different"
#endif

#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_ON)

#define CAN_43_MCAN_START_SEC_CONST_UNSPECIFIED
/* @violates @ref Can_43_MCAN_Cfg_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"

/*==================================================================================================
*                                   GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
/**
* @brief    Prototype of User Notifications
*/
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/**
* @brief          Can_RxFilterTableType
* @details
*
*/
/*
* @violates @ref Can_43_MCAN_Cfg_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required.
*/
CONST(Can_43_MCAN_RxFilterTableType, CAN_43_MCAN_CONST) RxFilterTableID_PCConfig0[CAN_43_MCAN_MAX_RX_FILTER_TABLE_0] =
{
    /* HRH: CanIdValue; CanFilterMaskValue */                         
    {
        /* Can Controller Offset on chip: MCAN1=offset 0, MCAN2=offset 1, .. */
        (uint8)MCAN_1_OFFSET,
        /* ID type: EXTENDED, STANDARD, MIXED */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Filter Offset */
        (uint8)0x00U,
        /* Filter Config */
        (uint8)0x01U,
        /* Filter Type */
        (uint8)0x02U,
        /* SFID1/EFID1 */
        (uint32)0x180cf102U,
        /* SFID2/EFID2 */
        (uint32)0x1fffffffU
    },
    {
        /* Can Controller Offset on chip: MCAN1=offset 0, MCAN2=offset 1, .. */
        (uint8)MCAN_2_OFFSET,
        /* ID type: EXTENDED, STANDARD, MIXED */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Filter Offset */
        (uint8)0x00U,
        /* Filter Config */
        (uint8)0x02U,
        /* Filter Type */
        (uint8)0x02U,
        /* SFID1/EFID1 */
        (uint32)0x180cf102U,
        /* SFID2/EFID2 */
        (uint32)0x00000000U
    },
    
    /* Filter table: CanRxFilterElement */
    {
        /* Can Controller Offset on chip: MCAN1=offset 0, MCAN2=offset 1, .. */
        (uint8)MCAN_1_OFFSET,
        /* ID type: EXTENDED, STANDARD, MIXED */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Filter Offset */
        (uint8)0x01U,
        /* Filter Config */
        (uint8)0x01U,
        /* Filter Type */
        (uint8)0x00U,
        /* SFID1/EFID1 */
        (uint32)0x18000000U,
        /* SFID2/EFID2 */
        (uint32)0x18ffffffU
    },
    {
        /* Can Controller Offset on chip: MCAN1=offset 0, MCAN2=offset 1, .. */
        (uint8)MCAN_2_OFFSET,
        /* ID type: EXTENDED, STANDARD, MIXED */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Filter Offset */
        (uint8)0x01U,
        /* Filter Config */
        (uint8)0x02U,
        /* Filter Type */
        (uint8)0x00U,
        /* SFID1/EFID1 */
        (uint32)0x18000000U,
        /* SFID2/EFID2 */
        (uint32)0x18ffffffU
    }
};

/*==================================================================================================*/
/**
* @brief          Information about message buffers
* @details        (CAN100)Several TX hardware objects with unique HTHs may be configured. The CanIf module provides the HTH as parameter of the TX request. See Figure 7-2 for a possible configuration.
*
*/
/*
* @violates @ref Can_43_MCAN_Cfg_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required.
*/

CONST(Can_43_MCAN_MBConfigObjectType, CAN_43_MCAN_CONST) Can_43_MCAN_MessageBufferConfigs_PC[CAN_43_MCAN_MAXMBCOUNT_0] =
{
    /* Can_Network_CANNODE_5_Rx_Ext_MailBox_1 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_RECEIVE,
        /* MessageId */
        (Can_IdType)0x180cf102U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x0U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_RX_FIFO0_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Rx_Ext_MailBox_1 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_RECEIVE,
        /* MessageId */
        (Can_IdType)0x180cf102U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x1U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_RX_FIFO1_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_1 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x9U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x2U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_2 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0xaU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x3U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_3 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0xbU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x4U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_4 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0xcU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x5U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_5 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0xdU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x6U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_6 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0xeU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x7U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_7 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0xfU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x8U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_8 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x10U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x9U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_9 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x11U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0xaU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_10 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x12U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0xbU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_11 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x13U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0xcU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_12 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x14U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0xdU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_13 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x15U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0xeU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_14 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x16U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0xfU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_15 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x17U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x10U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_16 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x18U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x11U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_17 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x19U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x12U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_18 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1aU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x13U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_19 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1bU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x14U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_20 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1cU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x15U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_21 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1dU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x16U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_22 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1eU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x17U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_23 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1fU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x18U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_24 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1fU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x19U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_25 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1fU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x1aU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_26 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1fU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x1bU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_27 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1fU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x1cU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_5_Tx_Ext_MailBox_28 Message Buffer of Can Controller ID = 0U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)0U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x1fU,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x1dU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_1 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x1eU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_2 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x1fU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_3 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x20U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_4 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x21U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_5 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x22U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_6 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x23U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_7 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x24U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_8 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x25U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_9 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x26U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_10 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x27U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_11 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x28U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_12 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x29U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_13 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x2aU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_14 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x2bU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_15 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x2cU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_16 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x2dU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_17 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x2eU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_18 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x2fU,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_19 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x30U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_20 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x31U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_21 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x32U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_22 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x33U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_23 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x34U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_24 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x35U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_25 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x36U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_26 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x37U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_27 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x38U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    },
    /* Can_Network_CANNODE_6_Tx_Ext_MailBox_28 Message Buffer of Can Controller ID = 1U*/
    {
        /* ControllerId  - based on the order from CanController list */
        (uint8)1U,
        /* ID type: EXTENDED, STANDARD */
        (Can_43_MCANIdType)CAN_43_MCAN_EXTENDED,
        /* Receive/Transmit MB configuration */
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        /* MessageId */
        (Can_IdType)0x21U,
        /* This Bit not used in platfrom where IPV_MCAN present. Initialised to zero so as not to change generic file */
        (uint8)0U,
        /* Hardware Object ID */
        (Can_HwHandleType)0x39U,
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        (uint8)0x0, /**< @brief Padding value for MB > 8 bytes */
        #endif        
        /* Store MB into Rx FIFO 0/Rx FIFO 1/ Rx Buffer */
        (uint8)MCAN_STORE_TX_BUFFER_U8,
        /* Read/Write period reference used when polling mode is selected for the controller */
        (uint8)0U   /* HOH configured for interrupt mode, reference not used */
    }
};

/*==================================================================================================*/
/**
* @brief          Information about Rx FIFO Configuration
* @details        Information about Rx FIFO Configuration
*
*/
CONST(Can_43_MCAN_ControllerRxFifoConfigType, CAN_43_MCAN_CONST) ControllerRxFifo0Configs_PC_0 =
/* FIFO Configuration of CanRxFifo_0 in CanController_0 */
{
    CAN_43_MCAN_FIFO_0,
    32U,
    0U,
    TRUE,
    (Can_43_MCAN_PCallBackType)NULL_PTR,
    FALSE,
    (Can_43_MCAN_PCallBackType)NULL_PTR
};

CONST(Can_43_MCAN_ControllerRxFifoConfigType, CAN_43_MCAN_CONST) ControllerRxFifo1Configs_PC_0 =
/* FIFO Configuration of CanRxFifo_1 in CanController_0 */
{
    CAN_43_MCAN_FIFO_1,
    32U,
    0U,
    TRUE,
    (Can_43_MCAN_PCallBackType)NULL_PTR,
    FALSE,
    (Can_43_MCAN_PCallBackType)NULL_PTR
};

CONST(Can_43_MCAN_ControllerRxFifoConfigType, CAN_43_MCAN_CONST) ControllerRxFifo1Configs_PC_1 =
/* FIFO Configuration of CanRxFifo_1 in CanController_1 */
{
    CAN_43_MCAN_FIFO_1,
    32U,
    0U,
    TRUE,
    (Can_43_MCAN_PCallBackType)NULL_PTR,
    FALSE,
    (Can_43_MCAN_PCallBackType)NULL_PTR
};

/*==================================================================================================*/
/**
* @brief          Information about Section Offset of Mcan controller
* @details        Information about Section Offset of Mcan controller
*
*/
CONST(Can_43_MCAN_ControllerSectionOffsetType, CAN_43_MCAN_CONST) Can_43_MCAN_ControllerSectionOffset_PC_0 =
{
    0U, /* Standard Filter Section is not initialzed */
    0U, /* Extended Filter Section Offset */
    4U, /* FIFO_0 Section Offset */
    580U, /* FIFO_1 Section Offset */
    0U, /* Rx_Buffer Section is not initialzed */
    1156U /* Tx_Buffer Section Offset */
};

CONST(Can_43_MCAN_ControllerSectionOffsetType, CAN_43_MCAN_CONST) Can_43_MCAN_ControllerSectionOffset_PC_1 =
{
    0U, /* Standard Filter Section is not initialzed */
    1660U, /* Extended Filter Section Offset */
    0U, /* FIFO_0 Section is not initialzed */
    1664U, /* FIFO_1 Section Offset */
    0U, /* Rx_Buffer Section is not initialzed */
    2240U /* Tx_Buffer Section Offset */
};

/*==================================================================================================*/
/**
* @brief          Configuration of MCan controller
* @details        Configuration of MCan controller
*
*/
/*
* @violates @ref Can_43_MCAN_Cfg_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required.
*/
CONST(Can_43_MCAN_ControllerBaudrateConfigType, CAN_43_MCAN_CONST) Can_43_MCAN_ControllerBaudrateConfigs_PC_0[CAN_43_MCAN_CFGSET0_MAX_BAUDRATE_FC_1_0] = 
{
    /*
    =================================================
    Clock Size = Clock from MCU.

    Clock Prescaler = 10 (1..1023)

    CanBitRate = 500 Kbps (1bps..1Mbps)
    Number CANTimeQuantas per bit = 8 (8..25)

    BTP Register Fields:
        TSEG1 = 4  (0..15)
        TSEG2 = 1  (1..7)
        SJW = 0  (0..3)
    =================================================
    */
    /* Configuration for CanController ID0 == MCAN_1 */
    {
        /* ===== Bit Timing and Prescaler Register - BTP ===== */
        
        /* BTP[BRP] - Clock Prescaler */
        (uint32)(
                  ((uint32)((uint32)9U << MCAN_BTP_BRP_SHIFT) & MCAN_BTP_BRP_U32)  |
                  /* BTP[TSEG1] - Segment 1 */
                  ((uint32)4U << MCAN_BTP_TSEG1_SHIFT) |
                  /* BTP[TSEG2] - Segment 2 */
                  ((uint32)1U << MCAN_BTP_TSEG2_SHIFT) | 
                  /* BTP[SJW] - Resynchronization Jump Width */
                  ((uint32)0U << MCAN_BTP_SJW_SHIFT) |
                  (uint32)0U
                ),
        
        #if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)
        0U,
        #endif /* CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON */
        
        (uint16)500 ,  /* 500kbps baud rate */
        
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        {
            (uint32)((uint32)1U << MCAN_FD_OFFSET_U8), /*CAN FD Activated*/
            (uint32)2000U,   /* 500kbps baud rate */
            (uint32)(
                      /* Propagation segment */
                      /* Phase segment 1 */
                      ((uint32)1U << MCAN_FD_PRESDIV_OFFSET) |  /* CAN FD propagation segment */
                      ((uint32)5U << MCAN_FD_PSEG1_OFFSET) | /* Time segment 1 = Propagation segment + Phase segment 1 */
                      ((uint32)2U<<MCAN_FD_PSEG2_OFFSET) |   /* Time segment 2 = Phase segment 2 */
                      ((uint32)0U<<MCAN_FD_SJW_OFFSET) /* Sync jump width*/
                    ),
            (uint32)0U<<8, /* TRCV DELAY*/
            									(boolean)FALSE, /*TRCV DELAY DISABLED*/
            (uint32)((uint32)1U<<MCAN_FD_BRS_OFFSET) /* BRS activated */
            /*true; */
            
            /*  
            (uint8)EIGHT_BYTES_PAYLOAD  
            */
        },
        #endif
        
        #if (CAN_43_MCAN_SET_BAUDRATE_API == STD_ON)
        (uint16)0
        #endif
    }
};

/*
* @violates @ref Can_43_MCAN_Cfg_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required.
*/
CONST(Can_43_MCAN_ControllerBaudrateConfigType, CAN_43_MCAN_CONST) Can_43_MCAN_ControllerBaudrateConfigs_PC_1[CAN_43_MCAN_CFGSET0_MAX_BAUDRATE_FC_2_1] = 
{
    /*
    =================================================
    Clock Size = Clock from MCU.

    Clock Prescaler = 10 (1..1023)

    CanBitRate = 500 Kbps (1bps..1Mbps)
    Number CANTimeQuantas per bit = 8 (8..25)

    BTP Register Fields:
        TSEG1 = 4  (0..15)
        TSEG2 = 1  (1..7)
        SJW = 0  (0..3)
    =================================================
    */
    /* Configuration for CanController ID1 == MCAN_2 */
    {
        /* ===== Bit Timing and Prescaler Register - BTP ===== */
        
        /* BTP[BRP] - Clock Prescaler */
        (uint32)(
                  ((uint32)((uint32)9U << MCAN_BTP_BRP_SHIFT) & MCAN_BTP_BRP_U32)  |
                  /* BTP[TSEG1] - Segment 1 */
                  ((uint32)4U << MCAN_BTP_TSEG1_SHIFT) |
                  /* BTP[TSEG2] - Segment 2 */
                  ((uint32)1U << MCAN_BTP_TSEG2_SHIFT) | 
                  /* BTP[SJW] - Resynchronization Jump Width */
                  ((uint32)0U << MCAN_BTP_SJW_SHIFT) |
                  (uint32)0U
                ),
        
        #if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)
        0U,
        #endif /* CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON */
        
        (uint16)500 ,  /* 500kbps baud rate */
        
        #if (CAN_43_MCAN_FD_MODE_ENABLE == STD_ON)
        {
            (uint32)((uint32)1U << MCAN_FD_OFFSET_U8), /*CAN FD Activated*/
            (uint32)2000U,   /* 500kbps baud rate */
            (uint32)(
                      /* Propagation segment */
                      /* Phase segment 1 */
                      ((uint32)1U << MCAN_FD_PRESDIV_OFFSET) |  /* CAN FD propagation segment */
                      ((uint32)5U << MCAN_FD_PSEG1_OFFSET) | /* Time segment 1 = Propagation segment + Phase segment 1 */
                      ((uint32)2U<<MCAN_FD_PSEG2_OFFSET) |   /* Time segment 2 = Phase segment 2 */
                      ((uint32)0U<<MCAN_FD_SJW_OFFSET) /* Sync jump width*/
                    ),
            (uint32)0U<<8, /* TRCV DELAY*/
            									(boolean)FALSE, /*TRCV DELAY DISABLED*/
            (uint32)((uint32)1U<<MCAN_FD_BRS_OFFSET) /* BRS activated */
            /*true; */
            
            /*  
            (uint8)EIGHT_BYTES_PAYLOAD  
            */
        },
        #endif
        
        #if (CAN_43_MCAN_SET_BAUDRATE_API == STD_ON)
        (uint16)0
        #endif
    }
};

/*==================================================================================================*/
/**
* @brief          Description of individual MCan controllers on chip
* @details        Description of individual MCan controllers on chip
*
*/
/*
* @violates @ref Can_43_MCAN_Cfg_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required.
*/
CONST(Can_43_MCAN_ControlerDescriptorType, CAN_43_MCAN_CONST) Can_43_MCAN_ControlerDescriptors_PC[CAN_43_MCAN_MAXCONTROLLERCOUNT_0] =
{
    /* ControlerDescriptor of CanController_0 */
    {
        /* No. of Rx Message Buffers for current controller */
        (uint8)0U,
        
        /* No. of Tx Message Buffers for current controller */
        (uint8)28U,
        
        /* ControllerRxFifo0ConfigsPtr */
        &ControllerRxFifo0Configs_PC_0,
        
        /* ControllerRxFifo1ConfigsPtr */
        &ControllerRxFifo1Configs_PC_0,
        
        /* pControllerSectionOffsetPtr */
        &Can_43_MCAN_ControllerSectionOffset_PC_0,
        
        /* No. of BaudRate configured for current controller */
        (uint8)1U,
        
        /* Default BaudRate configured for current controller */
        (uint8)0U,
        
        /* ControllerBaudrateConfigsPtr */
        Can_43_MCAN_ControllerBaudrateConfigs_PC_0,
        
        /* ===== Controller Options ===== */
        (uint32)CAN_43_MCAN_CTLR_CONFIG_ILE_INTL0_EN_U32
    },
    /* ControlerDescriptor of CanController_1 */
    {
        /* No. of Rx Message Buffers for current controller */
        (uint8)0U,
        
        /* No. of Tx Message Buffers for current controller */
        (uint8)28U,
        
        /* ControllerRxFifo0ConfigsPtr */
        NULL_PTR,
        
        /* ControllerRxFifo1ConfigsPtr */
        &ControllerRxFifo1Configs_PC_1,
        
        /* pControllerSectionOffsetPtr */
        &Can_43_MCAN_ControllerSectionOffset_PC_1,
        
        /* No. of BaudRate configured for current controller */
        (uint8)1U,
        
        /* Default BaudRate configured for current controller */
        (uint8)0U,
        
        /* ControllerBaudrateConfigsPtr */
        Can_43_MCAN_ControllerBaudrateConfigs_PC_1,
        
        /* ===== Controller Options ===== */
        (uint32)CAN_43_MCAN_CTLR_CONFIG_ILE_INTL0_EN_U32
    }
};

/*==================================================================================================*/
/**
* @brief          Description of static configuration of individual Mcan controllers on chip
* @details        Description of static configuration of individual Mcan controllers on chip
*
*/
static CONST(Can_43_MCANStatic_ControlerDescriptorType, CAN_43_MCAN_CONST) Can_43_MCANStaticControlerDescriptors_PC[CAN_43_MCAN_MAXCONTROLLERCOUNT_0] =
{
    /* ControlerDescriptor of CanController_0 */
    {
        /* Can Controller Offset on chip: Can_A=offset 0, Can_B=offset 1, .. -u8ControllerOffset */
        (uint8)MCAN_1_OFFSET,
        
        #ifdef CAN_43_MCAN_SUPPORT_MRAF_EVENT
        #if (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON)
        /* Pointer to MRAF notification function - CanMRAFNotification */   
        NULL_PTR,
        #endif /* (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON) */
        #endif /* define CAN_43_MCAN_SUPPORT_MRAF_EVENT */
        
        #if (CAN_43_MCAN_ERROR_NOTIFICATION_ENABLE == STD_ON)
        /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */             
        NULL_PTR,
        #endif
        
        /* ===== Controller Options ===== */
        (uint32)(
                  /* Can Test Mode Disabled */ 
                  /* Can controller error interrupt */
                  /* Rx select by interrupt */
                  /* Tx select by interrupt */
                  /* BusOff select by interrupt */
                  0U
                )
    }, /* ControlerDescriptors[0] end */
    /* ControlerDescriptor of CanController_1 */
    {
        /* Can Controller Offset on chip: Can_A=offset 0, Can_B=offset 1, .. -u8ControllerOffset */
        (uint8)MCAN_2_OFFSET,
        
        #ifdef CAN_43_MCAN_SUPPORT_MRAF_EVENT
        #if (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON)
        /* Pointer to MRAF notification function - CanMRAFNotification */   
        NULL_PTR,
        #endif /* (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON) */
        #endif /* define CAN_43_MCAN_SUPPORT_MRAF_EVENT */
        
        #if (CAN_43_MCAN_ERROR_NOTIFICATION_ENABLE == STD_ON)
        /* Pointer to Error interrupt notification function (ESR[ERR_INT]). */             
        NULL_PTR,
        #endif
        
        /* ===== Controller Options ===== */
        (uint32)(
                  /* Can Test Mode Disabled */ 
                  /* Can controller error interrupt */
                  /* Rx select by interrupt */
                  /* Tx select by interrupt */
                  /* BusOff select by interrupt */
                  0U
                )
    } /* ControlerDescriptors[1] end */
};

/*==================================================================================================*/
/**
* @brief          Top level structure containing all Can driver configurations
* @details        Top level structure containing all Can driver configurations
*
* @violates @ref Can_43_MCAN_Cfg_c_REF_3 All declarations and definitions of objects or
* functions at file scope shall have internal linkage unless external linkage is required.
*/
CONST(Can_43_MCAN_ConfigType, CAN_43_MCAN_CONST) Can_43_MCAN_ConfigSet_PC =
{
    /* MessageBufferConfigContainer */
    {
        /* MessageBufferConfigsPtr */
        Can_43_MCAN_MessageBufferConfigs_PC,
        
        /* MessageBufferConfigCount */
        (Can_HwHandleType)58U,
    },
    
    /* MCAN controller description */
    Can_43_MCAN_ControlerDescriptors_PC,
    
    /* The number of Rx Filter Element */
    CAN_43_MCAN_MAX_RX_FILTER_TABLE_0,
    
    /* Rx Filter Table */
    RxFilterTableID_PCConfig0,
    
    /*Maximum Object IDs configured */
    (uint32)58U,
    
    /*Controller ID mapping*/
    {
        0U ,1U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,0U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U ,1U 
    },
    
    /*Can Object Type mapping*/
    {
        (Can_43_MCAN_ObjType)CAN_43_MCAN_RECEIVE,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_RECEIVE,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT,
        (Can_43_MCAN_ObjType)CAN_43_MCAN_TRANSMIT
    }
};

/*==================================================================================================*/
/**
* @brief          Top level structure containing all static Can driver configurations
* @details        Top level structure containing all static Can driver configurations
*
*/
/* @violates @ref Can_43_MCAN_Cfg_c_REF_4 Violates MISRA 2004 Required Rule 8.10*/
CONST(Can_43_MCANStatic_ConfigType, CAN_43_MCAN_CONST) Can_43_MCANStatic_ConfigSet =
{
    /* Number of CAN controllers configured -u8ControllersConfigured*/
    (uint8) 2U,
    
    /* Mcan controller description - ControlerDescriptors*/
    Can_43_MCANStaticControlerDescriptors_PC
};

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*
@file Can_43_MCAN_Cfg.c
*/
#define CAN_43_MCAN_STOP_SEC_CONST_UNSPECIFIED
/* @violates @ref Can_43_MCAN_Cfg_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_43_MCAN_Cfg_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"

#endif /* #if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_ON) */

#ifdef __cplusplus
}
#endif

/** @} */
