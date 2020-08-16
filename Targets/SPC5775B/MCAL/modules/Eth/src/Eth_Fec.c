/**
*   @file    Eth_Fec.c
*   @version 1.0.1
*
*    @brief            FEC controller interface
*    @details          Implementation of the FEC controller interface for
*                      the Ethernet driver
*
*   @addtogroup ETH_DRIVER
*   @{
*/
/*==============================================================================
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
==============================================================================*/
/*==============================================================================
==============================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Eth_Fec_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, #include statements should only be
* preceded by other preprocessor directives or comments.
* The usage of the MemMap.h file violates this advisory rule, but this
* mechanism is used to properly place the code and variables into their
* sections.
*
* @section Eth_Fec_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, A compiler/linker shall be checked to
* ensure that 31 character significance and case sensitivity are supported for
* external identifiers. Name length of the macro is unfortunately longer than 31
* characters required by the agreed file template and cannot be changed. Authors
* of the template have not taken the MISRA rules into account.
* 
* @section Eth_Fec_c_REF_4
* Violates MISRA 2004 Required Rule 19.15, Repeated include file. Precautions
* shall be taken in order to prevent the contents of a header file being
* included twice. This is an approved violation of usage MemMap.h file used to
* create linkage sections.
* 
* @section Eth_Fec_c_REF_5
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only
* allowed form of pointer arithmetic. Array indexing shall only be applied to
* objects defined as an array type however most buffers are passed as pointer
* therefore pointer arithmetic is used to access their data. Accesses to the
* configuration structures in Post-Build variant are expected.
* 
* @section Eth_Fec_c_REF_7
* Violates MISRA 2004 Required Rule 11.1, Pointer to a function shall not be
* converted to anything else than integral type. This rule is not violated
* however the tool used for checks reports it therefore it must be commented
* here.
* 
* @section Eth_Fec_c_REF_8
* Violates MISRA 2004 Required Rule 13.7, Boolean operations whose results are
* invariant shall not be permitted. This condition is invariant only for
* PreCompile variant where is this behavior expected.
*
* @section Eth_Fec_c_REF_9
* Violates MISRA 2004 Advisory Rule 16.7, Pointers passed to the function should
* be pointing to const if the pointed memory is not modified within the
* function. This rule is violated because of API is defined in this way.
* 
* @section Eth_Fec_c_REF_10
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless
* external linkage is required. The APIs always require the external
* linkage. MISRA analysis tool does not see the linkage from upper layers
* therefore there is no violation.
* 
* @section Eth_Fec_c_REF_11
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only
* allowed form of pointer arithmetic. The MISRA analysis tool reports this
* violation badly if array of pointers is accessed even with the array indexing
* arithmetics - this is used in a post build configuration variant to access the
* configuration parameters. It is no violation but the tool bug however it must
* be documented anyway.
*
* @section Eth_Fec_c_REF_12
* Violates MISRA 2004 Required Rule 5.1,  Identifiers (internal and external)
* shall not rely on the significance of more than 31 characters.
* Name length of the macro is unfortunately longer than 31 characters required
* by the agreed file template and cannot be changed. Authors of the template
* have not taken the MISRA rules into account.
*
* @section Eth_Fec_c_REF_17
* Violates MISRA 2004 Required Rule 1.2,No reliance shall be placed
* on undefined or unspecified behavior. No reliance on undefined
* or unspecified behavior was not identified.
*
* @section Eth_Fec_c_REF_18
* Violates MISRA 2004 Required Rule 8.7,Objects shall be defined at block
* scope if they are only accessed from within a single function. This violation 
* is wrongly reported because the varialbe here has been drop by compiler. Other
* config will use this variable.
*
* @section Eth_Fec_c_REF_19
* Violates MISRA 2004 Advisory Rule 11.3, A cast shall not be performed between a
* pointer type and an integral type. The usage of pointers loaded by a
* computed address violates advisory this rule, but this mechanism is used
* to access memory mapped registers and data areas where  another approach
* is not feasible.
*
* @section Eth_Fec_c_REF_20
* Violates MISRA 2004 Required Rule 14.1, This rule refers to code which cannot under any circumstances be reached, 
* and which can be identified as such at compile-time
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

/*==============================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==============================================================================*/
#include "Eth.h" /* Includes also Eth_GeneralTypes.h, Eth_Cfg.h,
                    Eth_ComStack_Types.h, Dem.h, Det.h and
                    Mcal.h */
#include "SchM_Eth.h" /* RTE module header for critical sections protection */
#include "Eth_Fec_Counters.h"
#include "Eth_Fec.h" /* Own interface */
#include "StdRegMacros.h"
#include "EthIf_Cbk.h" /* EthIf callbacks to be called from Eth driver */

/*==============================================================================
*                              SOURCE FILE VERSION INFORMATION
==============================================================================*/

#define ETH_VENDOR_ID_C                      43
#define ETH_AR_RELEASE_MAJOR_VERSION_C       4
#define ETH_AR_RELEASE_MINOR_VERSION_C       0
/** @violates @ref Eth_Fec_c_REF_3 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_c_REF_12 MISRA rule 5.1 */
#define ETH_AR_RELEASE_REVISION_VERSION_C    3
#define ETH_SW_MAJOR_VERSION_C               1
#define ETH_SW_MINOR_VERSION_C               0
#define ETH_SW_PATCH_VERSION_C               1

/*==============================================================================
*                                     FILE VERSION CHECKS
==============================================================================*/
/* Check if current file and ETH header file are of the same vendor */
#if(ETH_VENDOR_ID_C != ETH_VENDOR_ID)
    #error "Eth_Fec.c and ETH.h have different vendor ids"
#endif
/* Check if current file and ETH header file are of the same Autosar version */
#if( (ETH_AR_RELEASE_MAJOR_VERSION_C    != ETH_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_AR_RELEASE_MINOR_VERSION_C    != ETH_AR_RELEASE_MINOR_VERSION) || \
     (ETH_AR_RELEASE_REVISION_VERSION_C != ETH_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Eth_Fec.c and Eth.h are different"
#endif
/* Check if current file and ETH header file are of the same Software version */
#if( (ETH_SW_MAJOR_VERSION_C != ETH_SW_MAJOR_VERSION) || \
     (ETH_SW_MINOR_VERSION_C != ETH_SW_MINOR_VERSION) || \
     (ETH_SW_PATCH_VERSION_C != ETH_SW_PATCH_VERSION) \
   )
    #error "Software Version Numbers of Eth_Fec.c and Eth.h are different"
#endif
/* Check if current file and Eth_FEC_LLD header file are of the same Autosar version */
#if( (ETH_AR_RELEASE_MAJOR_VERSION_C    != ETH_AR_RELEASE_MAJOR_VERSION_FEC) || \
     (ETH_AR_RELEASE_MINOR_VERSION_C    != ETH_AR_RELEASE_MINOR_VERSION_FEC) || \
     (ETH_AR_RELEASE_REVISION_VERSION_C != ETH_AR_RELEASE_REVISION_VERSION_FEC) \
   )
    #error "AutoSar Version Numbers of Eth_Fec.c and Eth_Fec.h are different"
#endif
/* Check if current file and Eth_FEC_LLD header file are of the same Software version */
#if( (ETH_SW_MAJOR_VERSION_C != ETH_SW_MAJOR_VERSION_FEC) || \
     (ETH_SW_MINOR_VERSION_C != ETH_SW_MINOR_VERSION_FEC) || \
     (ETH_SW_PATCH_VERSION_C != ETH_SW_PATCH_VERSION_FEC))
    #error "Software Version Numbers of Eth_Fec.c and Eth_Fec.h are different"
#endif
/* Check if current file and Eth_Fec_Counters.h header file are of the same Autosar version */
#if( (ETH_AR_RELEASE_MAJOR_VERSION_C    != ETH_AR_RELEASE_MAJOR_VERSION_CNT_H) || \
     (ETH_AR_RELEASE_MINOR_VERSION_C    != ETH_AR_RELEASE_MINOR_VERSION_CNT_H) || \
     (ETH_AR_RELEASE_REVISION_VERSION_C != ETH_AR_RELEASE_REVISION_VERSION_CNT_H))
    #error "AutoSar Version Numbers of Eth_Fec.c and Eth_Fec_Counters.h are different"
#endif
/* Check if current file and Eth_Fec_Counters.h header file are of the same Software version */
#if( (ETH_SW_MAJOR_VERSION_C != ETH_SW_MAJOR_VERSION_CNT_H) || \
     (ETH_SW_MINOR_VERSION_C != ETH_SW_MINOR_VERSION_CNT_H) || \
     (ETH_SW_PATCH_VERSION_C != ETH_SW_PATCH_VERSION_CNT_H))
    #error "Software Version Numbers of Eth_Fec.c and Eth_Fec_Counters.h are different"
#endif
/* Check if current file and StdRegMacros header file are of the same Software version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and StdRegMacros header file are of the same version */
    #if ((ETH_AR_RELEASE_MAJOR_VERSION_C != STDREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_AR_RELEASE_MINOR_VERSION_C != STDREGMACROS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Eth_Fec.c and StdRegMacros.h are different"
    #endif
    #if ((ETH_AR_RELEASE_MAJOR_VERSION_C != ETHIF_AR_RELEASE_MAJOR_VERSION) || \
         (ETH_AR_RELEASE_MINOR_VERSION_C != ETHIF_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Eth_Fec.c and EthIf_Cbk.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */
/*==============================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==============================================================================*/
/**
 * @brief       Item definition of multicast MAC address pool.
 * @details     This structure define an entry of MAC address pool which
 *              allows reception of multiple MAC address defined in
 *              Eth_FEC_LLD_MulticastPool array. Active parameter denote
 *              entries of MACAddress which will passed to receive
 *              call-back function.
 */
struct ETH_FEC_MULTICAST_POOL_ITEM
{
    VAR(boolean, ETH_VAR) bActive;
    VAR(uint8, ETH_VAR) au8PhysAddr[6];
};

/*==============================================================================
*                                       LOCAL MACROS
==============================================================================*/

/**
* @brief   Generation polynomial value
* @details Value of generation polynomial register for CRC32 calculation.
*          Correspond to active elements of generation polynomial function
*          x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8
*          + x^7 + x^5 + x^4 + x^2 + x^1 + 1 written from right to left
*          without base element x^32.
*/
#define ETH_FEC_LLD_CRC32_POLYVAL (0xEDB88320U)
/**
* @brief   Initial value of CRC32 calculation register
*/
#define ETH_FEC_LLD_CRC32_INITVAL (0xFFFFFFFFU)

/**
* @brief Wraps the registers base address - for future enhancements
*/

/**
* @brief Define the RX status
*/
/* RX Frame status bits - frame reception mode */
#define ETH_FEC_RXF_PROMISCUOUS     0x01000000U /* Frame received in promiscuous mode (would not be received if not promiscuous) */
#define ETH_FEC_RXF_BROADCAST       0x00800000U /* Frame received as broadcast */
#define ETH_FEC_RXF_MULTICAST       0x00400000U /* Frame received as multicast but
                                                             not broadcast */
#define ETH_FEC_RXF_MODE_MASK       0x01C00000U /* Mask for previous bits */
/* RX Frame status bits - errors and failures notification */
#define RXF_LENGTH_ERROR        0x00200000U /* Frame longer than configured
                                                      maximum of RX buffer */
#define ETH_FEC_RXF_NONOCTET_ERROR  0x00100000U /* Non octet aligned frame */
#define ETH_FEC_RXF_CRC_ERROR       0x00040000U /* CRC error */
#define ETH_FEC_RXF_OVERFLOW_ERROR  0x00020000U /* FIFO overrun during reception */
#define ETH_FEC_RXF_TRUNCATED       0x00010000U /* Frame had been longer than 2047B
                                               and therefore was truncated */
#define ETH_FEC_RXF_MAC_ERROR       0x80000000U /* MAC Error
                                                   (CRC, length error, etc.) */
#define ETH_FEC_RXF_PHY_ERROR       0x04000000U /* Invalid frame received, PHY Error */
#define ETH_FEC_RXF_COLLISION       0x02000000U /* Collision detected at reception */
#define ETH_FEC_RXF_ERRORS_MASK     0x86370000U /* Mask for previous bits */


#define ETH_FEC_RXF_VLAN_PRIORITY   0x0000E000U /* VLAN Priority Code Point */
#define ETH_FEC_RXF_VLAN_DETECTED   0x00000004U /* Received frame has a VLAN tag */
#define ETH_FEC_RXF_IP_HEADER_ERROR 0x00000020U /* IP header checksum error
                                               - bit is set for non IP
                                                 frames and for IP frames
                                                 with invalid header CRC */

#define ETH_FEC_RXF_PROTO_CRC_ERROR 0x00000010U /* Protocol CRC Error */
#define ETH_FEC_RXF_IPV6_FRAME      0x00000002U /* IPV6 Frame received */
#define ETH_FEC_RXF_IPV4_FRAGMENT   0x00000001U /* IPV4 Fragment */
/*==============================================================================
*                                      LOCAL CONSTANTS
==============================================================================*/
#define ETH_START_SEC_CONST_32
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"
/**
* @details Store Base Address of controller which is in used
*/
static CONST(uint32, ETH_VAR) Eth_u32BaseAddr[ETH_MAXCTRLS_SUPPORTED] =
{
#ifdef FEC_0_BASEADDR
/* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    (VAR(uint32, AUTOMATIC))FEC_0_BASEADDR,
#else
    #error There must be at always least one controller but the base address not defined (plugin inconsistency)
#endif
#if ETH_MAXCTRLS_SUPPORTED > 1U
  #ifdef FEC_1_BASEADDR
    (VAR(uint32, AUTOMATIC))FEC_1_BASEADDR
  #else     
    #error The base address for the second controller is not configured (plugin inconsistency)
  #endif
#endif
/* Additional controllers may be added here */

};
#define ETH_STOP_SEC_CONST_32
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

/*==================================================================================================
*                                      LOCAL VARIABLES
==============================================================================*/

#define ETH_START_SEC_VAR_INIT_BOOLEAN
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
    /**
     * @brief        Variable indicating multicast pool overflow
     * @details      Any time whenever count of active items in
     *               Eth_FEC_rMulticastPool could be greater than
     *               ETH_MULTICAST_POOL_SIZE this variable is set to TRUE
     *               and keeps TRUE until Eth_ControllerInit is called.
     */

    static VAR(boolean, ETH_VAR) Eth_FEC_bMcastPoolOvf[ETH_MAXCTRLS_SUPPORTED] = {(VAR(boolean, AUTOMATIC))FALSE};
    /* @brief        Multicast filter OPEN for all frames
     * @details      Multicast filtering is disabled and ALL frames are received.
     *               Means that all bytes of GAUR/GALR registers
     *               are set to 0xff and multicast filtering accept all frames
     *               at reception if the value is TRUE.
     */
    static VAR(boolean, ETH_VAR) Eth_FEC_bMcastFullOpen[ETH_MAXCTRLS_SUPPORTED] = {(VAR(boolean, AUTOMATIC))FALSE};
#endif /* ETH_UPDATE_PHYS_ADDR_FILTER */

#define ETH_STOP_SEC_VAR_INIT_BOOLEAN
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

#define ETH_START_SEC_VAR_INIT_16
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER

    /**
    * @brief          Number of active items inside multicast filter pool
    * @details        This variable is incremented with each added item to pool
    *                 and decremented with remove. Value is set to zero at pool
    *                 clean function.
    */
    static VAR(uint16, ETH_VAR) Eth_FEC_u16McastItemsCnt[ETH_MAXCTRLS_SUPPORTED] = {0U};

#endif  /* ETH_UPDATE_PHYS_ADDR_FILTER */
#define ETH_STOP_SEC_VAR_INIT_16
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

#define ETH_START_SEC_VAR_INIT_32
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

/**
* @brief    Address of Tx buffers ring start
* @details  Used for optimization of buffer address computation.
*           It is initialized during TX buffers initialization.
*/
static VAR(uint32, ETH_VAR) Eth_FEC_u32TxBufStartAddr[ETH_MAXCTRLS_SUPPORTED]={0U};

/**
* @brief    Address of Rx buffers ring start
* @details  Used for optimization of buffer address computation.
*           It is initialized during RX buffers initialization.
*/
static VAR(uint32, ETH_VAR) Eth_FEC_u32RxBufStartAddr[ETH_MAXCTRLS_SUPPORTED]={0U};
#define ETH_STOP_SEC_VAR_INIT_32
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"




#define ETH_START_SEC_VAR_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"
/**
* @brief          Active receive buffer descriptor index
* @details        This variable contains number of the buffer descriptor which
*                 will be used  for the first reception from the time of the
*                 last call of the receive function.
* @implements     Eth_u8ActiveRxBuf_Object
*/
/** @violates @ref Eth_Fec_c_REF_10 MISRA rule 8.10 */    
VAR(volatile uint8, ETH_VAR) Eth_u8ActiveRxBuf[ETH_MAXCTRLS_SUPPORTED] = {0U};
/** @violates @ref Eth_Fec_c_REF_10 MISRA rule 8.10 */
/**
* @brief        Index of buffer where to continue search for free buffers
* @details      This variable is used to reduce buffer memory fragmentation.
*               Algorithm tries to allocate new buffers right after previously
*               allocated buffers.
*/
static VAR(uint8, ETH_VAR) Eth_FEC_u8SearchTxBufFrom[ETH_MAXCTRLS_SUPPORTED] = {0U};
#define ETH_STOP_SEC_VAR_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"


#define ETH_START_SEC_VAR_NO_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"
/**
* @brief        Array of references to BD for each buffer.
* @details      Use buffer index for indexing this array.
*               It contains index of buffer descriptor this buffer belongs to.
*               The value is valid only if at least this flags are set on the
*               buffer: FEC_TXB_LOCK_U8 | FEC_TXB_LINK_U8 | FEC_TXB_FIRST_U8.
*               Otherwise the buffer is not linked with any BD or is not first
*               buffer of frame. */
static VAR(uint8, ETH_VAR) Eth_au8TxBdOfBuf[ETH_MAXCTRLS_SUPPORTED][ETHTXBUFNUM];

/**
* @brief        An array containing buffer flags.
* @details      Use buffer index for indexing this array.
*               It contains 4 flags for each buffer:
*               TXB_LOCK 8, TXB_CONF 4, TXB_LINK 2, TXB_FIRST 1 */
/** @violates @ref Eth_Fec_c_REF_10 MISRA rule 8.10 */    
VAR(volatile uint8, ETH_VAR) Eth_au8TxBufFlags[ETH_MAXCTRLS_SUPPORTED][ETHTXBUFNUM];
/** @violates @ref Eth_Fec_c_REF_10 MISRA rule 8.10 */
#if STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES
/**
* @brief        Number of buffers allocated together for one frame
* @details      Use buffer index for indexing this array.
*               Value is valid only if at least following flags are set on the
*               buffer: FEC_TXB_LOCK_U8 | FEC_TXB_FIRST_U8
*/
static VAR(uint8, ETH_VAR) Eth_FEC_au8TxBufGroup[ETH_MAXCTRLS_SUPPORTED][ETHTXBUFNUM];
#endif  /* STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES */

#define ETH_STOP_SEC_VAR_NO_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"


/** @violates @ref Eth_Fec_c_REF_3 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_c_REF_12 MISRA rule 5.1 */
#define ETH_START_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
* @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
*/
#include "MemMap.h"
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
/*
 * @brief        Pool multicast MAC address
 * @details      This is an array of structure of allowed MAC address
 *               for multicast frame reception.
 */
static struct VAR(ETH_FEC_MULTICAST_POOL_ITEM, ETH_VAR) Eth_FEC_rMulticastPool[ETH_MAXCTRLS_SUPPORTED][ETH_MULTICAST_POOL_SIZE];

#endif /* ETH_UPDATE_PHYS_ADDR_FILTER */

/** @violates @ref Eth_Fec_c_REF_3 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_c_REF_12 MISRA rule 5.1 */
#define ETH_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

/*==============================================================================
*                                      GLOBAL CONSTANTS
==============================================================================*/


/*==============================================================================
*                                      GLOBAL VARIABLES
==============================================================================*/
#define ETH_START_SEC_VAR_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"



/**
* @brief          Active transmit buffer descriptor index
* @details        This variable contains index of the buffer descriptor where
*                 new transmission shall be queued.
* @implements     Eth_u8ActiveTxBD_Object
* @violates @ref Eth_Fec_c_REF_10 MISRA rule 8.10 
*/
VAR(volatile uint8, ETH_VAR) Eth_u8ActiveTxBD[ETH_MAXCTRLS_SUPPORTED] = {0U};

/**
* @brief          Counter of the locked TX buffers
* @details        This variable is incremented with each buffer to be confirmed
*                 transmission and decremented by confirmation of such buffer
*                 thus it holds number of the buffers to be confirmed. It is
*                 used for optimization of the buffers search algorithm.
*/
/** @violates @ref Eth_Fec_c_REF_10 MISRA rule 8.10 */
VAR(uint8, ETH_VAR) Eth_u8LockedTxBufCount[ETH_MAXCTRLS_SUPPORTED] = {0U};

#define ETH_STOP_SEC_VAR_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"


#define ETH_START_SEC_VAR_NO_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"


#define ETH_STOP_SEC_VAR_NO_INIT_8
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"


/** @violates @ref Eth_Fec_c_REF_3 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_c_REF_12 MISRA rule 5.1 */
#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

#if VARIANT_PRE_COMPILE != ETH_CONFIG_VARIANT
/**
* @brief          Used for internal storage of configuration pointer
* @details        This variable is used to store the pointer to the instance
*                 of the Eth_ConfigType containing the configuration parameter,
*                 which is passed to the Eth_Init function, for the subsequent
*                 accesses.
*
* @note           This variable exists only if the Pre-Compile variant is not
*                 selected.
*
*/
/** @violates @ref Eth_Fec_c_REF_10 MISRA rule 8.10 */
P2CONST(Eth_ConfigType, ETH_VAR, ETH_APPL_CONST) Eth_InternalCfgPtr = NULL_PTR;
#endif

/** @violates @ref Eth_Fec_c_REF_3 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_c_REF_12 MISRA rule 5.1 */
#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"


/*==============================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==============================================================================*/
#define ETH_START_SEC_CODE
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
static FUNC(uint32, ETH_CODE) Eth_Fec_GetCRC32Hash  ( \
                       CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pData, \
                       VAR(uint32, AUTOMATIC) u32Length \
                                                    );
static FUNC(boolean, ETH_CODE) Eth_Fec_ComparePhysAddr  ( \
                                    CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhyAddrA, \
                                    CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhyAddrB \
                                                        );
static FUNC(boolean, ETH_CODE) Eth_Fec_IsAddrInMcastPool    ( \
                                    CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                                    CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr, \
                                    CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pPoolItemIdx \
                                                            );
static FUNC(boolean, ETH_CODE) Eth_Fec_McastPoolAddItem(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr);
static FUNC(boolean, ETH_CODE) Eth_Fec_McastPoolRmvItem(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr);
static FUNC(void, ETH_CODE) Eth_Fec_McastPoolClean(CONST(uint8, AUTOMATIC) u8CtrlIdx);
static FUNC(void, ETH_CODE) Eth_Fec_McastGAAdd(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr);
static FUNC(void, ETH_CODE) Eth_Fec_McastGARecalculate(CONST(uint8, AUTOMATIC) u8CtrlIdx);
static FUNC(boolean, ETH_CODE) Eth_Fec_IsPhysAddrAllowed    ( \
                    CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                    CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr \
                                                                );
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_McastGAClean(CONST(uint8, AUTOMATIC) u8CtrlIdx);
#endif /* ETH_UPDATE_PHYS_ADDR_FILTER */
static FUNC(Eth_RxBufferType, ETH_CODE) Eth_Fec_GetRxBufferType ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint8, AUTOMATIC) u8Buf, \
                        CONST(uint8, AUTOMATIC) u8BufCtrMax, \
                        CONSTP2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pMultiEnd \
                                                                );
static FUNC(void, ETH_CODE) Eth_Fec_GetRxBufferData ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint8, AUTOMATIC) u8Buf, \
                        CONST(uint8, AUTOMATIC) u8MultiEnd, \
                        CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pLength, \
                        P2P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) pDataPtr, \
                        CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) pStatusPtr \
                                                    );
static FUNC(void, ETH_CODE) Eth_Fec_ClearRxBuffer   ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint8, AUTOMATIC) u8BufIdx \
                                                    );
static FUNC(void, ETH_CODE) Eth_Fec_GiveBackTxBuffer( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        VAR(uint8, AUTOMATIC) u8BufIdx \
                                                    );
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteRxBDBits ( \
                                        CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                        CONST(uint8, AUTOMATIC) u8Bufnum, \
                                        CONST(uint32, AUTOMATIC) u32Data \
                                                        );
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteRxBDBufPtr   ( \
                                        CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                        CONST(uint8, AUTOMATIC) u8Bufnum, \
                                        CONST(uint32, AUTOMATIC) u32Data \
                                                            );
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteTxBDBufPtr   ( \
                                        CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                        CONST(uint8, AUTOMATIC) u8BdIdx, \
                                        CONST(uint32, AUTOMATIC) u32DataAddr \
                                                            );
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ReadRxBDBits(CONST(uint32, AUTOMATIC)u32BaseAddr, CONST(uint8, AUTOMATIC) u8Bufnum);
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_Write16TxBufMem   ( \
                                        CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                        CONST(uint32, AUTOMATIC)u32Offset, \
                                        CONST(uint16, AUTOMATIC) u16Data \
                                                            );
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ComputeTxBufAddr(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(uint8, AUTOMATIC) u8BufIdx);
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ComputeRxBufAddr(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(uint8, AUTOMATIC) u8BufIdx);
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteTxBDBits ( \
                                        CONST(uint32, AUTOMATIC) u32BaseAddr, \
                                        CONST(uint8, AUTOMATIC) u8BdIdx, \
                                        CONST(uint32, AUTOMATIC) u32DataAddr \
                                                        );
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ReadTxBDBits    ( \
                                        CONST(uint32, AUTOMATIC) u32BaseAddr, \
                                        CONST(uint8, AUTOMATIC) u8BdIdx \
                                                            );
/*==============================================================================
*                                       LOCAL FUNCTIONS
==============================================================================*/

#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
/**
 * @brief       Calculation of CRC32 hash
 * @details     This function calculates a CRC32 checksum of data of specified
 *              length.
 * @param[in]   pData Pointer to data array of bytes which CRC checksum has
 *              to be calculated.
 * @param[in]   u32Length Specifies the number of bytes of data array.
 * @return      CRC32 checksum.
 */
static FUNC(uint32, ETH_CODE) Eth_Fec_GetCRC32Hash (CONSTP2CONST(uint8, AUTOMATIC, ETH_VAR) pData, VAR(uint32, AUTOMATIC) u32Length)
{
    VAR(uint32, AUTOMATIC) u32CRC32Hash;    /* CRC hash output register */
    VAR(uint32, AUTOMATIC) u32CRC32ByteIdx; /* Index of data byte */
    VAR(uint8, AUTOMATIC) u8CRC32BitIdx;    /* Index of bit inside
                                               CRC32 calculated byte */

    u32CRC32Hash = ETH_FEC_LLD_CRC32_INITVAL;
    /* Loop over all bytes */
    for(u32CRC32ByteIdx = 0U; u32CRC32ByteIdx < u32Length; u32CRC32ByteIdx++)
    {
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        u32CRC32Hash ^= *(pData + u32CRC32ByteIdx);
        /* Loop over bits */
        for(u8CRC32BitIdx = 0U; 8U > u8CRC32BitIdx; u8CRC32BitIdx++)
        {
            u32CRC32Hash = (u32CRC32Hash >> 1) ^ ((~(u32CRC32Hash & 0x1U) + 0x1U) & ETH_FEC_LLD_CRC32_POLYVAL);
        }
    }
    return u32CRC32Hash;
}

/**
 * @brief       Compare two input physical addresses
 * @details     This function compares physical address pPhyAddrA
 *              against pPhyAddrB. In case that addresses match the TRUE
 *              is returned and FALSE otherwise.
 * @param[in]   pPhyAddrA Pointer to the first physical address array.
 * @param[in]   pPhyAddrB Pointer to the second physical address array.
 * @caution     Length of physical address is restricted to 6B!
 * @return      TRUE - addresses matches
 *              FALSE - otherwise
 */
static FUNC(boolean, ETH_CODE) Eth_Fec_ComparePhysAddr  ( \
                       CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhyAddrA, \
                       CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhyAddrB \
                                                        )
{
    /* Return variable */
    VAR(boolean, ETH_VAR) bReturn = (VAR(boolean, ETH_VAR))TRUE;
    VAR(uint8, AUTOMATIC) u8Count;
    
    for (u8Count=0U; u8Count<6U; u8Count++)
    {
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        if (pPhyAddrA[u8Count] != pPhyAddrB[u8Count])
        { 
            /* Addresses are the same */
            bReturn = (VAR(boolean, ETH_VAR))FALSE;
            break;
        }
    }
    return bReturn;
}

/**
 * @brief       Add item into multicast pool
 * @details     This function checks if the added address is not already in the
 *              pool and if not add it.
 * @note        This function does not take care about overflow flag.
 * @param[in]   u8CtrlIdx Index of controller which will be added item
 * @param[in]   pPhysAddrPtr Pointer to Physical address which shall be
 *              added
 * @return      TRUE - item/addresses was added successfully or item is already
 *                     in the table
 *              FALSE - table is full
 */
static FUNC(boolean, ETH_CODE) Eth_Fec_McastPoolAddItem(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr)
{
    /* Temporary return variable / Matching entry found */
    VAR(boolean, AUTOMATIC) bReturnVariable = (VAR(boolean, AUTOMATIC))FALSE;
    /* Index of pool entry */
    VAR(uint16, AUTOMATIC) u16PoolIdx = 0U;
    VAR(uint8, AUTOMATIC) u8Count = 0U;

    /** @violates @ref Eth_Fec_c_REF_17 MISRA rule 1.2 */
    if ((VAR(boolean, AUTOMATIC))TRUE == Eth_Fec_IsAddrInMcastPool(u8CtrlIdx, pPhysAddrPtr, &u16PoolIdx))
    { /* Item already in the table */
        bReturnVariable = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else if (ETH_MULTICAST_POOL_SIZE == Eth_FEC_u16McastItemsCnt[u8CtrlIdx])
    { /* Table is full */
        bReturnVariable = (VAR(boolean, AUTOMATIC))FALSE;
    }
    else
    { /* Item is not in the table - Look for empty position*/
        while (ETH_MULTICAST_POOL_SIZE > u16PoolIdx)
        { /* Loop over table items */
            if ((VAR(boolean, AUTOMATIC))FALSE == Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].bActive)
            { /* First empty item in table */
                /* Mark found item as used - active */
                Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].bActive = (VAR(boolean, AUTOMATIC))TRUE;
                /* Write address to the pools */
                for (u8Count=0U; u8Count<6U; u8Count++)
                {
                    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
                    Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].au8PhysAddr[u8Count]=pPhysAddrPtr[u8Count];
                }
                /* Increment the count of used items */
                Eth_FEC_u16McastItemsCnt[u8CtrlIdx]++;
                /* Set return variable */
                bReturnVariable = (VAR(boolean, AUTOMATIC))TRUE;
                break;
            } /* Active item check */
            u16PoolIdx++;
        } /* Items loop */
    } /* Table check */
    return bReturnVariable;
}

/**
* @brief         Remove the physical address from the pool.
* @details       This function goes over multicast pool and is checking
*                if the specified physical address is located and activated
*                in the multicast pool.
* @param[in]     u8CtrlIdx Index of controller in which item will be removed
* @param[in]     pPhysAddrPtr Pointer to physical address which shall be
*                removed
* @note          This function does not take care about overflow flag.
* @return        TRUE - address was removed from the pool
*                FALSE - address was not found in the pool
*/
static FUNC(boolean, ETH_CODE) Eth_Fec_McastPoolRmvItem(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr)
{
    /* Index of pool entry */
    VAR(uint16, AUTOMATIC) u16PoolIdx = 0U;
    /* Return variable */
    VAR(boolean, AUTOMATIC) bReturnVariable;

    /* Look for item in the table */
    /** @violates @ref Eth_Fec_c_REF_17 MISRA rule 1.2 */
    if ((VAR(boolean, AUTOMATIC))TRUE ==  Eth_Fec_IsAddrInMcastPool(u8CtrlIdx, pPhysAddrPtr, &u16PoolIdx))
    { /* Item was found in the table at position u16PoolIdx */
        /* Deactivate it */
        Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].bActive = (VAR(boolean, AUTOMATIC))FALSE;
        /* Decrement count of used pool items */
        Eth_FEC_u16McastItemsCnt[u8CtrlIdx]--;
        /* Set return variable */
        bReturnVariable = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else
    { /* Item is not in the table */
        bReturnVariable = (VAR(boolean, AUTOMATIC))FALSE;
    }
    return bReturnVariable;
}

/**
* @brief         Check whenever the specified physical address is in
*                multicast pool.
* @details       This function goes over multicast pool and is checking
*                if the specified physical address is located and activated
*                in the multicast pool.
* @param[in]     u8CtrlIdx Index of controller in which the address will be checked
* @param[in]     pPhysAddrPtr This parameter is a pointer at tested
*                physical address.
* @param[out]    pPoolItemIdx Index of found Eth_FEC_rMulticastPool
*                item. This value is valid only if TRUE is returned.
* @return        TRUE - address is in the pool and active
*                FALSE - address is not in the pool
*/
static FUNC(boolean, ETH_CODE) Eth_Fec_IsAddrInMcastPool    ( \
                CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr, \
                CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pPoolItemIdx \
                                                            )
{
    /* Temporary return variable / Matching entry found */
    VAR(boolean, AUTOMATIC) bAddressFound = (VAR(boolean, AUTOMATIC))FALSE;
    /* Index of pool entry */
    VAR(uint16, AUTOMATIC) u16PoolIdx = 0U;
    /* Used for counting of found active items in loop */
    VAR(uint16, AUTOMATIC) u16TmpActiveFound = 0U;

    /* Loop over multicast pool */
    while((u16TmpActiveFound !=  Eth_FEC_u16McastItemsCnt[u8CtrlIdx]) && (ETH_MULTICAST_POOL_SIZE > u16PoolIdx))
    {
        /* Filter only active entries */
        if((VAR(boolean, AUTOMATIC))TRUE == Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].bActive)
        { /* Item is active */
            if ((VAR(boolean, AUTOMATIC))TRUE == Eth_Fec_ComparePhysAddr(pPhysAddrPtr, Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].au8PhysAddr))
            { /* Item matches with requested */
                bAddressFound = (VAR(boolean, AUTOMATIC))TRUE;
                *pPoolItemIdx = u16PoolIdx;
                break;
            }
            u16TmpActiveFound++;
        }
        u16PoolIdx++;
    }
    return bAddressFound;
    /** @violates @ref Eth_Fec_c_REF_9 MISRA rule 16.7 */
}
/**
* @brief         Wipe all items of the pool.
* @details       This function goes over all items in the pool and sets
*                the active flag to FALSE
* @param[in]     u8CtrlIdx Index of controller which will be cleaned
* @note          This function does not take care about pool overflow
*/
static FUNC(void, ETH_CODE) Eth_Fec_McastPoolClean(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /* Index of pool entry */
    VAR(uint16, AUTOMATIC) u16PoolIdx = 0U;

    while (ETH_MULTICAST_POOL_SIZE > u16PoolIdx)
    {
        Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].bActive = (VAR(boolean, AUTOMATIC))FALSE;
        u16PoolIdx++;
    }
    Eth_FEC_u16McastItemsCnt[u8CtrlIdx] = 0U;
}

/**
* @brief         Enables Group Address reception for requested Physical Address
* @details       This function decides which register of GAUR/GALR is affected
*                and sets related bit for requested Physical Address reception
*                enablement.
* @param[in]     u8CtrlIdx Index of controller which will be updated GAA
* @param[in]     pPhysAddrPtr Pointer to Physical Address which group
*                shall be enabled.
*/
static FUNC(void, ETH_CODE) Eth_Fec_McastGAAdd(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr)
{
    /* Storage of CRC32 hash of Physical Address */
    VAR(uint32,AUTOMATIC) u32TmpCRC32Hash;
    /* Manipulation variable */
    VAR(uint32,AUTOMATIC) u32ManipulationVar;

    /* Once pool overflow was detected the recalculation of
    * the GAUR/GALR registers can not be used anymore.
    * Only new group reception bit can be enabled. */
    /* Calculate CRC32 hash */
    u32TmpCRC32Hash = Eth_Fec_GetCRC32Hash(pPhysAddrPtr, 6U);
    /* Estimate address group number
    * NOTE: Destination hash group is in GAUR/GALR register
    *       Group number is in six most significant bits
    *       in CRC32MacHash without MSB which decide about
    *       GAUR/GALR
    */
    if(1U == (u32TmpCRC32Hash >> 31U))
    { /* Address is in group located in GAUR register */
        /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        u32ManipulationVar = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GAUR_ADDR16);
        u32ManipulationVar |= ((1UL << ((u32TmpCRC32Hash >> 26UL) & 0x1FUL)));
        /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GAUR_ADDR16, u32ManipulationVar);
    }
    else
    { /* Address is in group located in GALR register */
        /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        u32ManipulationVar = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GALR_ADDR16);
        u32ManipulationVar |= ((1UL << ((u32TmpCRC32Hash >> 26UL) & 0x1FUL)));
        /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GALR_ADDR16, u32ManipulationVar);
    }
}

/**
* @brief         Recalculates and updates the values of GALR/GAUR registers.
* @details       This function goes over active multicast pool items
*                and calculates the values of GAUR/GALR registers.
* @param[in]     u8CtrlIdx Index of controller in which GA will be recalculated
*/
static FUNC(void, ETH_CODE) Eth_Fec_McastGARecalculate(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /* Used for counting of found active items in loop */
    VAR(uint16, AUTOMATIC) u16TmpActiveFound = 0U;
    /* Temporary storage of CRC32 hash  */
    VAR(uint32, AUTOMATIC) u32TmpCRC32Hash;
    /* Used for calculation of value for FEC_GALR_ADDR16 register */
    VAR(uint32, AUTOMATIC) u32TmpGALR = 0U;
    /* Used for calculation of value for FEC_GAUR_ADDR16 register */
    VAR(uint32, AUTOMATIC) u32TmpGAUR = 0U;
    /* Current item index */
    VAR(uint16, AUTOMATIC) u16PoolIdx = 0U;

    while ((u16TmpActiveFound != Eth_FEC_u16McastItemsCnt[u8CtrlIdx]) && (ETH_MULTICAST_POOL_SIZE > u16PoolIdx))
    { /* Go over pool till ends or all active items were processed  */
        if ((VAR(boolean, AUTOMATIC))TRUE == Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].bActive)
        { /* Filter only active items */
            /* Calculate CRC32 hash */
            u32TmpCRC32Hash = Eth_Fec_GetCRC32Hash(Eth_FEC_rMulticastPool[u8CtrlIdx][u16PoolIdx].au8PhysAddr, 6U);
            /* Estimate address group number
             * NOTE: Destination hash group is in GAUR/GALR register
             *       Group number is in six most significant bits
             *       in CRC32MacHash without MSB which decide about
             *       GAUR/GALR
             */
            if(1U == (u32TmpCRC32Hash >> 31U))
            { /* Address is in group located in GAUR register */
                u32TmpGAUR |= ((1UL << ((u32TmpCRC32Hash >> 26UL) & 0x1FUL)));
            }
            else
            { /* Address is in group located in GALR register */
                u32TmpGALR |= ((1UL << ((u32TmpCRC32Hash >> 26UL) & 0x1FUL)));
            }
            u16TmpActiveFound++;
        }
        u16PoolIdx++;
    }
    /* Write GAUR register */
    /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GAUR_ADDR16, u32TmpGAUR);
    /* Write GALR register */
    /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GALR_ADDR16, u32TmpGALR);
}

/**
* @brief         Clean GALR/GAUR registers.
* @details       This function disable reception of all multicast address groups
*                by seting of 0x00U to GAUR and GALR registers.
* @param[in]     u8CtrlIdx Index of controller in which GA will be cleaned
*/
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_McastGAClean(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /* Clear group address upper register */
    /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GAUR_ADDR16, 0U);
    /* Clear group address lower register */
    /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GALR_ADDR16, 0U);
}

/*================================================================================================*/
/**
* @brief         Check whenever the specified physical address
*                is allowed for reception.
* @details       This function checks the filter statuses and look into
*                multicast pool whether reception is allowed for specified
*                physical address.
* @param[in]     u8CtrlIdx Index of controller to be checked
* @param[in]     copu32PhysAddrPtr Pointer to physical address in network byte
*                order.
* @return        bReceptionAllowed Boolean value which defines that the frame
*                is contained in the pool (TRUE) or not (FALSE).
*/
static FUNC(boolean, ETH_CODE) Eth_Fec_IsPhysAddrAllowed(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONSTP2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr)
{
    /* Return variable */
    VAR(boolean, AUTOMATIC) bReceptionAllowed;
    /* Multicast Pool table item index */
    VAR(uint16, AUTOMATIC) u16McastPoolIdx;

    if ((VAR(boolean, AUTOMATIC))TRUE == Eth_FEC_bMcastPoolOvf[u8CtrlIdx])
    { /* Multicast filter overflow detected */
        bReceptionAllowed = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else if ((VAR(boolean, AUTOMATIC))TRUE == Eth_FEC_bMcastFullOpen[u8CtrlIdx])
    { /* Filter is fully open */
        bReceptionAllowed = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else
    { 
        /** @violates @ref Eth_Fec_c_REF_17 MISRA rule 1.2 */       
        bReceptionAllowed = Eth_Fec_IsAddrInMcastPool(u8CtrlIdx, pPhysAddrPtr, &u16McastPoolIdx);
    }
    return bReceptionAllowed;
}
#endif /* ETH_UPDATE_PHYS_ADDR_FILTER */

/* Access to the buffer descriptor status bits and the data pointer: */
/*============================================================================*/
/**
* @brief          Writes the Receive buffer descriptor status bits.
* @details        32 bit long value containing status bits in upper 16 bits and
*                 buffer length in lower 16 bits is written into the given
*                 buffer descriptor.
* @param[in]      u32BaseAddr Starting address of the Receive buffer descriptors ring
* @param[in]      u8Bufnum Index of the buffer descriptor to be written
* @param[in]      u32Data Status bits and buffer length to be written into
*                 the descriptor
* @note           This function is an inline function.
*/
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteRxBDBits ( \
                                CONST(uint32, AUTOMATIC) u32BaseAddr, \
                                CONST(uint8, AUTOMATIC) u8Bufnum, \
                                CONST(uint32, AUTOMATIC) u32Data  \
                                                        )
{
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 
    */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    *((P2VAR(volatile uint32, AUTOMATIC, ETH_APPL_DATA))(u32BaseAddr + (u8Bufnum * (VAR(uint32, AUTOMATIC))8U))) = u32Data;
}
/*============================================================================*/
/**
* @brief          Writes a data buffer address into the Receive buffer
*                 descriptor pointer.
* @param[in]      u32BaseAddr Starting address of the Receive buffer descriptors ring
* @param[in]      u8Bufnum Index of the buffer descriptor to be written
* @param[in]      u32Data Address to be written into the buffer pointer.
* @note           This function is an inline function.
*/
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteRxBDBufPtr   ( \
                                    CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                    CONST(uint8, AUTOMATIC) u8Bufnum, \
                                    CONST(uint32, AUTOMATIC) u32Data \
                                                            )
{
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 
    */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    *((P2VAR(volatile uint32, AUTOMATIC, ETH_APPL_DATA))(u32BaseAddr + 4U + (u8Bufnum * (VAR(uint32, AUTOMATIC))8U))) = u32Data;
}
/*============================================================================*/
/**
* @brief          Writes a data buffer address into the Transmit buffer
*                 descriptor pointer.
* @param[in]      u32BaseAddr Starting address of the Transmit buffer
*                 descriptors ring.
* @param[in]      u8BdIdx Index of the buffer descriptor to be written.
* @param[in]      u32DataAddr Address to be written into the buffer pointer.
* @note           This function is an inline function.
*/
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteTxBDBufPtr   ( \
                                    CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                    CONST(uint8, AUTOMATIC) u8BdIdx, \
                                    CONST(uint32, AUTOMATIC) u32DataAddr \
                                                            )
{
    /**  
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 
    */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    *((P2VAR(volatile uint32, AUTOMATIC, ETH_APPL_DATA))(u32BaseAddr + 4U + (u8BdIdx * (VAR(uint32, AUTOMATIC))8U))) = u32DataAddr;
}
/*============================================================================*/
/**
* @brief          Reads the status bits from the Receive buffer descriptor
* @param[in]      u32BaseAddr Starting address of the Receive buffer descriptors ring
* @param[in]      u8Bufnum Index of the buffer descriptor to be read
* @return         Read status bits (upper 16 bits) and buffer length
*                 (lower 16 bits)
* @note           This function is an inline function.
*/
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ReadRxBDBits    ( \
                                    CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                    CONST(uint8, AUTOMATIC) u8Bufnum \
                                                            )
{
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 
    */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    return *((P2VAR(volatile uint32, AUTOMATIC, ETH_APPL_DATA))(u32BaseAddr + (u8Bufnum * (VAR(uint32, AUTOMATIC))8U)));
}

/* Access to the buffer data functions: */
/*============================================================================*/
/**
* @brief          Writes the 16 bit long data into the memory
* @details        This function abstracts the write access into the transmit
*                 buffer memory. The transmit buffer is identified by its
*                 beginning i.e. base address and the offset specifies where to
*                 write the data.
* @param[in]      u32BaseAddr Base address where to write
* @param[in]      u32Offset Offset to be added to base address before the write
* @param[in]      u16Data The 16 bit long data to be written into the buffer.
* @note           This function is an inline function. It is used to ensure
*                 aligned accesses into the buffer on all target platforms.
*/
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_Write16TxBufMem   ( \
                                CONST(uint32, AUTOMATIC)u32BaseAddr, \
                                CONST(uint32, AUTOMATIC)u32Offset, \
                                CONST(uint16, AUTOMATIC) u16Data \
                                                            )
{
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 
    */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    *((P2VAR(volatile uint16, AUTOMATIC, ETH_APPL_DATA))(u32BaseAddr + (u32Offset))) = u16Data;
}

/*============================================================================*/
/**
* @brief        Compute address of TX buffer with given index
* @details      Type of the value of this macro is uint32
* @param[in]    u8CtrlIdx Index of controller we are working with
* @param[in]    u8BufIdx Index of buffer we need address of.
* @return       Address of beginning of given TX buffer.
*/
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ComputeTxBufAddr    ( \
                                         CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                                         CONST(uint8, AUTOMATIC) u8BufIdx \
                                                                )
{
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    return ( Eth_FEC_u32TxBufStartAddr[u8CtrlIdx] + ((VAR(uint32, AUTOMATIC))ETH_CFG_CTRLTXBUFLENBYTE(u8CtrlIdx) * u8BufIdx));
}

/*============================================================================*/
/**
* @brief        Compute address of RX buffer with given index
* @details      Type of the value of this macro is uint32
* @param[in]    u8CtrlIdx Index of controller we are working with
* @param[in]    u8BufIdx Index of buffer we need address of.
* @return       Address of beginning of given RX buffer.
*/
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ComputeRxBufAddr    ( \
                                         CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                                         CONST(uint8, AUTOMATIC) u8BufIdx \
                                                                )
{
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    return (Eth_FEC_u32RxBufStartAddr[u8CtrlIdx] + ((VAR(uint32, AUTOMATIC))ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx) * u8BufIdx));
}

/*============================================================================*/
/**
* @brief          Writes the Transmit buffer descriptor status bits.
* @details        32 bit long value containing status bits in upper 16 bits and
*                 buffer length in lower 16 bits is written into the given
*                 buffer descriptor.
* @param[in]      u32BaseAddr Starting address of the Transmit buffer
*                 descriptors ring.
* @param[in]      u8BdIdx Index of the buffer descriptor to be written
* @param[in]      u32DataAddr Status bits and buffer length to be written into
*                 the descriptor
*/
LOCAL_INLINE FUNC(void, ETH_CODE) Eth_Fec_WriteTxBDBits  ( \
                                    CONST(uint32, AUTOMATIC) u32BaseAddr, \
                                    CONST(uint8, AUTOMATIC) u8BdIdx, \
                                    CONST(uint32, AUTOMATIC) u32DataAddr \
                                            )
{
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 
    */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    *((P2VAR(volatile uint32, AUTOMATIC, ETH_APPL_DATA))(u32BaseAddr + (u8BdIdx * (VAR(uint32, AUTOMATIC))8U))) = u32DataAddr;
}

/*============================================================================*/
/**
* @brief          Reads the status bits from the Transmit buffer descriptor
* @param[in]      u32BaseAddr Starting address of the Transmit buffer
*                 descriptors ring.
* @param[in]      u8BdIdx Index of the buffer descriptor to be read.
* @return         Read status bits (upper 16 bits) and buffer length
*                 (lower 16 bits)
* @note           This function is an inline function.
*/
LOCAL_INLINE FUNC(uint32, ETH_CODE) Eth_Fec_ReadTxBDBits ( \
                                    CONST(uint32, AUTOMATIC) u32BaseAddr, \
                                    CONST(uint8, AUTOMATIC) u8BdIdx \
                                            )
{
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 
    */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    return *((P2VAR(volatile uint32, AUTOMATIC, ETH_APPL_DATA))(u32BaseAddr + (u8BdIdx * (VAR(uint32, AUTOMATIC))8U)));
}

/*============================================================================*/
/**
* @brief         Clears the receive buffer
* @details       Function sets the Empty bit in the given buffer descriptor, the
*                rest of the bits is left untouched because they are anyway
*                written by the hardware or unused. The advantage is that the
*                WRAP bit remains untouched.
* @param[in] u8Buf Index of the buffer to be cleared
* @param[in] u32BDAddress Address of the RX buffer descriptors ring start
*/

static FUNC(void, ETH_CODE) Eth_Fec_ClearRxBuffer  (CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(uint8, AUTOMATIC) u8BufIdx)
{
    VAR(uint32, AUTOMATIC) u32ManipulationVar;
    VAR(uint32, AUTOMATIC) u32BdAddress;   /* Stores buffer descriptor address */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32BdAddress = (VAR(uint32, AUTOMATIC))ETH_CFG_RXBDSTARTADDRESS(u8CtrlIdx);
    
    /* Empty the buffer */
    u32ManipulationVar = Eth_Fec_ReadRxBDBits(u32BdAddress, u8BufIdx); /* Read bits */
    u32ManipulationVar = u32ManipulationVar | FEC_RXBD_E_U32;  /* Mark the buffer as empty */
    Eth_Fec_WriteRxBDBits(u32BdAddress, u8BufIdx, u32ManipulationVar); /* Write val.back */
    /* Write the RDAR register to notify the controller about a new buffer, 
       written value is ignored, the write access is what matters */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_RDAR_ADDR16, FEC_RDAR_R_DES_ACTIVE_U32); 
}

/*============================================================================*/
/**
* @brief         Determines the type of the given buffer
* @param[in]     u8CtrlIdx Index of examined controller
* @param[in]     u8Buf Index of the examined buffer
* @param[in]     u8BufCtrMax Number of the Rx buffers
* @param[out]    pMultiEnd Last found buffer of the multi-buffer frame
* @details       Function does the following
*                -# Checks the given buffer to be empty and returns RX_BUF_EMPTY
*                   if it is empty.
*                -# Otherwise it checks the buffer to be the last in the frame
*                   and returns RX_BUF_SINGLE if it is the last one.
*                -# Otherwise it goes through all  remaining buffers and
*                   searches for the full and last buffer or an empty buffer.
*                   Index of the found buffer is loaded into pMultiEnd argument.
*                -# RX_BUF_MULTI_UNFINISHED is returned if the found buffer
*                   was empty.
*                -# RX_BUF_MULTI_FINISHED is returned if the found buffer was
*                   full and last.
*                -# RX_BUF_OVERFLOW when buffer is not found.
* @return        Type of the examined buffer
* @retval        RX_BUF_EMPTY - buffer is empty,
* @retval        RX_BUF_SINGLE - buffer contains received frame
* @retval        RX_BUF_MULTI_UNFINISHED - buffer contains part of the
*                frame which has not been received yet
* @retval        RX_BUF_MULTI_FINISHED - buffer contains part of the frame which
*                has been received
* @retval        RX_BUF_OVERFLOW - all buffers are full and frame being received
*                           cannot be stored
*/

static FUNC(Eth_RxBufferType, ETH_CODE) Eth_Fec_GetRxBufferType    ( \
                                    CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                                    CONST(uint8, AUTOMATIC) u8Buf, \
                                    CONST(uint8, AUTOMATIC) u8BufCtrMax, \
                                    CONSTP2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pMultiEnd \
                                                                   )
{
  
    VAR(uint32, AUTOMATIC) u32ManipulationVar;
    VAR(uint8, AUTOMATIC ) u8BufCtr;
    VAR(Eth_RxBufferType, AUTOMATIC) eReturnStatus = RX_BUF_OVERFLOW;
    VAR(boolean, AUTOMATIC) bBreakLoop; /* Signal that the loop should end */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    VAR(uint32, AUTOMATIC) u32BDAddress = (VAR(uint32, AUTOMATIC))ETH_CFG_RXBDSTARTADDRESS(u8CtrlIdx);
    
    u32ManipulationVar = Eth_Fec_ReadRxBDBits(u32BDAddress, u8Buf);
    if(FEC_RXBD_E_U32 == (u32ManipulationVar & FEC_RXBD_E_U32))
    {
        /* Buffer is empty */
         eReturnStatus = RX_BUF_EMPTY;
    }
    else
    { /* Buffer is full */
        if(FEC_RXBD_L_U32 == (u32ManipulationVar & FEC_RXBD_L_U32))
        { /* Buffer contains whole frame */
            eReturnStatus = RX_BUF_SINGLE;
          /* Indicate that only single buffer is used */
          *pMultiEnd = u8Buf;
        }
        else
        {   /* Buffer contains only part of the frame */
            /* Search for the last buffer in that frame */      
            u8BufCtr = u8Buf;
            bBreakLoop = ((VAR(boolean, AUTOMATIC))FALSE);/*Loop shall continue*/
            do
            {
                /* Continue with the next buffer */
                if(u8BufCtrMax == u8BufCtr) /* Check if the counter wraps */
                { /* Yes, it wraps  */
                    u8BufCtr = 0U;
                }
                else
                { /* No, it does not wrap */ 
                    u8BufCtr++;
                }
                /* Check the buffer properties to determine whether 
                   it is the last buffer in the multi-buffer frame*/
                if(u8BufCtr == u8Buf) /* Check  the overflow */
                {   /* Search in the ring returned to the starting position 
                       without finding the buffer. This means the ring is full 
                       of full buffers and the last buffer which shall end
                       the multi-buffer frame cannot be written because there 
                       is no space to write it. 
                    */          
                    eReturnStatus = RX_BUF_OVERFLOW; /* Signal an error */
                    /* Searching again should be avoided */
                    bBreakLoop = ((VAR(boolean, AUTOMATIC))TRUE); 
                } 
                else
                { /* No overflow detected */
                    u32ManipulationVar = Eth_Fec_ReadRxBDBits(u32BDAddress, u8BufCtr);
                    /* Check empty state */
                    if(FEC_RXBD_E_U32 == (u32ManipulationVar & FEC_RXBD_E_U32))
                    { /* Multi-buffer frame has not been finished yet -
                         last buffer has not been written,
                         only empty space for it has been found */
                         *pMultiEnd = u8BufCtr;
                         eReturnStatus = RX_BUF_MULTI_UNFINISHED;
                         /* Buffer cannot be found, stop search */
                         bBreakLoop = ((VAR(boolean, AUTOMATIC))TRUE);             
                    }
                    /* Buffer is full, check whether it is also the last one */
                    else if(FEC_RXBD_L_U32 == (u32ManipulationVar & FEC_RXBD_L_U32)) 
                    {   /* This is the last buffer of the multi-buffer frame */
                         *pMultiEnd = u8BufCtr;
                         eReturnStatus = RX_BUF_MULTI_FINISHED;
                         /* Buffer has been found, stop search */
                         bBreakLoop = ((VAR(boolean, AUTOMATIC))TRUE);                          
                    }
                    else
                    {   /* This is the next but not the last buffer 
                           of the multi-buffer frame -
                                       Continue search with the next buffer */ 
                        bBreakLoop = ((VAR(boolean, AUTOMATIC))FALSE); 
                         /* This else is requested by MISRA otherwise 
                            it could be removed */
                    }
                }  
            }while(((VAR(boolean, AUTOMATIC))FALSE) == bBreakLoop); 
        } 
    }
    return eReturnStatus;
}


/*============================================================================*/
/**
* @brief         Returns pointer to received frame, frame length and status
*                bits of the receive buffer
* @param[in]     u8CtrlIdx Index of controller to be read
* @param[in]     u8Buf First buffer of the frame
* @param[in]     u8MultiEnd Last buffer of the frame
* @param[out]    pLength  Frame length
* @param[out]    pDataPtr Pointer to the frame data
* @param[out]    pStatusPtr Buffer status bits
* @details       Function loads the pStatusPtr argument with the buffer status
*                bits, the length argument is loaded by the frame length
*                and the pDataPtr is loaded with the beginning address of the
*                received frame data.
* @note          The returned buffer contains Ethernet frame header and its
*                payload. The CRC is not included but it occupies next 4 bytes
*                in the memory after the buffer end.
* @implements    Eth_Fec_GetRxBufferData_Activity
*/

static FUNC(void, ETH_CODE) Eth_Fec_GetRxBufferData    ( \
                            CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                            CONST(uint8, AUTOMATIC) u8Buf, \
                            CONST(uint8, AUTOMATIC) u8MultiEnd, \
                            CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pLength, \
                            P2P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) pDataPtr, \
                            CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) pStatusPtr \
                                                        )
{
#if STD_ON == ETH_USE_RX_FRAMES_WRAP
    /* The maximum index of RX buffer */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    VAR(uint8, AUTOMATIC) u8BufCtrMax = ETH_CFG_RXBUFTOTAL( u8CtrlIdx) - 1U;
    /* Loop control variable */
    VAR(uint32, AUTOMATIC) u32ii;
    /* Temporary source and destination addresses */
    VAR(uint32, AUTOMATIC) u32srcAddr;
    VAR(uint32, AUTOMATIC) u32destAddr;
#endif /* ETH_USE_RX_FRAMES_WRAP */
    VAR(uint16, AUTOMATIC) u16FrameLength;
    /* Manipulation variable */
    VAR(uint32, AUTOMATIC) u32ManipulationVar;

    /* Get reception status of the frame */
    /* Compiler_Warning: (diab) this should not be a warning because they are same type. 
    No potential problem here. */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32ManipulationVar = Eth_Fec_ReadRxBDBits((VAR(uint32, AUTOMATIC))ETH_CFG_RXBDSTARTADDRESS(u8CtrlIdx), u8MultiEnd);
    /* Return the status bits */
    *pStatusPtr = u32ManipulationVar & (VAR(uint32, AUTOMATIC))0xFFFF0000U;
    /* Select the length field */
    u32ManipulationVar = u32ManipulationVar & FEC_RXBD_LENGTH_U32; 
    /* Return the length */
    u16FrameLength = (VAR(uint16, AUTOMATIC))(u32ManipulationVar & FEC_RXBD_LENGTH_U32); 

    /* Get data pointer and data length */
#if STD_ON == ETH_USE_MULTIBUFFER_RX_FRAMES
    if( u16FrameLength > 1522U )
    {   /* The length must be incorrect, it is greater than maximal allowed length */
        /* Return maximal length instead */
        /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
        *pLength = (VAR(uint16, AUTOMATIC)) 1522U;
    }
#else
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    if( u16FrameLength > ETH_CFG_CTRLRXBUFLENBYTE( u8CtrlIdx) )
    {   /* The length must be incorrect, it is greater than maximal allowed length */
        /* Return maximal length instead */
        /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
        *pLength = (VAR(uint16, AUTOMATIC)) (ETH_CFG_CTRLRXBUFLENBYTE( u8CtrlIdx));
    }
#endif
    else if( u16FrameLength < 14U )
    {   /* The length must be incorrect, minimal acceptable length is 14 (ethernet header only) */
        /* Return minimal length instead (avoid length underloop due to header length subtract) */
        *pLength = (VAR(uint16, AUTOMATIC)) (14U);
    }
    else
    {   /* The length seems correct, return it */
        /* In IPV_FEC, CRC is not truncated, so remove it */
        *pLength = u16FrameLength-4U;
    }
    
    if (u8Buf > u8MultiEnd)
    {
        /* Wrap occurred */
    #if STD_ON == ETH_USE_RX_FRAMES_WRAP
        /* Check whether data should be copied to leading or trailing area -
           chose which copy will be shorter: either buffer ring start to "u8MultiEnd", 
           or "u8Buf" to buffer ring end. */
        if ((u8BufCtrMax-u8Buf) > u8MultiEnd)
        { /* Copy from the start of the buffer ring to the trailing area because it is shorter */
            /* Setup source address */
            /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
            u32srcAddr = Eth_Fec_ComputeRxBufAddr(u8CtrlIdx, 0U);
            /* Setup destination address */
            /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
            u32destAddr = Eth_Fec_ComputeRxBufAddr(u8CtrlIdx, u8BufCtrMax) + ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx);
            /* Store the data pointer */
            /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
            u32ManipulationVar = Eth_Fec_ComputeRxBufAddr(u8CtrlIdx, u8Buf);
            /* Return the pointer */
            /** 
                @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1
            */
            /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
            *pDataPtr = (P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA))u32ManipulationVar;
            
            /* Get number of buffers up to wrap */
            u32ManipulationVar = (((VAR(uint32, AUTOMATIC))u8BufCtrMax - u8Buf) + 1U);
            /* Setup count. The 'length' value must be extended by 4 bytes of CRC */
            /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
            u32ManipulationVar = ((VAR(uint32, AUTOMATIC))(*pLength) + 4U) - (u32ManipulationVar * ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx));
        }
        else
        { /* Copy from the end of the buffer ring to the leading area because it is shorter */
            /* Get source address */
            /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
            /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
            u32srcAddr = Eth_Fec_ComputeRxBufAddr(u8CtrlIdx, 0U) \
                            + ((VAR(uint32, AUTOMATIC))u8Buf * ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx));
            /* Set destination address */
            /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
            /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
            u32destAddr =  ( Eth_Fec_ComputeRxBufAddr(u8CtrlIdx, 0U) \
                            - ((ETH_CFG_RXBUFTOTAL(u8CtrlIdx) - (VAR(uint32, AUTOMATIC))u8Buf) * ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx)) \
                           );
            /* Return the pointer */
            /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
            /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
            *pDataPtr = (P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA))u32destAddr;
            /* Setup count */
            /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
            u32ManipulationVar = (ETH_CFG_RXBUFTOTAL(u8CtrlIdx) - (VAR(uint32, AUTOMATIC))u8Buf) * ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx);
        }
        
        /* Perform the copy */
        for (u32ii=u32destAddr; u32ii<(u32destAddr+u32ManipulationVar); u32ii+=4U)
        {
            /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
            /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
            *(P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA)) u32ii = (uint32)(*(P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA)) u32srcAddr);
            /* Move the source address */
            u32srcAddr+=4U;
        }
    #else
        /* Do not receive the frame. Setup the error flags to ensure that frame
            will be rejected. */
        *pStatusPtr |= (VAR(uint32, AUTOMATIC)) 0xFFFF0000U;
    #endif /* ETH_USE_RX_FRAMES_WRAP */
    }
    else if (u8Buf == u8MultiEnd)
    {
        /* Receive the single-buffer frame */
        /* Store the data pointer */
        /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
        /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
        u32ManipulationVar = Eth_Fec_ComputeRxBufAddr(u8CtrlIdx, u8Buf);
        /* Return the pointer */
        /** 
            @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1
        */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        *pDataPtr = (P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA))u32ManipulationVar;
    }
    else
    {
    #if STD_ON == ETH_USE_MULTIBUFFER_RX_FRAMES
        /* Store the data pointer */
        /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
        u32ManipulationVar = Eth_Fec_ComputeRxBufAddr(u8CtrlIdx, u8Buf);
        /* Return the pointer */
        /** 
            @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1
        */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        *pDataPtr = (P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA)) u32ManipulationVar;
    #else
        /* Do not receive the frame. Setup the error flags to ensure that frame
            will be rejected. */
        *pStatusPtr |= (VAR(uint32, AUTOMATIC)) 0xFFFF0000U;
    #endif /* ETH_USE_MULTIBUFFER_RX_FRAMES */
    }
}

/*============================================================================*/
/**
* @brief         Unlocks given TX buffer and also BD if it is linked to buffer
* @param[in]     u8CtrlIdx Index of controller which will be release the buffer
* @param[in]     u8BufIdx DA index of the buffer to be unlocked
* @details       Function clears the Lock and the Transmitted bits of the given
*                buffer. Buffer becomes empty and can be reused for another
*                transmission.
* @note          All status bits and the length field are cleared.
*/
static FUNC(void, ETH_CODE) Eth_Fec_GiveBackTxBuffer(CONST(uint8, AUTOMATIC) u8CtrlIdx, VAR(uint8, AUTOMATIC) u8BufIdx)
{
    VAR(uint32, AUTOMATIC) u32ManipulationVar;
    VAR(uint8, AUTOMATIC) u8BDIdx; /* Index of linked BD (if any) */
#if STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES
    VAR(uint8, AUTOMATIC) u8BufNum; /* Number of buffers in current frame */
#endif /* ETH_USE_MULTIBUFFER_TX_FRAMES */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    VAR(uint32, AUTOMATIC) u32BDAddress = ETH_CFG_TXBDSTARTADDRESS(u8CtrlIdx);

    /* Is there a BD linked to this buffer? */
    if( (FEC_TXB_FIRST_U8 | FEC_TXB_LINK_U8 | FEC_TXB_LOCK_U8) == Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx])
    {   /* Yes, unlink the BD */
        /* Remove it on the BD side: */
        u8BDIdx = Eth_au8TxBdOfBuf[u8CtrlIdx][u8BufIdx];
        /* Read the TXBD status */
        u32ManipulationVar = Eth_Fec_ReadTxBDBits(u32BDAddress, u8BDIdx);
        /* Clear BufLinked flag */
        u32ManipulationVar &= (VAR(uint32, AUTOMATIC))(~FEC_TXBD_TO1_U32);
        /* Write modified bits back */
        Eth_Fec_WriteTxBDBits(u32BDAddress, u8BDIdx, u32ManipulationVar);
        /* NOTE: on buffer side the link is removed below */
    }

#if STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES
    /* Unlock all buffers of frame */
    u8BufNum = Eth_FEC_au8TxBufGroup[u8CtrlIdx][u8BufIdx];
    while(0U != u8BufNum)
    {
        Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx] = 0U;
        u8BufNum--;
        u8BufIdx++; /* The memory must be continuous, wrap may not occur */
    }
#else /* ETH_USE_MULTIBUFFER_TX_FRAMES */
    /* Unlock the buffer, there is only one */
    Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx] = 0U;
#endif /* ETH_USE_MULTIBUFFER_TX_FRAMES */
}

/*==============================================================================
*                                       GLOBAL FUNCTIONS
==============================================================================*/

/*============================================================================*/
/**
* @brief         Finds empty TX buffer(s) (if any) and locks them
* @param[in]     u8CtrlIdx Index of controller to be borrowed buffer
* @param[out]    pBufIdx Granted buffer index to be used for frame
*                transmission is stored here.
* @param[out]    pBufPtr Pointer to data area beginning is stored here.
* @param[in,out] pBufLength Wanted or Granted buffer length
* @details       Function goes through buffers, searching either UnlockedAT
*                or Free buffers. If UnlockedAT buffer is found, whole frame
*                is freed at first. Once continuous region of memory of
*                requested length is found, it is allocated, pointer to the
*                memory is returned, index of first allocated buffer is returned
*                and real allocated length is also returned. Otherwise FALSE is
*                returned.
* @return        The search result
* @retval        TRUE Available buffer of desired length was found and locked.
* @retval        FALSE There is not empty buffer available at the moment.
* @implements    Eth_Fec_BorrowTxBuffer_Activity
*/
FUNC(boolean, ETH_CODE) Eth_Fec_BorrowTxBuffer  ( \
                CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                    CONSTP2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pBufIdx, \
                    P2P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) pBufPtr, \
                    CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pBufLength\
                                                )
{
    VAR(uint8, AUTOMATIC) u8BufNumNeed; /* Needed number of buffers */
    VAR(uint8, AUTOMATIC) u8BufNumFound; /* Number of free buffers found */
#if STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES
    VAR(uint8, AUTOMATIC) u8IdxL; /* General purpose index to be used in loops */
#endif /* ETH_USE_MULTIBUFFER_TX_FRAMES */
    VAR(uint32, AUTOMATIC) u32BDStatus;
    VAR(uint8, AUTOMATIC) u8Idx;  /* General purpose index to be used in loops */
    VAR(uint16, AUTOMATIC) u16SearchCnt; /* Countdown to limit search */
    
    VAR(boolean, AUTOMATIC) bDataAreaFound = ((VAR(boolean, AUTOMATIC))FALSE); 
    /* Used to track if some free buffer was found */
    /* Local copies of configuration (optimization): */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    VAR(uint8, AUTOMATIC) u8TotalBufNum = ETH_CFG_TXBUFTOTAL(u8CtrlIdx);
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    VAR(uint16, AUTOMATIC) u16BufSize = ETH_CFG_CTRLTXBUFLENBYTE(u8CtrlIdx);
    /* Compiler_Warning: (diab) this should not be a warning because they are same type. 
    No potential problem here. */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    VAR(uint32, AUTOMATIC) u32BDAddr = ETH_CFG_TXBDSTARTADDRESS(u8CtrlIdx);
    
#if STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES
    /* Compute needed number of buffers. Add 14B for eth header, round up */
    u8BufNumNeed = (VAR(uint8, AUTOMATIC))((*pBufLength + (u16BufSize + (14U - 1U))) / u16BufSize);
    /* s16SearchCnt must be incremented by the number of needed buffers because
       we must check the buffers at the end again if we skipped them due to
       the fact that we started search in the middle of the continuous block
       just before the wrap (example: we need 4 buffers, and we start search
       from the 3rd buffer before the row end therefore we would end by
       examining the 4th buffer from the end (if no adjust was done) without
       discovering needed 4 buffers block at the end of the row). */
    u16SearchCnt = ((VAR(uint16, AUTOMATIC))u8TotalBufNum + (VAR(uint16, AUTOMATIC))u8BufNumNeed) - 1U;
#else /* ETH_USE_MULTIBUFFER_TX_FRAMES */
    /* One buffer is always needed */
    u8BufNumNeed = 1U;
    u16SearchCnt = u8TotalBufNum;
#endif /* ETH_USE_MULTIBUFFER_TX_FRAMES */
    /* Start at Eth_FEC_u8SearchTxBufFrom (to minimize fragmentation) */
    u8Idx = Eth_FEC_u8SearchTxBufFrom[u8CtrlIdx];
    u8BufNumFound = 0U;
    while(((VAR(boolean, AUTOMATIC))FALSE == bDataAreaFound) && (u16SearchCnt != 0U))
    {
        /* Check buffer status, whether the buffer may be unlocked now */
        if ((FEC_TXB_LOCK_U8 | FEC_TXB_LINK_U8 | FEC_TXB_FIRST_U8) == Eth_au8TxBufFlags[u8CtrlIdx][u8Idx])
        {   /* According to buffer flags, it may be unlocked now */
            /* Now check BD status, whether Ready bit is cleared */
            u32BDStatus = FEC_TXBD_R_U32 & Eth_Fec_ReadTxBDBits(u32BDAddr, Eth_au8TxBdOfBuf[u8CtrlIdx][u8Idx]);
            if( 0U == u32BDStatus )
            {   /* Yes, the frame is in UNLOCKEDAT state and both BD and
                   buffers shall be unlocked and unlinked now */
                Eth_Fec_GiveBackTxBuffer(u8CtrlIdx, u8Idx);
            }
        }
        /* Check buffer status. Is the buffer free ? */
        if(0U == Eth_au8TxBufFlags[u8CtrlIdx][u8Idx])
        {   /* Yes, it is free */
            u8BufNumFound++;
            if( u8BufNumFound == u8BufNumNeed )
            {   /* All needed buffers found */
                bDataAreaFound = (VAR(boolean, AUTOMATIC))TRUE;
                u8Idx++;
                /* Next time continue search from here */
                if( u8Idx >= u8TotalBufNum )
                {
                    Eth_FEC_u8SearchTxBufFrom[u8CtrlIdx] = 0U;
                }
                else
                {
                    Eth_FEC_u8SearchTxBufFrom[u8CtrlIdx] = u8Idx;
                }
                /* Compute index of the first buffer, u8Idx is behind allocated
                   buffers now. Continuous block => no wrap => no under-loop */
                *pBufIdx = u8Idx - u8BufNumFound;
                /* Compute buffer pointer, skip 14 bytes for ethernet header */
                /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
                /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
                *pBufPtr = (void *)(14U + (Eth_Fec_ComputeTxBufAddr(u8CtrlIdx, *pBufIdx)));
                /* Return real length of buffers minus eth header length */
                (*pBufLength) = (u16BufSize * u8BufNumNeed) - 14U;
                /* Lock all allocated buffers, do in critical section to prevent interference */
                Eth_au8TxBufFlags[u8CtrlIdx][*pBufIdx] = FEC_TXB_LOCK_U8 | FEC_TXB_FIRST_U8; /* The 1st */

#if STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES
                /* Write number of buffers belonging to this frame */
                Eth_FEC_au8TxBufGroup[u8CtrlIdx][*pBufIdx] = u8BufNumNeed;

                for (u8IdxL = (*pBufIdx) + 1U; u8IdxL < (*pBufIdx+u8BufNumNeed); u8IdxL++) /* Skip the first */
                {
                    Eth_au8TxBufFlags[u8CtrlIdx][u8IdxL] = FEC_TXB_LOCK_U8;
                }
#endif /* ETH_USE_MULTIBUFFER_TX_FRAMES */
            }
        }
        else
        {   /* No, buffer is locked => continuity broken */
            u8BufNumFound = 0U;
        }
        u16SearchCnt--;
        u8Idx++;
        if( u8Idx >= u8TotalBufNum )
        {   /* Wrapped */
            u8Idx = 0U;
            u8BufNumFound = 0U; /* Wrap => continuity broken */
        }
    }
    return bDataAreaFound;
}

/*============================================================================*/
/* TX Buffers status bits summary ()

    BufferState   BD_Bits Link BufferFlags
    Free:                        0000
    LockedBT:                    1001
    LockedIT:         11---------1111
    UnlockedIT:       11---------1011
    LockedAT:         01---------1111
    UnlockedAT:       01---------1011
    LockedATUnlinked:            1101
    LockedNotFirstOfFrame:       1000
    FreeBufferDescr:  00
                      ||    |    ||||-- FEC_TXB_FIRST_U8: First buffer of frame
                      ||    |    |||--- FEC_TXB_LINK_U8: Linked to BD
                      ||    |    ||---- FEC_TXB_CONF_U8: TxConfirmation needed
                      ||    |    |----- FEC_TXB_LOCK_U8: Buffer locked
                      ||    |---------- Link between BD and buffer. If the link
                      ||                exists, FEC_TXB_LINK_U8 and FEC_TXBD_TO1_U32 
                      ||                bits are set and following is true:
                      ||                BDIdx = Eth_au8TxBdOfBuf[BufIdx]
                      ||--------------- FEC_TXBD_TO1_U32: Linked to buffer(s)
                      |---------------- FEC_TXBD_R_U32:   In transmission (ready bit)

    Transitions between states:
    In Eth_Fec_BorrowTxBuffer():
        Free -> LockedBT:             Standard operation.
        UnlockedAT -> LockedBT:       Buffer automatically released and reused.
    In Eth_Fec_Transmit();
        LockedBT -> LockedIT:         Standard operation, TxConfirm required.
        LockedBT -> UnlockedIT:       Standard operation.
        UnlockedAT -> Free:           The linked buffer descriptor was needed
                                      -> both BD and Buffers were
                                      automatically freed.
        LockedAT -> LockedATUnlinked: The linked buffer descriptor was needed
                                      -> it was unlinked from the buffers.
    In FEC (the hardware):
        LockedIT -> LockedAT:         Standard operation.
        UnlockedIT -> UnlockedAT:     Standard operation.
    In TxConfirmation:
        LockedAT -> Free:             Standard operation.
        LockedATUnlinked -> Free:     Standard operation.
*/

/*============================================================================*/
/**
* @brief         Checks whether the transmit buffer state is LOCKEDBT
* @param[in]     u8BufIdx Checked buffer index (first buffer of frame)
* @param[in]     u32BDAddr Address of the TX descriptor ring start
* @details       Function checks whether the buffer is locked and first of frame
*                (whether it may be passed to Transmit function).
* @retval        TRUE Buffer is in LOCKEDBT state, valid frame "handle"
* @retval        FALSE Buffer is in different state
*/
FUNC(boolean, ETH_CODE) Eth_Fec_IsTxBufLockedBT(CONST(uint8, AUTOMATIC) u8CtrlIdx, CONST(uint8, AUTOMATIC) u8BufIdx)
{
    VAR(boolean, AUTOMATIC) bResult; /* Result holder */ 

    if( (FEC_TXB_LOCK_U8|FEC_TXB_FIRST_U8)== Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx] )
    {   /* OK, it is locked and first buffer of frame */
        bResult = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else 
    {
        bResult = (VAR(boolean, AUTOMATIC))FALSE;
    }
    return bResult;
}

/*============================================================================*/
/**
* @brief         Triggers the transmission of the given frame
* @param[in]     u8CtrlIdx Index of controller which will be triggered the transmission
* @param[in]     u8BufIdx Buffer index provided by Eth_Fec_BorrowTxBuffer.
* @param[in]     u16EtherType Type or length field value in the 802.3 frame header
* @param[in]     u16Length Payload length
* @param[in]     bConfirm Selects whether the frame transmission shall
*                be confirmed or not
* @param[in]     pDest Frame destination address
* @details       At first Ethernet header is assembled.
*                Then the buffers are linked with active buffer descriptor
*                (Eth_u8ActiveTxBD) and the buffer descriptor is written
*                including the Ready bit. The controller is notified about the
*                new buffer by a write into the TDAR register.
* @note          Note that as buffer was successfully borrowed, at least one BD
*                will also be available, because number of BDs >= number of
*                frames in buffers, so even if all buffers (but this one) are
*                linked to BDs, at least one BD is free and may be used for
*                current frame. 
*                Buffer descriptors are used as ring buffer, where
*                Eth_u8ActiveTxBD is index of first available BD. It is also
*                the only one BD that may be used, because it is the BD where
*                FEC controller will look for next frame.
* @implements    Eth_Fec_Transmit_Activity
*/

FUNC(void, ETH_CODE) Eth_Fec_Transmit   ( \
                            CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                            CONST(uint8, AUTOMATIC) u8BufIdx, \
                            CONST(Eth_FrameType, AUTOMATIC) u16EtherType, \
                            CONST(uint16, AUTOMATIC) u16Length, \
                            CONST(boolean, AUTOMATIC) bConfirm, \
                            P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) pDest \
                                        )
{
    VAR(uint32, AUTOMATIC) u32BufAddr; /* Address of (first) buffer */
    VAR(uint32, AUTOMATIC) u32ManipulationVar; /* Used for bit manipulations */
    /* Local copies of configuration (optimization): */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    VAR(uint8, AUTOMATIC) u8TotalBufNum = ETH_CFG_TXBUFTOTAL(u8CtrlIdx);
    /* Compiler_Warning: (diab) this should not be a warning because they are same type. 
    No potential problem here. */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    VAR(uint32, AUTOMATIC) u32BDAddr = ETH_CFG_TXBDSTARTADDRESS(u8CtrlIdx);
    
    /* Assemble frame header */
    /* Compute address of the buffer. */
    u32BufAddr = (VAR(uint32, AUTOMATIC)) Eth_Fec_ComputeTxBufAddr(u8CtrlIdx, u8BufIdx);

    /* Copy destination MAC address - use a temporary variable to access 
       a given destination address because the pDest pointer is only of 8bit 
       type therefore the data may not have 16-bit alignment. The 16-bit 
       alignment of the buffer data is ensured by the buffer alignment 
       restrictions */
    u32ManipulationVar = ((VAR(uint32, AUTOMATIC))(*pDest) << 8U);
    /** @violates @ref Eth_Fec_c_REF_5 */
    u32ManipulationVar |= *(pDest + 1U);
    Eth_Fec_Write16TxBufMem(u32BufAddr, 0U, (VAR(uint16, AUTOMATIC)) u32ManipulationVar); /* Put first 2 bytes */
    /** @violates @ref Eth_Fec_c_REF_5 */
    u32ManipulationVar = ((VAR(uint32, AUTOMATIC))(*(pDest + 2U)) << 8U);
    /** @violates @ref Eth_Fec_c_REF_5 */
    u32ManipulationVar |= *(pDest + 3U);
    Eth_Fec_Write16TxBufMem(u32BufAddr, 2U, (VAR(uint16, AUTOMATIC)) u32ManipulationVar); /* Put second 2 bytes */
    /** @violates @ref Eth_Fec_c_REF_5 */
    u32ManipulationVar = ((VAR(uint32, AUTOMATIC))(*(pDest + 4U)) << 8U);
    /** @violates @ref Eth_Fec_c_REF_5 */
    u32ManipulationVar |= *(pDest + 5U);
    Eth_Fec_Write16TxBufMem(u32BufAddr, 4U, (VAR(uint16, AUTOMATIC))u32ManipulationVar); /* Put third 2 bytes */
    /* Read source MAC address from registers and put it to header */
    /* Read first 4 bytes */
    /**  
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32ManipulationVar = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PALR_ADDR16);
    Eth_Fec_Write16TxBufMem(u32BufAddr, 8U, (VAR(uint16, AUTOMATIC))(u32ManipulationVar & 0xFFFFU)); /* Put second 2 bytes */
    u32ManipulationVar = u32ManipulationVar >> 16U; /* Put bits to right position */
    Eth_Fec_Write16TxBufMem(u32BufAddr, 6U, (VAR(uint16, AUTOMATIC))(u32ManipulationVar & 0xFFFFU)); /* Prepend first 2 bytes */
    /* Read last 2 bytes */
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32ManipulationVar = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PAUR_ADDR16);
    u32ManipulationVar = u32ManipulationVar >> 16U; /* Put bits to right position */
    Eth_Fec_Write16TxBufMem(u32BufAddr, 10U, (VAR(uint16, AUTOMATIC))(u32ManipulationVar & 0xFFFFU)); /* Append third 2 bytes */  
    /* Type field should be placed into the type/length header field
       Transmitted length is set up by the buffer length when type 
       field has value grater than 1499
    */
    /* Append the type field */
    Eth_Fec_Write16TxBufMem(u32BufAddr, 12U, (VAR(uint16, AUTOMATIC))u16EtherType);

    /* Note: The link flags are set later below */
    Eth_au8TxBdOfBuf[u8CtrlIdx][u8BufIdx] = Eth_u8ActiveTxBD[u8CtrlIdx];
    /* Write frame/buffer status bits */
    if( (VAR(boolean, AUTOMATIC))TRUE == bConfirm )
    {   /* TxConfirmation is requested, also set TxConfirmation bit */
        Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx] = FEC_TXB_LOCK_U8 | FEC_TXB_FIRST_U8 | FEC_TXB_LINK_U8 | FEC_TXB_CONF_U8;
        /* Update number of pending confirmations */
        /* Enter critical section for RMW access */
        SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_00();
        Eth_u8LockedTxBufCount[u8CtrlIdx]++;
        /* Exit Exclusive area */
        SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_00();
    }
    else
    {
        Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx] = FEC_TXB_LOCK_U8 | FEC_TXB_FIRST_U8 | FEC_TXB_LINK_U8;
    }
    
    /* Now write the buffer descriptor */
    /* Write pointer */
    Eth_Fec_WriteTxBDBufPtr(u32BDAddr, Eth_u8ActiveTxBD[u8CtrlIdx], u32BufAddr);
    /* Write status bits and frame length. Note that FEC_TXBD_R_U32 bit must be written
       last. It will be written last, together with other bits and length.
       14 bytes of ethernet header is added to the length.  */
    u32ManipulationVar = FEC_TXBD_LENGTH_U32 & ((uint32)u16Length + 14U);
    /* Set: FEC_TXBD_R_U32: buffer is ready for transmission
            FEC_TXBD_TO1_U32: buffers are linked to this BD
            FEC_TXBD_L_U32: This BD is last in frame
            FEC_TXBD_TC_U32: Compute and append CRC to frame */
    u32ManipulationVar |= FEC_TXBD_R_U32 | FEC_TXBD_TO1_U32 | FEC_TXBD_L_U32 | FEC_TXBD_TC_U32;
    if( Eth_u8ActiveTxBD[u8CtrlIdx] == (u8TotalBufNum - 1U) )
    {   /* It is the last BD in ring, it must have wrap bit set */
        u32ManipulationVar |= FEC_TXBD_W_U32;
    }
    /* Write the assembled value to BD to allow the frame transmission */
    Eth_Fec_WriteTxBDBits(u32BDAddr, Eth_u8ActiveTxBD[u8CtrlIdx], u32ManipulationVar);
    /* This BD is not active any more, increment to next (consider wrap) */
    Eth_u8ActiveTxBD[u8CtrlIdx]++;
    if( Eth_u8ActiveTxBD[u8CtrlIdx] >= u8TotalBufNum )
    {
        Eth_u8ActiveTxBD[u8CtrlIdx] = 0U;
    }
    /* Write the TDAR register to notify the controller about a new buffer,
       written value is ignored, the write access is what matters. */
    /**  
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_TDAR_ADDR16, FEC_TDAR_X_DES_ACTIVE_U32); 
    /** @violates @ref Eth_Fec_c_REF_9 MISRA rule 16.7 */
}                                    



/*============================================================================*/
/**
* @brief         Resets the Ethernet controller
* @param[in]     u8CtrlIdx Index of controller which will be reset
* @details       Function masks all interrupts, issues a controller reset, 
*                waits for a while to allow controller finish its 
*                initialization. It clears all interrupt flags at the end.
* @implements    Eth_Fec_ResetController_Activity
*/

FUNC(void, ETH_CODE) Eth_Fec_ResetController(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(volatile uint8, AUTOMATIC) u8WaitCtr; /* Waiting loop counter */

    /* Disable all interrupts before the masks are cleared to 
       avoid spurious interrupt generation */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIMR_ADDR16, 0U);
    /* Issue a reset */
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_ECR_ADDR16, FEC_ECR_RESET_U32);
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
    /* Clear multicast pool buffer */
    Eth_Fec_McastPoolClean(u8CtrlIdx);
    /* Clear MulticastPool flags */
    Eth_FEC_bMcastPoolOvf[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))FALSE;
    Eth_FEC_bMcastFullOpen[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))FALSE;
#endif /* ETH_UPDATE_PHYS_ADDR_FILTER */
    /* Wait until reset is finished - approximately 8 bus cycles */
    for(u8WaitCtr = 0U; u8WaitCtr <= ETH_RESET_WAIT_LOOP_COUNT; u8WaitCtr++)
    {
        ; /* This loop is intentionally empty. It  provides only necessary
             delay needed for controller internal re-initialization. */
    }  
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
    Eth_Fec_McastGAClean(u8CtrlIdx);
#endif /* ETH_UPDATE_PHYS_ADDR_FILTER */
    /* Clear all interrupt flags - all interrupts are masked, 
       no spurious interrupt can occur */
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16, FEC_EIR_ALL_W1C); 
}

/*============================================================================*/
/**
* @brief         Checks the access to the controller
* @details       Function is intended to be used only after the Ethernet
*                controller reset. It checks the reset value of one register
*                and checks whether it agrees with the datasheet value.
*                Controller is claimed as accessible if the value agrees.
* @param[in]     u8CtrlIdx Index of controller which will be checked the access
* @return        Controller accessibility
* @retval        TRUE Controller is accessible, value in register agrees.
* @retval        FALSE Controller access failed, different value read.
*/

FUNC(boolean, ETH_CODE) Eth_Fec_CheckAccessToCtrl(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(boolean, AUTOMATIC) bControllerAvailable; /* Used to hold return value*/
    
    /* Check if the RCR register contains the reset value */
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    if(FEC_RCR_INIT_VAL_U32 == REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_RCR_ADDR16))
    {
        /* Yes, it contains  right number, controller is probably available */
        bControllerAvailable = ((VAR(boolean, AUTOMATIC))TRUE);
    }
    else
    {
        /* No, the value is wrong, controller is definitely not available. */
        bControllerAvailable = ((VAR(boolean, AUTOMATIC))FALSE);
    }
    return bControllerAvailable;
}

/*============================================================================*/
/**
* @brief         Configures the controller
* @details       Function
*                -# enables/disables Received frame interrupts
*                -# enables/disables Transmitted frame interrupts
*                -# clears MAC addresses hash tables
*                -# configures the controller MAC address
*                -# configures the MII
*                -# configures RCR and TCR registers
*                -# configures the maximal received frame length
* @param[in]     u8CtrlIdx Index of controller which will be configured
* @note          The controller is ready for use after the function finishes
*                however the buffers configuration must be still done.
*/
FUNC(void, ETH_CODE) Eth_Fec_ConfigureCtrl(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to assemble register 
              value before writing to register or to read the register value */ 
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
    VAR(uint8, AUTOMATIC) u8CtrlLoop;
    VAR(uint8, AUTOMATIC) u8Count;
    VAR(uint16, AUTOMATIC) u16McastItemLoop;
#endif

    /* Initialize interrupts */
    u32RegisterValue = 0U; /* All interrupts are disabled */
     /* Check whether the RX interrupt is enabled for this controller
        and multiple configuration */
    /** @violates @ref Eth_Fec_c_REF_8 MISRA rule 13.7 
      * @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_20 MISRA rule 14.1 */
    if(((VAR(boolean, AUTOMATIC))TRUE) == ETH_CFG_ENABLERXINTERRUPT(u8CtrlIdx))
    {
         u32RegisterValue = u32RegisterValue | FEC_EIMR_RXF_U32; /* Enable RX irq */       
    }
    /* Check whether the TX interrupt is enabled for this controller
       and multiple configuration */
    /** @violates @ref Eth_Fec_c_REF_8 MISRA rule 13.7 
    * @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_20 MISRA rule 14.1 */
    if(((VAR(boolean, AUTOMATIC))TRUE) == ETH_CFG_ENABLETXINTERRUPT(u8CtrlIdx))
    {
        u32RegisterValue = u32RegisterValue | FEC_EIMR_TXF_U32; /* Enable TX irq */
    }
    /* Write the assembled value */ 
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIMR_ADDR16, u32RegisterValue);
  
    /* Configure MAC address(es) */
    u32RegisterValue = 0U;
    /* Configure Multicast hash table - no multicast received */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GAUR_ADDR16, u32RegisterValue);
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GALR_ADDR16, u32RegisterValue);
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_IAUR_ADDR16, u32RegisterValue);
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_IALR_ADDR16, u32RegisterValue);
    /* Configure device MAC address */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u32RegisterValue = ETH_CFG_MACADDRESSLOW(u8CtrlIdx);
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PALR_ADDR16, u32RegisterValue);
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u32RegisterValue = ETH_CFG_MACADDRESSHIGH(u8CtrlIdx);
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PAUR_ADDR16, u32RegisterValue);

    /* Configure MII management data clock speed */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u32RegisterValue = ETH_CFG_MSCR(u8CtrlIdx);
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_MSCR_ADDR16, u32RegisterValue);    
    /* The rest of MII configuration is in RCR register */    
    /* Configure Rx */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u32RegisterValue = ETH_CFG_RCR(u8CtrlIdx);
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_RCR_ADDR16, u32RegisterValue);    
    /* Configure the Rx buffers length */ 
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u32RegisterValue = ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx);
    u32RegisterValue = u32RegisterValue & FEC_EMRBR_R_BUF_SIZE_U32; /*Clear other bits */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EMRBR_ADDR16, u32RegisterValue); 
    /* Configure Tx */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u32RegisterValue = ETH_CFG_TCR(u8CtrlIdx);
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_TCR_ADDR16, u32RegisterValue);
    /****************************************************************/
    /* Write also registers initialized by hardware - avoid mismatch 
       between documentation and hardware implementation */ 
    /* Write TFWR with value 3 (FIFO watermark = 192 bytes) to minimize
       chance of FIFO underflow */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_TFWR_ADDR16, 3U);
    /* Write FRSR with value 0x0000_0500 to set both FIFOs to 256 bytes -
    FIFOs occupy memory space from BASE + 0x400 to BASE + 0x600 */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_FRSR_ADDR16, 0x00000500U);
    /* Write the OPD register with pause duration of 15 slot times
    (1 slot time = 512 bit times  = approx 49us for 10BASE )*/    
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_OPD_ADDR16, (0x00010000U|15U));
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
    /* Initialize for variable */
    for (u8CtrlLoop = 0U; u8CtrlLoop < (uint8)ETH_MAXCTRLS_SUPPORTED; u8CtrlLoop++)
    {
        for (u16McastItemLoop = 0U; u16McastItemLoop < (uint16)ETH_MULTICAST_POOL_SIZE; u16McastItemLoop++)
        {
            Eth_FEC_rMulticastPool[u8CtrlLoop][u16McastItemLoop].bActive=(VAR(boolean, AUTOMATIC))FALSE;
            for (u8Count=0U; u8Count<6U; u8Count++)
            {
                Eth_FEC_rMulticastPool[u8CtrlLoop][u16McastItemLoop].au8PhysAddr[u8Count]=0U;
            }
        }
    }
#endif
}

/*============================================================================*/
/**
* @brief         Configures all receive buffers
* @details       Function initializes all RX buffer descriptors - sets the Empty
*                bit and clears the rest. It computes all buffer addresses
*                and writes them into buffer descriptor pointers. The buffer
*                descriptors ring start is written to the appropriate register.
* @param[in]     u8CtrlIdx Index of controller in which Rx buffer will be configured
* @par
*                Buffers immediately follow the buffer descriptors area when the
*                number of buffers is even, 8 bytes are skipped otherwise. All
*                buffers are of the same size, no space is between them.
*
* @warning       Buffer descriptors ring start address must be 16-bytes aligned.
*                All buffers must have length equal to multiple of 16 bytes.
*/

FUNC(void, ETH_CODE)  Eth_Fec_ConfigureRxBuffers(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32BdAddress;   /* Stores buffer descriptor address */
    VAR(uint32, AUTOMATIC) u32BufAddress;  /* Used to compute buffer address */
    VAR(uint32, AUTOMATIC) u32BDInit;   /* Initialization value for the BD bits */
    VAR(uint8, AUTOMATIC) u8BufCtr;    /* Counter used to loop over the buffers */
  
   /* Access to local variable is faster than  via pointer in case of post-build 
      or link-time configuration. Configured value should be somewhere stored in 
      case of pre-compile configuration. */
    VAR(uint8, AUTOMATIC) u8BufNum;       /* Holds configured number of buffers */
    VAR(uint16, AUTOMATIC) u16BufLength;   /* Holds configured maximal length of 
                                              one Rx buffer */
    
    /* Get the length of one Rx buffer */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u16BufLength = ETH_CFG_CTRLRXBUFLENBYTE(u8CtrlIdx);
    /* Get the number of configured buffers */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    u8BufNum = ETH_CFG_RXBUFTOTAL(u8CtrlIdx);
    /* Get start address of Rx buffer descriptor rings */
    /* Compiler_Warning: (diab) this should not be a warning because they are same type. 
    No potential problem here. */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32BdAddress = (VAR(uint32, AUTOMATIC))ETH_CFG_RXBDSTARTADDRESS(u8CtrlIdx);
    /* Store the value into register - select ony necessary bits */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32( Eth_u32BaseAddr[u8CtrlIdx] + FEC_ERDSR_ADDR16, (u32BdAddress & FEC_ERDSR_R_DES_START_U32));   
    /* Assemble the configuration value */
    u32BDInit = FEC_RXBD_E_U32;
    /* Compute address of the first receive buffer data area - it has to be 16 
       bytes aligned which is done by following:
       - Buffer descriptors start address is generated as 16-bytes aligned 
       - All buffer descriptors are 8 bytes long and create continuous block
       - Buffer lengths are limited to be multiple of 16 bytes
       - Buffer area follows immediately after the buffer descriptors area if 
         the number of buffers is even
       - An empty space of 8 bytes is inserted between buffer descriptors and 
         buffers area if the number of buffers is odd    
    */
    /* Leave space for buffer descriptors */
    u32BufAddress = u32BdAddress + (u8BufNum * (VAR(uint32, AUTOMATIC))8U); 
    /* Check whether the number of buffers is odd */
    /* @violates @ref Eth_Fec_c_REF_8 MISRA rule 13.7 */
    if(0U != (u8BufNum & 0x01U))
    { /* Yes */
        u32BufAddress = u32BufAddress + 8U;  /* Skip 8 bytes */
    }
#if STD_ON == ETH_USE_RX_FRAMES_WRAP
    /* Create a space for leading buffers */
    /* 
       Payload(1500) + MAC(2*6) + VLAN(4) + TypeLength(2) + CRC(4) = 1522
       and therefore 1536 is needed
    */
    u32BufAddress += (VAR(uint32, AUTOMATIC))((((1536U / 2U) + ((VAR(uint32, AUTOMATIC))u16BufLength - 1U)) / u16BufLength )  * u16BufLength);
#endif /* ETH_USE_RX_FRAMES_WRAP */
    /* Write the buffer pointers to buffer descriptors and initialize
       status bits of all buffers */
    Eth_FEC_u32RxBufStartAddr[u8CtrlIdx] = u32BufAddress;
    for(u8BufCtr = 0U; u8BufCtr < u8BufNum; u8BufCtr++)
    {
        /* Write buffer descriptor control bits and length - buffer only needs 
           to be marked as empty, all other fields will be updated 
           during reception */
        Eth_Fec_WriteRxBDBits(u32BdAddress, u8BufCtr, u32BDInit); 
        /* Write buffer address into descriptor */
        Eth_Fec_WriteRxBDBufPtr(u32BdAddress, u8BufCtr, u32BufAddress);     
        /* Compute address of the next buffer */
        u32BufAddress = u32BufAddress + u16BufLength;
    } 
    /* Close the descriptor ring */
    u32BDInit = u32BDInit | FEC_RXBD_W_U32; /* This is the last descriptor */
    Eth_Fec_WriteRxBDBits(u32BdAddress, (VAR(uint8, AUTOMATIC)) (u8BufNum - 1U), u32BDInit);  /* Mark the last one */
}

/*============================================================================*/
/**
* @brief         Configures all transmit buffers
* @details       Function clears all buffer descriptor bits -> marks all buffer
*                descriptors as Free and not ready for the transmission.
*                The buffer descriptors ring start address is written it the
*                appropriate register.
* @par
*                All buffers of same size, immediately follow buffer descriptors
*                as a continuous block without empty spaces between buffers.
* @warning       Buffer descriptors ring start address must be 16-bytes aligned.
*                Buffer sizes are limited to be multiple of 16 bytes.
*/

FUNC(void, ETH_CODE) Eth_Fec_ConfigureTxBuffers(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32BdAddress; /* Stores buffer descriptor address */
    VAR(uint8, AUTOMATIC) u8Idx;      /* Index to go through array */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /* Number of TX buffers from configuration */
    VAR(uint8, AUTOMATIC) u8BufNum = ETH_CFG_TXBUFTOTAL(u8CtrlIdx);   

    /* Get start address of TX buffer descriptors ring */
    /* Compiler_Warning: (diab) this should not be a warning because they are same type. 
    No potential problem here. */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32BdAddress = ETH_CFG_TXBDSTARTADDRESS(u8CtrlIdx);

    for(u8Idx=0U; u8Idx < u8BufNum; u8Idx++)
    {
        /* Unlock all TX buffers */
        Eth_au8TxBufFlags[u8CtrlIdx][u8Idx] = 0U;
        /* Clear all buffer descriptor status bits, zero length */
        Eth_Fec_WriteTxBDBits(u32BdAddress, u8Idx, 0U); 
    }
    /* Set wrap bit on last buffer descriptor */
    /* Just in case, unnecessary because it is always set in Eth_Fec_Transmit */
    Eth_Fec_WriteTxBDBits(u32BdAddress, u8BufNum-1U, FEC_TXBD_W_U32); 
    
    /* Compute start address of TX buffers */
    /** @violates @ref Eth_Fec_c_REF_11 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_8 MISRA rule 13.7 */
    if(0U == (u8BufNum & 0x01U))
    {   /* Even number of descriptors - first data pointer is already aligned to 64 bytes */
        Eth_FEC_u32TxBufStartAddr[u8CtrlIdx] = u32BdAddress + ((VAR(uint32, AUTOMATIC))8U * u8BufNum);
    }
    else
    {   /* Odd number of descriptors - leave 32 bytes to get the first data pointer aligned to 64 bytes */
        Eth_FEC_u32TxBufStartAddr[u8CtrlIdx] = u32BdAddress + ((VAR(uint32, AUTOMATIC))8U * u8BufNum) + 8U;
    }
    /* Start free buffer search from beginning */
    /** @violates @ref Eth_Fec_c_REF_8 MISRA rule 13.7 */
    Eth_FEC_u8SearchTxBufFrom[u8CtrlIdx] = 0U;
    /* Store the value into register - select only necessary bits */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32( Eth_u32BaseAddr[u8CtrlIdx] + FEC_ETDSR_ADDR16, (u32BdAddress & FEC_ETDSR_X_DES_START_U32));
}


/*============================================================================*/
/**
* @brief         Starts the controller
* @param[in]     u8CtrlIdx Index of controller which will be enabled
* @details       Function enables the controller after that it activates receive
*                and transmit buffer descriptors rings.
*/

FUNC(void, ETH_CODE) Eth_Fec_EnableController(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /* Init the active Rx buffer descriptor pointer -
       the BDs are reset during controller reset or disablement */
    Eth_u8ActiveRxBuf[u8CtrlIdx] = 0U;
    Eth_u8ActiveTxBD[u8CtrlIdx] = 0U;
    Eth_u8LockedTxBufCount[u8CtrlIdx] = 0U;
    /* Enable the controller - needs to be done at first */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_ECR_ADDR16, FEC_ECR_ETHER_EN_U32);
    /* Tell the controller to check Rx buffer descriptors */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_RDAR_ADDR16, FEC_RDAR_R_DES_ACTIVE_U32); 
    /* Tell the controller to check Tx buffer descriptors  */
    /** 
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_TDAR_ADDR16, FEC_TDAR_X_DES_ACTIVE_U32); 
}


/*============================================================================*/
/**
* @brief         Immediately stops the controller
* @details       Function clears the ECR[ETHER_EN] bit which causes
*                - receiver to stop
*                - transmitter to append bad CRC and stop, descriptor of
*                  this frame is no updated
*                - DMA, FIFO control and buffer descriptors reset
* @param[in]     u8CtrlIdx Index of controller which will be disabled
* @par
*                Actions needed to recover:
*                - set ECR[ETHER_EN] (reenable the controller)
*                - write RDAR, TDAR (tell that some buffers are prepared)
*/
FUNC(void, ETH_CODE) Eth_Fec_DisableController(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /* Clear the ECR[ETHER_EN] bit */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_ECR_ADDR16, 0U); 
}


/*============================================================================*/
/**
* @brief         Check whether the controller is running
* @details       Function checks the ECR[ETHER_EN] bit to determine whether
*                the controller has been stopped or whether it is running.
* @param[in]     u8CtrlIdx Index of controller which will be checked active status
* @return        The current controller mode.
* @retval        ETH_MODE_ACTIVE The controller is running.
* @retval        ETH_MODE_DOWN The controller is stopped.
*/

FUNC(Eth_ModeType, ETH_CODE) Eth_Fec_CheckCtrlIsActive(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(Eth_ModeType, AUTOMATIC) eReturnValue; /* Return value holder */
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to access register */

    /* Find whether the module is on by reading ECR[ETHER_EN]*/
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_ECR_ADDR16);
    if(FEC_ECR_ETHER_EN_U32 == (u32RegisterValue & FEC_ECR_ETHER_EN_U32))
    {    /* Module is on */
         eReturnValue = ETH_MODE_ACTIVE;
    }
    else
    {    /* Module is off */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
         eReturnValue = ETH_MODE_DOWN;
    }
    return eReturnValue;
}


/*============================================================================*/
/**
* @brief         Clears the RXF (received frame) flag
* @param[in]     u8CtrlIdx Index of controller in which RxIRQ flag will be cleared
*/

FUNC(void, ETH_CODE) Eth_Fec_ClearRxIrqFlag(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16, FEC_EIR_RXF_W1C);
}

/*============================================================================*/
/**
* @brief         Clears the TXF (transmitted frame) flag
*/
/** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
FUNC(void, ETH_CODE) Eth_Fec_ClearTxIrqFlag(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16, FEC_EIR_TXF_W1C);
}

/*============================================================================*/
/**
* @brief         Checks whether the TXF flag is set
* @details       This function can be used to check whether the frame 
*                transmitted interrupt flag is set.
* @param[in]     u8CtrlIdx Index of controller in which TxIRQ flag will be checked
* @retval        TRUE if the TXF flag is set
* @retval        FALSE if the TXF flag is cleared
*/
FUNC(boolean, ETH_CODE) Eth_Fec_IsTxIrqFlagSet(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to read register value */
    VAR(boolean, AUTOMATIC) bReturnValue; /* Stores the result */
    
    /* Read the register */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16);
    /* Check whether the bit is set */
    if(FEC_EIR_TXF_U32 == (u32RegisterValue & FEC_EIR_TXF_U32))
    {
        bReturnValue = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else
    {
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        bReturnValue = (VAR(boolean, AUTOMATIC))FALSE;
    }
    /* Test point for Fault Injection Test, for other, this line will be skipped. */
//    MCAL_FAULT_INJECTION_POINT(ETH_FIP_1_ISTXIRQFLAGSET_RET);
    
    return bReturnValue;
    
}
/*============================================================================*/
/**
* @brief         Checks whether the RXF flag is set
* @details       This function can be used to check whether the frame received
*                interrupt flag is set.
* @param[in]     u8CtrlIdx Index of controller in which RxIRQ flag will be checked
* @retval        TRUE if the RXF flag is set
* @retval        FALSE if the RXF flag is cleared
*/
FUNC(boolean, ETH_CODE) Eth_Fec_IsRxIrqFlagSet(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to read register value */
    VAR(boolean, AUTOMATIC) bReturnValue; /* Stores the result */
    
    /* Read the register */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16);
    /* Check whether the bit is set */
    if(FEC_EIR_RXF_U32 == (u32RegisterValue & FEC_EIR_RXF_U32))
    {
        bReturnValue = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else
    {
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        bReturnValue = (VAR(boolean, AUTOMATIC))FALSE;
    }
    /* Test point for Fault Injection Test, for other, this line will be skipped. */
//    MCAL_FAULT_INJECTION_POINT(ETH_FIP_2_ISRXIRQFLAGSET_RET);
    
    return bReturnValue;
}
/*============================================================================*/
/**
* @brief         Checks whether the transmit interrupt is enabled.
@param[in]       u8CtrlIdx Index of controller in which TxIRQ mask will be checked
* @retval        TRUE the interrupt is enabled
* @retval        FALSE the interrupt is disabled
*/
FUNC(boolean, ETH_CODE) Eth_Fec_IsTxIrqEnabled(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to read register value */
    VAR(boolean, AUTOMATIC) bReturnValue; /* Stores the result */
    
    /* Read the register */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIMR_ADDR16);
    /* Check whether the bit is set */
    if(FEC_EIMR_TXF_U32 == (u32RegisterValue & FEC_EIMR_TXF_U32))
    {
        bReturnValue = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else
    {
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        bReturnValue = (VAR(boolean, AUTOMATIC))FALSE;
    }
    return bReturnValue;
}
/*============================================================================*/
/**
* @brief         Checks whether the receive interrupt is enabled.
@param[in]       u8CtrlIdx Index of controller in which TxIRQ mask will be checked
* @retval        TRUE the interrupt is enabled
* @retval        FALSE the interrupt is disabled
*/
FUNC(boolean, ETH_CODE) Eth_Fec_IsRxIrqEnabled(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to read register value */
    VAR(boolean, AUTOMATIC) bReturnValue; /* Stores the result */
    
    /* Read the register */
    /**@violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIMR_ADDR16);
    /* Check whether the bit is set */
    if(FEC_EIMR_RXF_U32 == (u32RegisterValue & FEC_EIMR_RXF_U32))
    {
        bReturnValue = (VAR(boolean, AUTOMATIC))TRUE;
    }
    else
    {
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        bReturnValue = (VAR(boolean, AUTOMATIC))FALSE;
    }
    return bReturnValue;
}
/*================================================================================================*/
/**
* @brief         Reports received frames to the upper layer
* @param[in]     u8CtrlIdx Index of the controller to report receptions
* @param[in]     bIrq Selects between the poll driven and interrupt driven
*                mode (algorithm). The value TRUE means interrupt driven mode.
* @details       Function examines type of receive buffers. It begins
*                from the empty buffer found by previous call or from the
*                first one if no call has been done since the controller has
*                been enabled or from the latest known full buffer containing
*                the single-buffer-error-free frame.
* @par
*                Each buffer is checked to be error-free, buffer type is
*                examined and the buffer is reported via the
*                EthIf_RxIndication function call if the buffer type
*                is RX_BUF_SINGLE. All buffers of multi-buffer frame are
*                discarded when such frame is detected i.e. buffer type is
*                RX_BUF_MULTI_FINISHED.
* @par
*                Search ends when empty buffer is found i.e. buffer type
*                is RX_BUF_MULTI_UNFINISHED or RX_BUF_EMPTY or in the poll
*                driven mode when a second single-buffer frame is found
*                (this frame is not reported to the EthIf_RxIndication).
*                Function silently discards all buffers when the receive
*                buffers ring overflow is detected i.e. RX_BUF_OVERFLOW value
*                of buffer type is found.
* @note          The function reports all found frames in the interrupt driven
*                mode. In the poll driven mode it reports only the first found
*                frame signals whether there is at least another frame to be
*                received (in the next call).
* @return        In the poll driven mode signalizes whether a frame has been
*                reported to the EthIf module and whether another frame is
*                available. It shall be ignored in the interrupt driven mode.
* @retval        ETH_RECEIVED Only one frame received
* @retval        ETH_NOT_RECEIVED No frame received
* @retval        ETH_RECEIVED_MORE_DATA_AVAILABLE More frames received
*                frame was discarded.
*/
FUNC(Eth_RxStatusType, ETH_CODE) Eth_Fec_ReportReception ( \
                                                CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                                                CONST(boolean, AUTOMATIC) bIrq \
                                                         )
{
    VAR(uint8, AUTOMATIC) u8BufCtr; /* Buffer referencing variable */
    VAR(Eth_RxBufferType, AUTOMATIC) eBufferType; /* Used to obtain
                                             buffer type from lower layers */
    VAR(uint8, AUTOMATIC) u8MultiEnd = 0U; /* Used to obtain number of last buffer in
                                                     the multi-buffer frame */
    VAR(uint8, AUTOMATIC) u8BufCtrMax; /* Variable used to hold the buffers
        number - this should be faster than reading the configuration */
    VAR(uint32, AUTOMATIC) u32ProtectionCounter = 0U; /* Protection counter */
    /* --- Frame information storage temporary variables --- */
    VAR(uint32, AUTOMATIC) u32FrameStatus;
    VAR(uint16, AUTOMATIC) u16Length;
    P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) pu8DataPtr = NULL_PTR;
    VAR(Eth_FrameType, AUTOMATIC) u16EtherType;
    VAR(boolean, AUTOMATIC) bBroadcast;
    VAR(uint8, AUTOMATIC) u8EthIfCtrlIdx;  /* Controller which received it */
    /* --- Internal state machine state variables --- */
    VAR(boolean, AUTOMATIC) bFinishLoop; /* Decisions whether continue
                                              with buffer search stored here */
    VAR(boolean, AUTOMATIC) bFirstFrameFound; /* TRUE if some frame already
                                                found and reported to EthIf */
    VAR(Eth_RxStatusType, AUTOMATIC) eRetVal; /* Single return implementation
                                            needs to store the return value */
    /* The eRetVal could be used as a steering variable instead of the
       FirstFramFound but the readability would be decreased and the compiler
       will optimize it anyway */

    u8BufCtr = Eth_u8ActiveRxBuf[u8CtrlIdx];
    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
    u8EthIfCtrlIdx = ETH_CFG_CTRLIDXINETHIF(u8CtrlIdx); /* Get the value */
    /* No valid frames have been found yet */
    bFirstFrameFound = (VAR(boolean, AUTOMATIC))FALSE;
    eRetVal = ETH_NOT_RECEIVED;
    /* Initialize the loop-control variable */
    bFinishLoop = (VAR(boolean, AUTOMATIC)) FALSE;
    /* Get number of buffers */
    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
    u8BufCtrMax = (VAR(uint8, AUTOMATIC))(ETH_CFG_RXBUFTOTAL(u8CtrlIdx) - 1U);
    do
    {
        /** @violates @ref Eth_Fec_c_REF_17 MISRA rule 1.2 */
        eBufferType = Eth_Fec_GetRxBufferType(u8CtrlIdx, u8BufCtr, u8BufCtrMax, &u8MultiEnd);
        if((RX_BUF_SINGLE == eBufferType) || (RX_BUF_MULTI_FINISHED == eBufferType))
        {   /* Single buffer frames are the only to be reported */
            /* Get the buffer length and pointer to it */
            /** @violates @ref Eth_Fec_c_REF_17 MISRA rule 1.2 */
            Eth_Fec_GetRxBufferData(u8CtrlIdx, u8BufCtr, u8MultiEnd, &u16Length, &pu8DataPtr, &u32FrameStatus);

            /* Check whether the frame has been received without any error
             * and if is multicast check if is in the multicast pool */
             /* Regular broadcast and unicast address which is not multicast */
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
            if ((0U == (u32FrameStatus & (ETH_FEC_RXF_ERRORS_MASK|ETH_FEC_RXF_MULTICAST))) \
               /* Frame received in promiscuous mode */
               || (ETH_FEC_RXF_PROMISCUOUS == (u32FrameStatus & (ETH_FEC_RXF_ERRORS_MASK | ETH_FEC_RXF_PROMISCUOUS))) \
               /* Multicast address contained in pool */
               /** @violates @ref Eth_Fec_c_REF_15 MISRA rule 12.4 */
               || (((0U == (u32FrameStatus & ETH_FEC_RXF_ERRORS_MASK))) && ((VAR(boolean, AUTOMATIC))TRUE == Eth_Fec_IsPhysAddrAllowed(u8CtrlIdx, pu8DataPtr))) \
               )
#else
            if((0U == (u32FrameStatus & (ETH_FEC_RXF_ERRORS_MASK))))
#endif /* STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER */
            {   /* No error, frame can be passed to upper layers */
                /* Check whether there is already a frame to pass */
                if((VAR(boolean, AUTOMATIC))FALSE == bFirstFrameFound)
                {   /* No, this is the first found received valid frame */
                    /* Pass the received frame to the upper layer */
                    /* Parse the u16EtherType from the frame header */
                    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
                    /** @violates @ref Eth_Fec_c_REF_5 */
                    u16EtherType = ((VAR(uint16, AUTOMATIC))(*(pu8DataPtr + 12U)) << 8U);
                    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
                    /** @violates @ref Eth_Fec_c_REF_5 */
                    u16EtherType |= *(pu8DataPtr + 13U);
                    /* Check whether the frame is sent to a broadcast
                       address */
                    if(ETH_FEC_RXF_BROADCAST == (u32FrameStatus & ETH_FEC_RXF_BROADCAST))
                    {   /* bBroadcast */
                        bBroadcast = (VAR(boolean, AUTOMATIC))TRUE;
                    }
                    else
                    {   /* Unicast or multicast */
                        bBroadcast = (VAR(boolean, AUTOMATIC))FALSE;
                    }
                    /* Notify the EthIf - pass the Ethernet controller index,
                       u16EtherType, broadcast indication, frame source address,
                       pointer to the payload and the payload length */
                    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
                    EthIf_RxIndication (u8EthIfCtrlIdx, u16EtherType, bBroadcast, (pu8DataPtr + 6U), (pu8DataPtr + 14U), (u16Length - 14U) );
                    /* Forget that the frame was found if the interrupt
                       mode is used so all frames will be reported. In the
                       poll driven mode on the other hand remember that the
                       first frame has been already reported so only one frame
                       will be reported. */
                    eRetVal = ETH_RECEIVED;
                    if((VAR(boolean, AUTOMATIC))FALSE == bIrq)
                    {   /* Poll driven mode - remember */
                        bFirstFrameFound = (VAR(boolean, AUTOMATIC))TRUE;
                    }
                }
                else
                {   /* Another valid received frame has already been found */
                    /* Remember that there is another frame to be read and
                       stop the search */
                    eRetVal = ETH_RECEIVED_MORE_DATA_AVAILABLE;
                    bFinishLoop = ((VAR(boolean, AUTOMATIC))TRUE);
                    /* The processing shall start with this buffer when the
                       function is called next time */
                    Eth_u8ActiveRxBuf[u8CtrlIdx] = u8BufCtr;
                }
            }
            /* Clear the buffers */
            if ((VAR(boolean, AUTOMATIC))FALSE == bFinishLoop)
            {
                /* Clear the interrupt flags */
                Eth_Fec_ClearRxIrqFlag(u8CtrlIdx);
                /* Clear all the first buffer */
                Eth_Fec_ClearRxBuffer(u8CtrlIdx, u8BufCtr);
                /* Clear all others belong to frame */
                while(u8BufCtr != u8MultiEnd)
                {
                    u8BufCtr++;
                    if(u8BufCtr > u8BufCtrMax)
                    {
                        u8BufCtr = 0U;
                    }
                    Eth_Fec_ClearRxBuffer(u8CtrlIdx, u8BufCtr);
                }
                /* Continue with the next buffer */
                u8BufCtr++;
                if(u8BufCtr > u8BufCtrMax)
                {
                    u8BufCtr = 0U;
                }
                Eth_u8ActiveRxBuf[u8CtrlIdx] = u8BufCtr;
            }
        }
        else /* RX_BUF_MULTI_UNFINISHED || RX_BUF_EMPTY || RX_BUF_OVERFLOW */
        {
            /* Other states mean that loop has to end */
            bFinishLoop = ((VAR(boolean, AUTOMATIC))TRUE);
        }
        /* Protection against newerendless loop */
        u32ProtectionCounter++;
        if ((2U * (VAR(uint32, AUTOMATIC))(u8BufCtrMax)) <= u32ProtectionCounter)
        { /* Buffer ring was processed twice in a loop without exit */
          /* Note that this condition is unreachable at normal HW conditions */
            /* Terminate the loop */
            bFinishLoop = ((VAR(boolean, AUTOMATIC))TRUE);
        }
    }
    while(((VAR(boolean, AUTOMATIC))FALSE) == bFinishLoop);
    /* Handler of buffers overflow - discard all buffers */
    if(RX_BUF_OVERFLOW == eBufferType)
    {
        #if STD_ON == DEBUG_VARIABLES /* Only if debug variables are used */
            /* Increment the debug variable */
            Eth_RxBuffersOverflow[u8CtrlIdx] = Eth_RxBuffersOverflow[u8CtrlIdx] + 1U;
        #endif
        for(u8BufCtr = 0U; u8BufCtr <= u8BufCtrMax; u8BufCtr++)
        {
            Eth_Fec_ClearRxBuffer(u8CtrlIdx, u8BufCtr);
        }
    }

    /* Return information about availability of more buffers */
    return eRetVal;
}
/*============================================================================*/
/**
* @brief         Confirms transmission of all transmitted buffers
* @param[in]     u8CtrlIdx Index of the controller to report transmissions
* @details       Function examines all transmit buffers whether some of them
*                have been already sent and whether they should be confirmed.
*                EthIf_TxConfirmation is called for each such buffer.
* @return        Error report
* @retval        TRUE No error has occurred.
* @retval        FALSE Some error has occurred.
* 
*/
FUNC(boolean, ETH_CODE) Eth_Fec_ReportTransmission(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint8, AUTOMATIC) u8BufIdx; /* Counter used for buffer referencing */
    VAR(uint8, AUTOMATIC) u8TotalBufNum; /* Variable used to hold the buffs number
     - this should be faster than reading the configuration */
    VAR(uint8, AUTOMATIC) u8EthIfCtrlIdx; /* Copy of the configured parameter
       EthCtrlIdxInEthIf  - this should improve execution time (multiple
       access to memory is slower than access to register) */
    VAR(uint32, AUTOMATIC) u32BDAddr; /* BD addr. used by lower driver layers
     - to avoid its re-initializations during function calls in the loop
       it is placed here. Reading value from (ROM) memory through pointer is
       slower than local variable access (register or stack). */
    VAR(uint8, AUTOMATIC) u8BDIdx; /* Index of linked BD */
    VAR(uint32, AUTOMATIC) u32BDStatus; /* Status bits of linked BD */
    VAR(uint8, AUTOMATIC) u8TxBufFlag; /* Temporary Tx buffer flag */
    
    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
    u8EthIfCtrlIdx = ETH_CFG_CTRLIDXINETHIF(u8CtrlIdx); /* Get the value needed
                                  for EthIf_TxConfirmation callback call */
    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
    u8TotalBufNum = ETH_CFG_TXBUFTOTAL(u8CtrlIdx); /* Get number of buffers */
    /* Compiler_Warning: (diab) this should not be a warning because they are same type. 
    No potential problem here. */
    /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32BDAddr = ETH_CFG_TXBDSTARTADDRESS(u8CtrlIdx); /* Get TXBDs base
                  memory address value to pass it to lower drivers layers*/
    
    /* Search through all buffers */
    for(u8BufIdx = 0U; (Eth_u8LockedTxBufCount[u8CtrlIdx] > 0U) && (u8BufIdx < u8TotalBufNum); u8BufIdx++)
    {
        /* At first check status bits of buffer */
        u8TxBufFlag = Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx];
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        if((FEC_TXB_LOCK_U8 | FEC_TXB_CONF_U8 | FEC_TXB_FIRST_U8) ==((FEC_TXB_LOCK_U8 | FEC_TXB_CONF_U8 | FEC_TXB_FIRST_U8) & u8TxBufFlag))
        {   /* The frame is in LOCKEDAT or LOCKEDIT state */
            /* If there is link to BD, try to remove it */
            if( FEC_TXB_LINK_U8 == (FEC_TXB_LINK_U8 & u8TxBufFlag))
            {   
               u8BDIdx = Eth_au8TxBdOfBuf[u8CtrlIdx][u8BufIdx];
                /* There is link, may be removed only if FEC_TXBD_R_U32=0 and FEC_TXBD_TO1_U32=1
                  (if FEC_TXBD_TO1_U32 would be 0 it might be frame being turned into
                  LockedIT state with BD not written yet) */
                u32BDStatus = Eth_Fec_ReadTxBDBits(u32BDAddr,u8BDIdx);
                if( FEC_TXBD_TO1_U32 == ((FEC_TXBD_R_U32 | FEC_TXBD_TO1_U32) & u32BDStatus) )
                {   
                    /* Ready bit is zero -> frame was sent -> remove the link */
                    u8TxBufFlag &= (VAR(uint8, AUTOMATIC))(~FEC_TXB_LINK_U8);
                    /*Enter exclusive area before update software flag to prevent interfere */
                    Eth_au8TxBufFlags[u8CtrlIdx][u8BufIdx] = u8TxBufFlag;
                    /* Clear BufLinked flag */
                    u32BDStatus &= (VAR(uint32, AUTOMATIC))(~FEC_TXBD_TO1_U32);
                    /* Write modified bits back */
                    Eth_Fec_WriteTxBDBits(u32BDAddr, u8BDIdx, u32BDStatus);
                }
            }
            /* Call TxConfirmation and free buffers only if the link is gone */
            if( 0U == (FEC_TXB_LINK_U8 & u8TxBufFlag) )
            {   
                /* The link was removed -> LOCKEDAT state, call confirmation */
                /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
                EthIf_TxConfirmation( u8EthIfCtrlIdx, u8BufIdx);
                Eth_Fec_GiveBackTxBuffer(u8CtrlIdx, u8BufIdx); /* At last free the buffers */
                
                /* Update number of pending confirmations, need critical section because this is RMW access */
                SchM_Enter_Eth_ETH_EXCLUSIVE_AREA_01();
                Eth_u8LockedTxBufCount[u8CtrlIdx]--;
                SchM_Exit_Eth_ETH_EXCLUSIVE_AREA_01();
            }
        }
    }
    return (VAR(boolean, AUTOMATIC))TRUE; /*No error detection implemented yet*/
}
#if STD_ON == ETH_DEV_ERROR_DETECT
/*============================================================================*/
/**
* @brief         Checks whether the any frame longer than receive buffer
*                was received.
* @details       This function checks whether a frame is longer than configured
*                receive buffer length has been received since the previous
*                call. BABR interrupt flag is set even if the frame is
*                discarded by the hardware acceleration.
* @param[in]     u8CtrlIdx Index of controller which report too long frame message
* @return        - TRUE if too long frame has been received
*                - FALSE if too long frame has not been received
*/
FUNC(boolean, ETH_CODE) Eth_Fec_TooLongFrmRcvd(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to read register value */
    VAR(boolean, AUTOMATIC) bReturnValue; /* Stores the result */

    /* Read the register */
    /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16);
    /* Check whether the bit is set */
    if(FEC_EIR_BABR_U32 == (u32RegisterValue & FEC_EIR_BABR_U32))
    {
        bReturnValue = (VAR(boolean, AUTOMATIC))TRUE;
        /* Clear the bit (W1C) */
        /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16, FEC_EIR_BABR_W1C);
    }
    else
    {
        bReturnValue = (VAR(boolean, AUTOMATIC))FALSE;
    }
    return bReturnValue;

}
#endif /* ETH_DEV_ERROR_DETECT */

/*============================================================================*/
/**
* @brief         Returns lower four bytes of the controllers MAC address
* @details       Function reads MAC address from the register and returns it.
*                0xAABBCCDD is returned if the controller MAC address
*                is AA:BB:CC:DD:EE:FF
* @param[in]     u8CtrlIdx Index of controller to get 4 low bytes of PhysAddress
* @return        First four bytes of the MAC address.
*/

FUNC(uint32, ETH_CODE) Eth_Fec_GetPhysAddressLow(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    /* Return lower 32 bits of MAC address */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    return REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PALR_ADDR16);
}

/*============================================================================*/
/**
* @brief         Returns upper four bytes of the controllers MAC address
* @details       Function reads MAC address from the register and returns it.
*                0xEEFF is returned if the controller MAC address is
*                AA:BB:CC:DD:EE:FF.
* @param[in]     u8CtrlIdx Index of controller to get 2 high bytes of PhysAddress
* @return        Last two bytes of the MAC address.
*/

FUNC(uint16, ETH_CODE) Eth_Fec_GetPhysAddressHigh(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint32, AUTOMATIC) u32RegisterValue;
    
    /* Get upper 16 bits of MAC address and move them to appropriate position*/
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PAUR_ADDR16);
    u32RegisterValue = u32RegisterValue >> 16U;
    /* Return the obtained value */
    return (VAR(uint16, AUTOMATIC)) u32RegisterValue;
}

/*============================================================================*/
/**
* @brief         Update physical address of the controller.
* @param[in]     pPhysAddrPtr Pointer to MAC address which should set to
*                controller. The address in network byte order stored into 6
*                bytes of memory.
* @caution       This function may be called only when the controller is down.
*                Call of function Eth_ControllerInit change MAC address
*                to the default value!
* @implements    Eth_Fec_SetPhysAddr_Activity
*/

FUNC(boolean, ETH_CODE) Eth_Fec_SetPhysAddr(CONST(uint8, AUTOMATIC) u8CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr)
{
    VAR(boolean, AUTOMATIC) bReturnStatus = (VAR(boolean, AUTOMATIC))FALSE;
    VAR(uint32, AUTOMATIC) u32RegisterValue = (VAR(uint32, AUTOMATIC))0U;

    /* Change mac address only when the conroller is down */
    if(ETH_MODE_DOWN == Eth_Fec_CheckCtrlIsActive(u8CtrlIdx))
    {
        /* Prepare lower bytes of MAC */
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        u32RegisterValue = (uint32)(*(pPhysAddrPtr + 0U));
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        u32RegisterValue = ((u32RegisterValue << 8U) | (uint32)(*(pPhysAddrPtr + 1U)));
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        u32RegisterValue = ((u32RegisterValue << 8U) | (uint32)(*(pPhysAddrPtr + 2U)));
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        u32RegisterValue = ((u32RegisterValue << 8U) | (uint32)(*(pPhysAddrPtr + 3U)));
        /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */ 
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */        
        REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PALR_ADDR16, u32RegisterValue);
        /* Prepare higher bytes of MAC */
        u32RegisterValue = 0U;
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        u32RegisterValue = (uint32)(*(pPhysAddrPtr + 4U));
        /** @violates @ref Eth_Fec_c_REF_5 MISRA rule 17.4 */
        u32RegisterValue = ((u32RegisterValue << 8U) | (uint32)(*(pPhysAddrPtr + 5U)));
        u32RegisterValue = ((u32RegisterValue << 16U) | 0x8808U);
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        /** 
            @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
        REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_PAUR_ADDR16, u32RegisterValue);
        /* Set return status */
        bReturnStatus = (VAR(boolean, AUTOMATIC))TRUE;
    }
    return bReturnStatus;
    /** @violates @ref Eth_Fec_c_REF_9 MISRA rule 16.7 */
}
/** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
/*================================================================================================*/
/**
* @brief        Handle multicast addresses add or remove operations
* @details      This function handle add and remove operations with multicast
*               receive pool.
*               Handled pool of MAC address specifies the addresses which
*               will be pass to higher layers at frame reception.
* @param[in]    u8CtrlIdx Index of controller to be update the filter
* @param[in]    pPhysAddrPtr Pointer to the MAC address in network
*               byte order which will be added or removed to or from a pool.
* @param[in]    eAction This parameter defines the operation with a pool.
*               Value ETH_ADD_TO_FILTER behaves function to add new address into
*               a pool and ETH_REMOVE_FROM_FILTER means operation of removal
*               from the pool.
* @implements   Eth_Fec_UpdtePhysAddrFiltr_Activity
*/

FUNC(void, ETH_CODE) Eth_Fec_UpdtePhysAddrFiltr ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) pPhysAddrPtr, \
                        VAR(Eth_FilterActionType, AUTOMATIC) eAction \
                                                )
{
    /* Indicator of full open filter action */
    VAR(boolean, AUTOMATIC) bFullFilterOpenRequest;
    /* Indicator of full close filter action */
    VAR(boolean, AUTOMATIC) bFullFilterCloseRequest;
    /* Pattern for full open filter request */
    VAR(uint8, AUTOMATIC) au8FullFilterOpenPattern[] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
    /* Pattern for full close filter request */
    VAR(uint8, AUTOMATIC) au8FullFilterClosePattern[] = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

    /* Fill full open filter indicator */
    /** @violates @ref Eth_Fec_c_REF_17 MISRA rule 1.2 */
    bFullFilterOpenRequest = Eth_Fec_ComparePhysAddr(pPhysAddrPtr, au8FullFilterOpenPattern);
    /* Fill full close filter indicator */
    /** @violates @ref Eth_Fec_c_REF_17 MISRA rule 1.2 */
    bFullFilterCloseRequest = Eth_Fec_ComparePhysAddr(pPhysAddrPtr, au8FullFilterClosePattern);
    switch(eAction)
    {
        case ETH_ADD_TO_FILTER:
            if ((VAR(boolean, AUTOMATIC))TRUE == bFullFilterOpenRequest)
            { /* Full open filter action (ETH_ADD_TO_FILTER) */
                /* Multicast filter will be bypassed at reception */
                Eth_FEC_bMcastFullOpen[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))TRUE;
                /* Open all groups in GALR register */
                /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
                /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
                REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GALR_ADDR16, 0xffffffffU);
                /* Open all groups in GAUR register */
                /* @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */
                /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
                REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_GAUR_ADDR16, 0xffffffffU);
            }
            /** @requirements   SWS_Eth_00147 */
            else if ((VAR(boolean, AUTOMATIC))TRUE == bFullFilterCloseRequest)
            { /* Full close filter action (ETH_ADD_TO_FILTER) */
            /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
                /* Full close request excludes previous full open request */
                Eth_FEC_bMcastFullOpen[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))FALSE;
                /* Clean overflow flag */
                /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
                Eth_FEC_bMcastPoolOvf[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))FALSE;
                /* Clean the table */
                Eth_Fec_McastPoolClean(u8CtrlIdx);
                /* Reset the filter */
                Eth_Fec_McastGAClean(u8CtrlIdx);
            }
            else
            { /* Regular adding of PhysAddr into the pool (ETH_ADD_TO_FILTER) */
                if ((VAR(boolean, AUTOMATIC))FALSE == Eth_Fec_McastPoolAddItem(u8CtrlIdx, pPhysAddrPtr))
                { /* Table is full */
                    /* Once table is full Overflow tag is set  */
                    Eth_FEC_bMcastPoolOvf[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))TRUE;
                }
                /* Open Group Address for requested Physical Address */
                Eth_Fec_McastGAAdd(u8CtrlIdx, pPhysAddrPtr);
            }
            break;
        case ETH_REMOVE_FROM_FILTER:
            if ((VAR(boolean, AUTOMATIC))TRUE == bFullFilterOpenRequest)
            { /* Full open filter action (ETH_REMOVE_FROM_FILTER)  */
                Eth_FEC_bMcastFullOpen[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))FALSE;
            }
            /** @requirements   SWS_Eth_00147 */
            else if ((VAR(boolean, AUTOMATIC))TRUE == bFullFilterCloseRequest)
            { /* Full close filter action (ETH_REMOVE_FROM_FILTER) */
                /* Full close request excludes previous full open request */
                Eth_FEC_bMcastFullOpen[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))FALSE;
                /* Clean overflow flag */
                Eth_FEC_bMcastPoolOvf[u8CtrlIdx] = (VAR(boolean, AUTOMATIC))FALSE;
                /* Clean the table */
                Eth_Fec_McastPoolClean(u8CtrlIdx);
                /* NOTE: Filter Reset is done at recalculation */
            }
            else
            { /* Regular removal of Physical Address from Pool */
                (void)Eth_Fec_McastPoolRmvItem(u8CtrlIdx, pPhysAddrPtr);
            }
            if (((VAR(boolean, AUTOMATIC))FALSE == Eth_FEC_bMcastPoolOvf[u8CtrlIdx]) && ((VAR(boolean, AUTOMATIC))FALSE == Eth_FEC_bMcastFullOpen[u8CtrlIdx]))
            { /* No Pool overflow or full open request */
                /* Recalculate the pool addresses */
                Eth_Fec_McastGARecalculate(u8CtrlIdx);
            }
            break;
        default:
            ; /* Required by MISRA but no action needed */
            break;
    }
}
#endif /* STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER */

/*============================================================================*/
/**
* @brief         Clears all MIB Counters
* @details       Function disables the counters block, writes value 0 to all
*                counters and reenables the counters block.
* @param[in]     u8CtrlIdx Index of controller to be cleared the counters
*/

FUNC(void, ETH_CODE) Eth_Fec_ClearMIBCounters(CONST(uint8, AUTOMATIC) u8CtrlIdx)
{
    VAR(uint16, AUTOMATIC) u16TempCtr; /* Counter used to access MIB counters */ 
    
    /* Disable MIB */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_MIBC_ADDR16, FEC_MIBC_MIB_DISABLE_U32);
    /* Clear the MIB RAM */
    for(u16TempCtr = FEC_RMON_T_DROP_ADDR16; u16TempCtr <= FEC_IEEE_R_OCTETS_OK_ADDR16; u16TempCtr += 4U)
    {
        /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
        REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + (VAR(uint32, AUTOMATIC))u16TempCtr, 0U);
    }
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    /* Enable MIB */
    /**
        @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_MIBC_ADDR16, 0U);
}
/*============================================================================*/
/**
* @brief         Reads value of the given counter
* @param[in]     u8CtrlIdx Index of controller to be read
* @param[in]     u16Counter counter to read the value
* @param[out]    pValue Pointer to place where to store the counter value
*/

FUNC(void, ETH_CODE) Eth_Fec_GetCounterState    ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                        CONST(uint16, AUTOMATIC) u16Counter, \
                        CONSTP2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) pValue \
                                                )
{
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    *pValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + (VAR(uint32, AUTOMATIC))u16Counter);
}
#if STD_ON == ETH_CTRLENABLE_MII
/*============================================================================*/
/**
* @brief         Transfers management data over the MII
* @param[in]     u8CtrlIdx Index of controller to be transferred
* @param[in]     u8Trcv Transceiver to communicate with
* @param[in]     u8Reg Register which shall be accessed
* @param[in,out] pData Written/read data
* @param[in]     u32Operation Selection between write and read access
* @details       Function assembles the management frame and issues the bus
*                transaction, then it waits until the transaction finishes
*                and read data is returned in case of read access.
*                Waiting loop can be  broken if it reaches configured
*                number of iterations.
* @return        Failure status
* @retval        TRUE Success, no error has occurred.
* @retval        FALSE Failure, no response from the hardware within a timeout.
* @note          Function is present only if the macro ETH_CTRLENABLE_MII value
*                is equal to STD_ON.
*/
FUNC(boolean, ETH_CODE) Eth_Fec_DoMiiMMF    ( \
                        CONST(uint8, AUTOMATIC) u8CtrlIdx, \
                            CONST(uint8, AUTOMATIC) u8Trcv, \
                            CONST(uint8, AUTOMATIC) u8Reg, \
                            CONSTP2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) pData, \
                            CONST(uint32, AUTOMATIC) u32Operation \
                                            )
{
    VAR(uint32, AUTOMATIC) u32RegisterValue; /* Used to assemble 
                register value before writing and for registers reads */
    VAR(uint32, AUTOMATIC) u32ManipulationVar; /* Used for bit manipulations */
    VAR(volatile uint32, AUTOMATIC) u32ProtectionCounter; /* The loop is
            claimed infinite when this counter reaches configured value */
    VAR(boolean, AUTOMATIC) bReturnStatus;
    
    /* Initialize the loop status variables - The loop works correctly */
    bReturnStatus = ((VAR(boolean, AUTOMATIC))TRUE);
    /* Write the initial value */
    u32ProtectionCounter = 0U; 
    /* Clear the EIR[MII] flag by writing 1 to it */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16, FEC_EIR_MII_W1C);   
    /* Start assembling the frame with ST, TA field and select operation */
    u32RegisterValue = (VAR(uint32, AUTOMATIC)) (FEC_MMFR_ST_VAL_U32|u32Operation|FEC_MMFR_TA_VAL_U32);
    /* Add the PHY address */
    /* Move it to the right position */
    u32ManipulationVar = (VAR(uint32, AUTOMATIC))u8Trcv << 23U; 
    /* Clear any inappropriate bits */
    u32ManipulationVar = u32ManipulationVar & FEC_MMFR_PA_U32; 
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
    u32RegisterValue = u32RegisterValue | u32ManipulationVar; /* Apply it */
    /* Add the register address */
    /* Move it to the right position */
    u32ManipulationVar = (VAR(uint32, AUTOMATIC))u8Reg << 18U;
    /* Clear any inappropriate bits */
    u32ManipulationVar = u32ManipulationVar & FEC_MMFR_RA_U32; 
    u32RegisterValue = u32RegisterValue | u32ManipulationVar; /* Apply it */
    /* Add data - ignored by read operation */
    u32RegisterValue = u32RegisterValue | (* pData);
    /* Write assembled value to the register - it 
       triggers the MII MMF transaction */
    /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
    /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
    REG_WRITE32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_MMFR_ADDR16, u32RegisterValue);
    /* Wait until transaction is finished */
    do
    {      
        /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_EIR_ADDR16);
        /* Infinite loop protection */
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
        /* Check whether the loop is infinite */
        if(u32ProtectionCounter >= ETH_INFINITE_LOOP_PROTECTION)
        {   /* Yes */
            /* Loop is infinite and has to be broken*/
            bReturnStatus = ((VAR(boolean, AUTOMATIC))FALSE); 
            #if STD_ON == DEBUG_VARIABLES
            /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */
                Eth_MiiFailed[u8CtrlIdx] = Eth_MiiFailed[u8CtrlIdx] + 1U;
            #endif
            break;                /* Break the loop */
        }
        u32ProtectionCounter = u32ProtectionCounter + 1U; /* Increment counter */
        
    }
    while(FEC_EIR_MII_W1C != (u32RegisterValue & FEC_EIR_MII_W1C));
    /* Check whether the previous code has been succesful */
    if(((VAR(boolean, AUTOMATIC))TRUE) == bReturnStatus)
    {   /* Everything OK, continue */
        /* Read the data value from register - should 
           be ignored by write operation */
        /** @violates @ref Eth_Fec_c_REF_7 MISRA rule 11.1 */    
        /** @violates @ref Eth_Fec_c_REF_19 MISRA rule 11.3 */    
        u32RegisterValue = REG_READ32(Eth_u32BaseAddr[u8CtrlIdx] + FEC_MMFR_ADDR16);
        * pData = (VAR(uint16, AUTOMATIC))(u32RegisterValue & FEC_MMFR_DATA_U32);
    }
    return bReturnStatus; 
} 
#endif /* ETH_CTRLENABLE_MII */



#define ETH_STOP_SEC_CODE
/**
 * @violates @ref Eth_Fec_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_Fec_c_REF_4 MISRA rule 19.15
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
