/**
*   @file    Lin_ESCI.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Lin - Low level driver header file.
*   @details This file includes the function prototypes defined in the LIN low level driver for ESCI.
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

#ifndef Lin_ESCI_H
#define Lin_ESCI_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Lin_ESCI_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, #include statements in a
* file should only be preceded by other preprocessor directives or comments.
* AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* @section Lin_ESCI_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,
* Precautions shall be taken in order to prevent the contents of a header file being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions. The inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Lin_ESCI_h_REF_3
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Lin_ESCI_h_REF_4
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters.
*
* @section Lin_ESCI_h_REF_5
* Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to
* a braced initializer, a constant, a string literal, a parenthesized expression,
* a type qualifier, a storage class specifier, or a do-while-zero construct.
*
* @section Lin_ESCI_h_REF_6
* Violates MISRA 2004 Required Rule 20.2, Re-use of C90 reserved identifier
* This violation is due to the use of "_" which is required as per Autosar.
*
* @section Lin_ESCI_h_REF_7
* Violates MISRA 2004 Required Rule 8.12, Array declared with unknown size.
*
* @section Lin_ESCI_h_REF_8
* Violates MISRA 2004 Required Rule 8.8, declaring an external identifier in a header file,
* that will be included in any file where the identifier is defined or used
*
* @section Lin_ESCI_h_REF_9
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
* State variables may be used by LLD layer.
*
*/

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LIN_VENDOR_ID_ESCI                    43
/*
* @violates @ref Lin_ESCI_h_REF_3 Identifier clash
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_AR_RELEASE_MAJOR_VERSION_ESCI     4
/*
* @violates @ref Lin_ESCI_h_REF_3 Identifier clash
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_AR_RELEASE_MINOR_VERSION_ESCI     0
/*
* @violates @ref Lin_ESCI_h_REF_3 Identifier clash
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_AR_RELEASE_REVISION_VERSION_ESCI  3
#define LIN_SW_MAJOR_VERSION_ESCI             1
#define LIN_SW_MINOR_VERSION_ESCI             0
#define LIN_SW_PATCH_VERSION_ESCI             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*=================================================================================================
                                       DEFINES AND MACROS
=================================================================================================*/
/**
* @brief        Time out for the slave data byte.
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_ZERO_U8           ((uint8)63U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_ONE_U8            ((uint8)77U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_TWO_U8            ((uint8)91U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_THREE_U8          ((uint8)105U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_FOUR_U8           ((uint8)119U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_FIVE_U8           ((uint8)133U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_SIX_U8            ((uint8)147U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_SEVEN_U8          ((uint8)161U)
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_TIMEOUT_DATABYTE_EIGHT_U8          ((uint8)175U)

/**
* @brief        Interrupt Errors conditions.
*
*/
#define CRC_ERROR                  0x09U /**< @brief CRC error occurred
                                              on a channel. */
#define OVERFLOW_ERROR             0x0AU /**< @brief Overflow error occurred
                                              on a channel. */
#define SLAVE_TIMEOUT_ERROR        0x0BU /**< @brief Slave Timeout error
                                              occurred on a channel. */
#define UNREQUESTED_DATA_ERROR     0x0CU /**< @brief Unrequested Data error
                                              occurred on a channel. */
#define PHYSICAL_BUS_ERROR         0x0DU /**< @brief Phisical Bus error
                                              occurred on a channel. */

/**
* @brief        LIN frames states.
*
*/
#define LIN_CH_SEND_HEADER         0x09U /**< @brief The channel is sending
                                             the header part of the frame */
#define LIN_CH_SEND_DATA           0x0AU /**< @brief The channel is sending
                                               the data part of the frame */
#define LIN_CH_SEND_HEADER_ERROR   0x0BU /**< @brief The channel is
               reporting an error after sent the header part of the frame */
#define LIN_CH_SEND_DATA_ERROR     0x0CU /**< @brief The channel is
                 reporting an error after sent the data part of the frame */
#define LIN_CH_RECEIVE_DATA        0x0DU /**< @brief The channel is
                                     receiving the data part of the frame */

/**
* @brief        Macro used to prepare and send the frame.
*
*/
/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Number of eSCI registers writes to sent a master response frame header
*
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define MASTER_RESPONSE_HEADER_WRITE_COUNT_U8       ((uint8)3U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Number of writes on eSCI registers to sent a slave response frame header
*
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define SLAVE_RESPONSE_HEADER_WRITE_COUNT_U8        ((uint8)4U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Number of writes on eSCI registers to sent a complete frame
*
*/
#define LIN_HEADER_DATA_WRITE_COUNT_U8              ((uint8)11U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Index of the Data Buffer byte zero
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ZERO_U8                                ((uint8)0U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Index of the Data Buffer byte one
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ONE_U8                                 ((uint8)1U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Standard length for master request command
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_MAX_DATA_LENGTH_U8                     ((uint8)8U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Constant indicating not mapped eSCI channels
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_NONMAPPED_CHANNEL_VALUE               -1

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Index of the Header Buffer byte zero
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_HEADER_ZERO_U8                         ((uint8)0U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Index of the Header Buffer byte one
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_HEADER_ONE_U8                          ((uint8)1U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Index of the Header Buffer byte two
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_HEADER_TWO_U8                          ((uint8)2U)

/*
*  @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer,
*  a constant, a string literal, a parenthesized expression, a type qualifier,
*  a storage class specifier, or a do-while-zero construct.
*/
/**
* @brief Index of the Header Buffer byte three
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_HEADER_THREE_U8                        ((uint8)3U)

/**
* @brief        Macro to recalculate the parity.
*
*/

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to get the bit seven of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SEVEN_MASK_U8                   ((uint8)0x80U)

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to get the bit six of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SIX_MASK_U8                     ((uint8)0x40U)

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to get the bits six and seven of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SIX_SEVEN_MASK_U8               ((uint8)0xC0U)

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to shift by two the bits of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SHIFT_BY_TWO_U8                 ((uint8)2U)

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to shift by three the bits of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SHIFT_BY_THREE_U8               ((uint8)3U)

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to shift by four the bits of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SHIFT_BY_FOUR_U8                ((uint8)4U)

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to shift by five the bits of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SHIFT_BY_FIVE_U8                ((uint8)5U)

/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
/**
* @brief Mask to shift by six the bits of the LIN identifier register
*
*/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
#define ESCI_ID_BIT_SHIFT_BY_SIX_U8                 ((uint8)6U)


/**
* @brief        Sleep command type.
*
*/
/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
#define SLEEP_CMD_TYPE_U8                           ((uint8)0x03U)

/**
* @brief        Sleep command ID 0x3C.
*
*/
/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
#define SLEEP_IDENTIFIER_VALUE_U8                   ((uint8)0x3CU)

/**
* @brief        Data 0 of the shadow buffer to send sleep command.
*
*/
/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
#define SLEEP_DATABYTE_ONE_VALUE_U8                 ((uint8)0x00U)

/**
* @brief        Data 1-7 of the shadow buffer to send sleep command.
*
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
/* @violates @ref Lin_ESCI_h_REF_5 C macros shall only expand to a braced initializer. */
#define SLEEP_DATABYTE_TWO_TO_EIGHT_VALUE_U8        ((uint8)0xFFU)

/**
* @brief        DMA macros.
*
*/
/**
* @brief Mask to configure D_REQ(bit3) bit of TCD.
*
*/
#define DMA_D_REQ_MASK_U8                           ((uint8)0x08U)
/**
* @brief Mask to configure INT_HALF(bit2) bit of TCD.
*
*/
#define DMA_INT_HALF_MASK_U8                        ((uint8)0x04U)
/**
* @brief Mask to configure INT_MAJ(bit1) bits of TCD.
*
*/
#define DMA_INT_MAJ_MASK_U8                         ((uint8)0x02U)

/**
* @brief        Catastrophic Errors Recovery (CER) Codes returned by the LIN driver.
*
* @details      Unexpected frame status CER code.
*
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_CER_UNEXPECTED_FRAME_STATUS_INTERRUPT_U8 ((uint8)0x01U)


/**
* @brief        Catastrophic Errors Recovery (CER) Codes returned by the LIN driver.
*
* @details      Unexpected frame error status CER code.
*
*/
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_CER_UNEXPECTED_FRAME_ERROR_STATUS_INTERRUPT_U8 ((uint8)0x02U)


/*==================================================================================================
                                             ENUMS
==================================================================================================*/
/**
* @brief          API ESCI LLD functions service IDs.
* @details        Service IDs of the ESCI LLD API.
*/
typedef enum
    {
        ESCI_TX_IRQHANDLER_EDMA = (uint8)0x01U, /**< @brief
                                      ESCI_Tx_InterruptHandler_eDma()
                                                   ID.*/
        ESCI_RX_IRQHANDLER_EDMA = (uint8)0x02U, /**< @brief
                                      ESCI_Rx_InterruptHandler_eDma()
                                                   ID.*/
        ESCI_COPYDATA_ID        = (uint8)0x03U, /**< @brief
                                      ESCI_CopyData() ID.*/
        ESCI_HWGETSTATUS_ID     = (uint8)0x04U, /**< @brief
                                      ESCI_HardwareGetStatus() ID.*/
        ESCI_WAKEUP_ID          = (uint8)0x05U, /**< @brief
                                      ESCI_Wakeup() ID.*/
        ESCI_GOTOSLEEPINT_ID    = (uint8)0x06U, /**< @brief
                                      ESCI_GoToSleepInternal() ID.*/
        ESCI_GOTOSLEEP_ID       = (uint8)0x07U, /**< @brief
                                      ESCI_GoToSleep() ID.*/
        ESCI_SENDRESPONSE_ID    = (uint8)0x08U, /**< @brief
                                      ESCI_SendResponse()ID.*/
        ESCI_SENDHEADER_ID      = (uint8)0x09U, /**< @brief
                                      ESCI_SendHeader() ID.*/
        ESCI_INITCHANNEL_ID     = (uint8)0x0AU, /**< @brief
                                      ESCI_InitChannel() ID.*/
        ESCI_CHECKWAKEUP_ID     = (uint8)0x0BU, /**< @brief
                                      ESCI_CheckWakeup() ID.*/
        ESCI_IRQHANDLER_ID      = (uint8)0x0CU  /**< @brief
                                      ESCI_InterruptHandler() ID.*/
    } Lin_ESCI_ApiFunctionIds;


/*=================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/*=================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/
#define LIN_START_SEC_VAR_NO_INIT_8
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 
/* @violates @ref Lin_ESCI_h_REF_7 Array declared with unknown size */
/* @violates @ref Lin_ESCI_h_REF_8 Declaring an external identifier in a header file */
extern volatile VAR(uint8,LIN_VAR)Lin_au8LinChStatus[LIN_HW_MAX_MODULES];
/* @violates @ref Lin_ESCI_h_REF_7 Array declared with unknown size */
/* @violates @ref Lin_ESCI_h_REF_8 Declaring an external identifier in a header file */
extern volatile VAR(uint8,LIN_VAR)Lin_au8LinChFrameStatus[LIN_HW_MAX_MODULES];
/* @violates @ref Lin_ESCI_h_REF_7 Array declared with unknown size */
/* @violates @ref Lin_ESCI_h_REF_8 Declaring an external identifier in a header file */
extern VAR(uint8, LIN_VAR)Lin_au8TransmitHeaderCommand[LIN_HW_MAX_MODULES];
/* @violates @ref Lin_ESCI_h_REF_7 Array declared with unknown size */
/* @violates @ref Lin_ESCI_h_REF_8 Declaring an external identifier in a header file */
extern volatile VAR(uint8,LIN_VAR)Lin_au8LinChFrameErrorStatus[LIN_HW_MAX_MODULES];
/* @violates @ref Lin_ESCI_h_REF_7 Array declared with unknown size */
/* @violates @ref Lin_ESCI_h_REF_8 Declaring an external identifier in a header file */
extern VAR(sint8,LIN_VAR)Lin_as8ChannelHardwareMap[LIN_HW_MAX_AVAILABLE_MODULES];

#define LIN_STOP_SEC_VAR_NO_INIT_8
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_START_SEC_VAR_INIT_UNSPECIFIED
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 /* @violates @ref Lin_ESCI_h_REF_9  All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required */
extern P2CONST(Lin_ConfigType,LIN_VAR,LIN_APPL_CONST) Lin_pcConfigPtr;
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_STOP_SEC_VAR_INIT_UNSPECIFIED
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 /* @violates @ref Lin_ESCI_h_REF_7 Array declared with unknown size */
/* @violates @ref Lin_ESCI_h_REF_8 Declaring an external identifier in a header file */
extern P2CONST(Lin_ChannelConfigType,LIN_VAR,LIN_APPL_CONST)Lin_pChannelConfigPtr[LIN_HW_MAX_MODULES];
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
#define LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 /*=================================================================================================
                                     FUNCTION PROTOTYPES
=================================================================================================*/
#define LIN_START_SEC_CODE
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 /* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (void, LIN_CODE) Lin_ESCI_InterruptHandler(CONST(uint8, AUTOMATIC) u8Channel);

#ifdef LIN_USE_DMA
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
FUNC(void, LIN_CODE) Lin_ESCI_TxInterruptHandler_eDma(CONST(uint8, AUTOMATIC) u8Channel);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
/* @violates @ref Lin_ESCI_h_REF_4 Identifier shall not rely on the significance of more than 31 characters */
FUNC(void, LIN_CODE) Lin_ESCI_RxInterruptHandler_eDma(CONST(uint8, AUTOMATIC) u8Channel);
#endif

/*****************************************************************************
**                          Non-AUTOSAR LIN Low Level Driver API's          **
*****************************************************************************/
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (Std_ReturnType, LIN_CODE) Lin_ESCI_CheckWakeup(CONST(uint8, AUTOMATIC) u8Channel);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (void, LIN_CODE) Lin_ESCI_InitChannel(CONST(uint8, AUTOMATIC) u8Channel);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (Std_ReturnType, LIN_CODE) Lin_ESCI_SendHeader(CONST(uint8, AUTOMATIC) u8Channel, \
                                P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) pcPduInfoPtr);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (void, LIN_CODE) Lin_ESCI_SendResponse(CONST(uint8, AUTOMATIC) u8Channel, \
                                P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) pcPduInfoPtr);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (Std_ReturnType, LIN_CODE) Lin_ESCI_GoToSleep(CONST(uint8, AUTOMATIC) u8Channel);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (Std_ReturnType, LIN_CODE) Lin_ESCI_GoToSleepInternal(CONST(uint8, AUTOMATIC) u8Channel);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (void, LIN_CODE) Lin_ESCI_Wakeup(CONST(uint8, AUTOMATIC) u8Channel);
  /* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (Lin_StatusType, LIN_CODE) Lin_ESCI_HardwareGetStatus(CONST(uint8, AUTOMATIC) u8Channel, \
                                P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) pLinSduPtr);
/* @violates @ref Lin_ESCI_h_REF_6 Re-use of C90 reserved identifier */
FUNC (void, LIN_CODE) Lin_ESCI_CopyData(CONST(uint8, AUTOMATIC) u8Channel, \
                                P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) pLinSduPtr);

#define LIN_STOP_SEC_CODE
/*
* @violates @ref Lin_ESCI_h_REF_1 #include statements in a file should only be preceded
*        by other preprocessor directives or comments.
*/
/*
* @violates @ref Lin_ESCI_h_REF_2 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
 #include "MemMap.h"
 
#ifdef __cplusplus
}
#endif

#endif /* Lin_ESCI_H */

/** @} */
