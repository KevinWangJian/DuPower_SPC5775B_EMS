/**
*   @file    Adc_Eqadc_Irq.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - ADCDig Interrupt source file.
*   @details  Autosar Adc Interrupt source file.
*
*   @addtogroup ADC
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : EQADC
*   Dependencies         : none
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

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Eqadc_Irq_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement.
*
* @section Adc_Eqadc_Irq_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h.
* There are different kinds of execution code sections.
* 
* @section Adc_Eqadc_Irq_c_REF_3
* Violates MISRA 2004 Required Rule 14.7, Return statement before end of function.
* The return statement are used to simplify the code structure and easier readability.
* 
* @section Adc_Eqadc_Irq_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned int to pointer. This macro compute the
* address of any register by using the hardware offset of the controller. The address calculated as an
* unsigned int is passed to  a macro for initializing the pointer with that address.
*
* @section Adc_Eqadc_Irq_c_REF_6
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer 
* arithmetic but used due to the code complexity.
*
* @section Adc_Eqadc_Irq_c_REF_7
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions at file scope shall
* have internal linkage unless external linkage is required.
* State variables may be used by LLD layer.
*
* @section Adc_Eqadc_Irq_c_REF_8
* Violates MISRA 2004 Required Rule 8.8, An external object or function shall be declared
* in one and only one file.
* This violation cannot be removed due to the interaction with MCL module.
*
* @section Adc_Eqadc_Irq_c_REF_9
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Eqadc_Irq_c_REF_10
* Violates MISRA 2004 Advisory Rule 11.3,
* A cast should not be performed between a pointer type and an integral type.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers shall not more than 31 characters
* Violation is needed because of Autosar restrictions for naming File version check macros.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external Units
* 3) internal and external interfaces from this Unit
==================================================================================================*/
#include "Adc_Ipw.h"
#define USER_MODE_REG_PROT_ENABLED                (ADC_USER_MODE_REG_PROT_ENABLED)
#include "SilRegMacros.h"
#include "Mcal.h"
#include "SchM_Adc.h"
#ifdef ADC_DMA_SUPPORTED
  #include "CDD_Mcl.h"
#endif
#include "Adc_Siu.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_EQADC_AR_VENDOR_ID_IRQ_C                 43
#define ADC_EQADC_AR_RELEASE_MAJOR_VERSION_IRQ_C     4
#define ADC_EQADC_AR_RELEASE_MINOR_VERSION_IRQ_C     0
#define ADC_EQADC_AR_RELEASE_REVISION_VERSION_IRQ_C  3
#define ADC_EQADC_SW_MAJOR_VERSION_IRQ_C             1
#define ADC_EQADC_SW_MINOR_VERSION_IRQ_C             0
#define ADC_EQADC_SW_PATCH_VERSION_IRQ_C             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC IPW header file are from the same vendor */
#if (ADC_EQADC_AR_VENDOR_ID_IRQ_C != ADC_VENDOR_ID_IPW_H)
    #error "Adc_Eqadc_Irq.c and Adc_Ipw.h have different vendor ids"
#endif

/* Check if source file and ADC IPW header file are of the same Autosar version */
#if ((ADC_EQADC_AR_RELEASE_MAJOR_VERSION_IRQ_C != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_EQADC_AR_RELEASE_MINOR_VERSION_IRQ_C != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_EQADC_AR_RELEASE_REVISION_VERSION_IRQ_C != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AutoSar Version Numbers of Adc_Eqadc_Irq.c and Adc_Ipw.h are different"
#endif

/* Check if source file and ADC IPW header file are of the same Software version */
#if ((ADC_EQADC_SW_MAJOR_VERSION_IRQ_C != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_EQADC_SW_MINOR_VERSION_IRQ_C != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_EQADC_SW_PATCH_VERSION_IRQ_C != ADC_SW_PATCH_VERSION_IPW_H) \
    )
    #error "Software Version Numbers of Adc_Eqadc_Irq.c and Adc_Ipw.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((ADC_EQADC_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_EQADC_AR_RELEASE_MINOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Eqadc_Irq.c and Mcal.h are different"
 #endif 
 /* Check if source file and SilREgMacros header file are of the same AutoSar version */
 #if ((ADC_EQADC_AR_RELEASE_MAJOR_VERSION_IRQ_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_EQADC_AR_RELEASE_MINOR_VERSION_IRQ_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Eqadc_Irq.c and SilRegMacros.h are different"
 #endif 
 
 #ifdef ADC_DMA_SUPPORTED
  /* Check if source file and DMA header file are of the same Autosar version */
  #if ((ADC_EQADC_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
       (ADC_EQADC_AR_RELEASE_MINOR_VERSION_IRQ_C != MCL_AR_RELEASE_MINOR_VERSION)  \
      )
      #error "AutoSar Version Numbers of Adc_Eqadc_Irq.c and CDD_Mcl.h are different"
  #endif
  /* Check if source file and Mcl_Types.h are of the same Autosar version */
  #if ((ADC_EQADC_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
       (ADC_EQADC_AR_RELEASE_MINOR_VERSION_IRQ_C != MCL_TYPES_AR_RELEASE_MINOR_VERSION)  \
      )
      #error "AutoSar Version Numbers of Adc_Eqadc_Irq.c and Mcl_Types.h are different"
  #endif
 #endif
#endif

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

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

#ifdef ADC_DMA_SUPPORTED
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_9 The compiler/linker shall be checked 31 for external identifiers */
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/**
 * @violates @ref Adc_Eqadc_Irq_c_REF_1 MemMap.h is included after each section define in order to set the current memory section as defined by AUTOSAR
 * @violates @ref Adc_Eqadc_Irq_c_REF_2 This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
 */
#include "MemMap.h"

/**
 * @brief          Internal buffer used by DMA to transfer blocks with gaps.
 * @violates @ref Adc_Eqadc_Irq_c_REF_7 This warning appears when defining functions or objects that will be used by the upper layers.
 * @violates @ref Adc_Eqadc_Irq_c_REF_8 declaration of an external object or function 
*/
extern VAR(Adc_ValueGroupType,ADC_VAR) Adc_Eqadc_DmaInternalResultBuffer[ADC_MAX_HW_UNITS];

/** @violates @ref Adc_Eqadc_Irq_c_REF_9 The compiler/linker shall be checked 31 for external identifiers */
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/**
 * @violates @ref Adc_Eqadc_Irq_c_REF_1 MemMap.h is included after each section define in order to set the current memory section as defined by AUTOSAR
 * @violates @ref Adc_Eqadc_Irq_c_REF_2 This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
 */
#include "MemMap.h"
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
#endif /* ADC_DMA_SUPPORTED */

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define ADC_START_SEC_CODE
/**
 * @violates @ref Adc_Eqadc_Irq_c_REF_1 MemMap.h is included after each section define in order to set the current memory section as defined by AUTOSAR
 * @violates @ref Adc_Eqadc_Irq_c_REF_2 This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
 */
#include "MemMap.h"

#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult0(void);
#endif /* #if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult1(void);
#endif /* #if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult2(void);
#endif /* #if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult3(void);
#endif /* #if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON)*/

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult4(void);
#endif /* #if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult5(void);
#endif /* #if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult0(void);
#endif /* #if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO1_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult1(void);
#endif /* #if (ADC_EQADC_B_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult2(void);
#endif /* #if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO3_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult3(void);
#endif /* #if (ADC_EQADC_B_FIFO3_ENABLED == STD_ON)*/

#if (ADC_EQADC_B_FIFO4_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult4(void);
#endif /* #if (ADC_EQADC_B_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO5_ENABLED == STD_ON)
/** @violates @ref Adc_Eqadc_Irq_c_REF_8 Function declaration */
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult5(void);
#endif /* #if (ADC_EQADC_B_FIFO5_ENABLED == STD_ON) */

#ifdef ADC_DMA_SUPPORTED
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_LimitCheckValueInRange
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_DmaInterruptCommonFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
);
#endif /* #ifdef ADC_DMA_SUPPORTED */

#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcACFifo0Empty);
ISR(Adc_Eqadc_EqadcARFifo0Full);
#endif /* #if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcACFifo1Empty);
ISR(Adc_Eqadc_EqadcARFifo1Full);
#endif /* #if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcACFifo2Empty);
ISR(Adc_Eqadc_EqadcARFifo2Full);
#endif /* #if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcACFifo3Empty);
ISR(Adc_Eqadc_EqadcARFifo3Full);
#endif /* #if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcACFifo4Empty);
ISR(Adc_Eqadc_EqadcARFifo4Full);
#endif /* #if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcACFifo5Empty);
ISR(Adc_Eqadc_EqadcARFifo5Full);
#endif /* #if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcBCFifo0Empty);
ISR(Adc_Eqadc_EqadcBRFifo0Full);
#endif /* #if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO1_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcBCFifo1Empty);
ISR(Adc_Eqadc_EqadcBRFifo1Full);
#endif /* #if (ADC_EQADC_B_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcBCFifo2Empty);
ISR(Adc_Eqadc_EqadcBRFifo2Full);
#endif /* #if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO3_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcBCFifo3Empty);
ISR(Adc_Eqadc_EqadcBRFifo3Full);
#endif /* #if (ADC_EQADC_B_FIFO3_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO4_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcBCFifo4Empty);
ISR(Adc_Eqadc_EqadcBRFifo4Full);
#endif /* #if (ADC_EQADC_B_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO5_ENABLED == STD_ON)
ISR(Adc_Eqadc_EqadcBCFifo5Empty);
ISR(Adc_Eqadc_EqadcBRFifo5Full);
#endif /* #if (ADC_EQADC_B_FIFO5_ENABLED == STD_ON) */

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_CFIFO_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_CFifoEmptyCommonFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
);
#endif /* #if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_RFifoFullCommonFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
);

LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_FifoDisableFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
);
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */

LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_UpdateQueue
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
);

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
LOCAL_INLINE FUNC(boolean, ADC_CODE) Adc_Eqadc_CheckNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
);
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */

LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_RecordResult
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
);

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_UpdateGroupState
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
);
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_UpdateQueue
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
)
{
    /* Remove ongoing group from array */
    Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIndex] = ADC_INVALID_GROUPS_ID;
#if (ADC_ENABLE_QUEUING == STD_ON)
    Adc_RemoveFromQueue(Unit, 0U);
    #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
    if (Adc_aUnitStatus[Unit].SwNormalQueueIndex > 0U)
    {
        Adc_Eqadc_StartNormalConversion(Unit);
    }
    #endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */
#else
    /* no element will be present in the queue */
    Adc_aUnitStatus[Unit].SwNormalQueueIndex = 0U;
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */
}

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
LOCAL_INLINE FUNC(boolean, ADC_CODE) Adc_Eqadc_CheckNotification
(
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(boolean, AUTOMATIC) bCallNotification = (boolean) FALSE;

    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
    if ((ADC_NOTIFICATION_ENABLED == Adc_aGroupStatus[Group].eNotification) && \
        (NULL_PTR != Adc_pCfgPtr->pGroups[Group].Notification)
       )
    {
        bCallNotification = (boolean)TRUE;
    }
    return bCallNotification;
}
#endif /* ADC_GRP_NOTIF_CAPABILITY == STD_ON */

LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_RecordResult
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
)
{
    VAR(Adc_ValueGroupType, AUTOMATIC) ResultIdx;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = NULL_PTR;
    VAR(Adc_ValueGroupType, AUTOMATIC) AdcCdrvalue = (Adc_ValueGroupType)0U;
#if ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) || ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) && (ADC_ENABLE_LIMIT_CHECK == STD_ON)))
    VAR(uint8, AUTOMATIC) u8Shift;
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)... */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    /* bFlag to set if ADC results are in the range selected */
    VAR(boolean,AUTOMATIC) bFlag = (boolean)TRUE;
    VAR(Adc_ValueGroupType, AUTOMATIC) AdcTemp = 0U;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    pResult = (pGroupPtr->pResultsBufferPtr[Group]);
    GroupSamples = (pGroupPtr->NumSamples);
    ResultIdx = ((GroupSamples * Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex]) + Adc_aGroupStatus[Group].ResultIndex);
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    ChIndex = Adc_GroupChannelIndex(Group, Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex]);
#if ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) || ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) && (ADC_ENABLE_LIMIT_CHECK == STD_ON)))
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    u8Shift = (14U - Adc_pCfgPtr->pChannels[Unit][ChIndex].Res);
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)... */

    /* Read RFIFO into RAM buffer after right aligned */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    AdcCdrvalue = REG_READ16(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex) + 2U);
    /* Clear the RFDF bit in FISR0 register by writing 1 to it */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_FISR_RFDF_U32);
    
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
    AdcCdrvalue = (Adc_ValueGroupType)((uint32)AdcCdrvalue & EQADC_DATA_MASK_U32) >> u8Shift;
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) */

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    if((boolean)TRUE == Adc_ChannelsLimitCheckingCfg[Unit][ChIndex].bChannelLimitCheck)
    {
    #if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
        AdcTemp = (Adc_ValueGroupType)((uint32)AdcCdrvalue >> u8Shift);
    #else
        AdcTemp = AdcCdrvalue;
    #endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) */
        bFlag = (boolean)Adc_CheckConversionValuesInRange(AdcTemp, Unit, ChIndex);
        if (bFlag == (boolean)TRUE)
        {
            Adc_aGroupStatus[Group].bLimitCheckFailed = (boolean)FALSE;
            /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
            pResult[ResultIdx] = (Adc_ValueGroupType)AdcCdrvalue;
        }
        else
        {
            Adc_aGroupStatus[Group].bLimitCheckFailed = (boolean)TRUE;
            Adc_aGroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;
            /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
            return (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
        pResult[ResultIdx] = (Adc_ValueGroupType)AdcCdrvalue;
    }
#else
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    pResult[ResultIdx] = (Adc_ValueGroupType)AdcCdrvalue;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

    return (Std_ReturnType)E_OK;
}

#if defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__)
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_LimitCheckValueInRange
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group
)
{
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Std_ReturnType, AUTOMATIC) ReadGroupRet = (Std_ReturnType)E_OK;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(Adc_ValueGroupType, AUTOMATIC) ResultValue;
    VAR(Adc_ValueGroupType, AUTOMATIC) ResultTemp;
    VAR(uint8, AUTOMATIC) u8Shift;
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
    ChIndex = Adc_pCfgPtr->pGroups[Group].pAssignment[0];
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
    u8Shift = (14U - (Adc_pCfgPtr->pChannels[Unit][ChIndex].Res));
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
    ResultValue = (Adc_ValueGroupType)(Adc_Eqadc_DmaInternalResultBuffer[Unit] & EQADC_DATA_MASK_U32);
    ResultTemp = ResultValue >> u8Shift;
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
    ResultValue = ResultTemp;
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) */

    if((boolean)FALSE == Adc_CheckConversionValuesInRange(ResultTemp, Unit, ChIndex))
    {
        Adc_aGroupStatus[Group].bLimitCheckFailed = (boolean)TRUE;
        ReadGroupRet = (Std_ReturnType)E_NOT_OK;
    }
    else
    {
        Adc_aGroupStatus[Group].bLimitCheckFailed = (boolean)FALSE;
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
        pResult = Adc_pCfgPtr->pGroups[Group].pResultsBufferPtr[Group] + Adc_aGroupStatus[Group].ResultIndex;
        *pResult = ResultValue;
    }
    return ReadGroupRet;
}
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
/**
* @brief          This function handles the DMA Interrupt common function for all FIFOs
*                 on all eQADC units.
* @details        This function handles the DMA Interrupt common function.
*
* @param[in]      u8EqadcIdx   EQADC Unit
* @param[in]      u8FifoIndex  FIFO from 0 to 5.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE)Adc_Eqadc_DmaInterruptCommonFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
)
{
    VAR(Adc_HwUnitType, AUTOMATIC) Unit;
    VAR(Adc_GroupType, AUTOMATIC) Group = (Adc_GroupType)0U;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pResult = NULL_PTR;
    VAR(Adc_ChannelIndexType, AUTOMATIC) ChIdx = (Adc_ChannelIndexType)0U;
    /* Streaming num samples should be atleast 1U */
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples = (Adc_StreamNumSampleType)1U;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
    VAR(uint8, AUTOMATIC) u8Shift;
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) */
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn = (Std_ReturnType)E_OK;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = NULL_PTR;
    VAR(Mcl_ChannelType, AUTOMATIC) DmaChannel = 0U;
    VAR(Mcl_DmaTcdType*, AUTOMATIC) TcdAddress;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(boolean, AUTOMATIC)  bCallNotification = (boolean) FALSE;
#endif

    if(NULL_PTR != Adc_pCfgPtr)
    {
        /* enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_13();

        /*Obtain the active group*/
        Group = Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIndex];
        if(ADC_INVALID_GROUPS_ID == Group)
        {
            /* exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
            /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
            return;
        }
        Adc_aGroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
        Unit = Adc_GroupUnit(Group);
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
        pGroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
        GroupSamples = pGroupPtr->NumSamples;
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
        ChIndex = Adc_pCfgPtr->pGroups[Group].pAssignment[0];
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
        if ((boolean)TRUE == Adc_ChannelsLimitCheckingCfg[Unit][ChIndex].bChannelLimitCheck)
        {
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_LimitCheckValueInRange(Unit, Group))
            {
                if (ADC_CONV_MODE_ONESHOT == pGroupPtr->eMode)
                {
                    if(ADC_TRIGG_SRC_SW == pGroupPtr->eTriggerSource)
                    {
                        /* Disable the DMA cmd channel*/
                        DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIndex << 1U)];
                        Mcl_DmaDisableHwRequest(DmaChannel);
                        /* Disable the DMA result channel*/
                        DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIndex << 1U) + 1U];
                        Mcl_DmaDisableHwRequest(DmaChannel);
                    }
                }
                else
                {
                    /* Start the DMA cmd channel */
                    DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIndex << 1U)];
                    Mcl_DmaEnableHwRequest(DmaChannel);
                    /* Start the DMA result channel */
                    DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIndex << 1U) + 1U];
                    Mcl_DmaEnableHwRequest(DmaChannel);
                }
                /* Exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
                /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
                return;
            }
        }
        else
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
        {
            /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
            pResult = (pGroupPtr->pResultsBufferPtr[Group] + Adc_aGroupStatus[Group].ResultIndex);
            /* if ISR Alignment Samples is true, then align to right the samples of current group */
            for(ChIdx = 0U; ChIdx < pGroupPtr->AssignedChannelCount; ChIdx++)
            {
                /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
                ChIndex = Adc_GroupChannelIndex(Group, ChIdx);
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
                /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
                u8Shift = (14U - (Adc_pCfgPtr->pChannels[Unit][ChIndex].Res));
                /* Read RFIFO into RAM buffer  after right aligned */
                /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
                *(pResult + (ChIdx*(GroupSamples))) = (Adc_ValueGroupType)((uint32)((*(pResult + (ChIdx*(GroupSamples)))) & EQADC_DATA_MASK_U32) >> u8Shift);
#else
                /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be the only allowed form of pointer arithmetic */
                *(pResult + (ChIdx*(GroupSamples))) = (Adc_ValueGroupType)((uint32)(*(pResult + (ChIdx*(GroupSamples)))) & EQADC_DATA_MASK_U32);
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) */
            }
        }
        /* increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed */
        Adc_aGroupStatus[Group].ResultIndex++;
        if(ADC_BUSY == Adc_aGroupStatus[Group].eConversion)
        {
            Adc_aGroupStatus[Group].eConversion = ADC_COMPLETED;
        }
        /* if all samples completed, wrap to 0 */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
        if (Adc_aGroupStatus[Group].ResultIndex >= GroupSamples)
        {
            Adc_aGroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;
            
            if((ADC_STREAM_BUFFER_LINEAR == pGroupPtr->eBufferMode) && (ADC_ACCESS_MODE_STREAMING == pGroupPtr->eAccessMode))
            {
                /* Stop Conversion [ADC316] */
                /* the below func will stop the conversion and abort the current group conversion,
                is important to abort the current, otherwise, another interrupt occurs after the stop */
                FuncReturn = Adc_Eqadc_FifoDisableFunc(u8EqadcIdx, u8FifoIndex);
                
                if((Std_ReturnType)E_OK == FuncReturn)
                {
#if(STD_ON == ADC_HW_TRIGGER_API)
                    /* hardware triggered group */
                    if (ADC_TRIGG_SRC_HW == pGroupPtr->eTriggerSource)
                    {
                        Adc_aUnitStatus[Unit].HwNormalQueue[0] = 0U;
                        Adc_aUnitStatus[Unit].HwNormalQueueIndex = 0U;   /* Filled slots in the Hw queue */
                        /* Disable the hardware trigger source */
                        Adc_Siu_DisableHwTrigger((uint8)u8EqadcIdx, (uint8)u8FifoIndex);
                    }
                    else
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
                    {
                        Adc_Eqadc_UpdateQueue(Unit, u8EqadcIdx, u8FifoIndex);
                    }
#if(STD_ON == ADC_GRP_NOTIF_CAPABILITY)
                    bCallNotification = Adc_Eqadc_CheckNotification(Group);
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
                }
                /* exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
#if(STD_ON == ADC_GRP_NOTIF_CAPABILITY)
                if((boolean)TRUE == bCallNotification)
                {
                    pGroupPtr->Notification();
                }
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
                /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
                return;
            }
        }
        if (ADC_CONV_MODE_CONTINUOUS == pGroupPtr->eMode)
        {
            if (ADC_TRIGG_SRC_SW == pGroupPtr->eTriggerSource)
            {
                /* if all samples completed, wrap to 0 */
                if (Adc_aGroupStatus[Group].ResultIndex >= pGroupPtr->NumSamples)
                {
                    Adc_aGroupStatus[Group].ResultIndex = 0U;
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
                    pResult = pGroupPtr->pResultsBufferPtr[Group];
                    DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIndex*2U)+1U];
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
                    TcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress(DmaChannel);
                    /* configure the destination result address in TCD of the DMA channels */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
                    Mcl_DmaTcdSetDaddr(TcdAddress, (uint32)pResult);
                }
            }
            /* Start the DMA cmd channel */
            DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][u8FifoIndex*2U];
            Mcl_DmaEnableHwRequest(DmaChannel);
            /* Start the DMA result channel */
            DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIndex*2U)+1U];
            Mcl_DmaEnableHwRequest(DmaChannel);
        }
        else
        {
            /* one-shot conversion */
            if (ADC_TRIGG_SRC_SW == pGroupPtr->eTriggerSource) /* software trigger group */
            {
                Adc_aGroupStatus[Group].ResultIndex = 0U;
                /* Disable the FIFO */
                FuncReturn = Adc_Eqadc_FifoDisableFunc(u8EqadcIdx, u8FifoIndex);
                if (FuncReturn == (Std_ReturnType)E_OK)
                {
                    Adc_Eqadc_UpdateQueue(Unit, u8EqadcIdx, u8FifoIndex);
                }
            }
#if(STD_ON == ADC_HW_TRIGGER_API)
            else  /* hardware trigger group */
            {
                /* if all samples completed, wrap to 0 */
                if (Adc_aGroupStatus[Group].ResultIndex >= pGroupPtr->NumSamples)
                {
                    Adc_aGroupStatus[Group].ResultIndex = 0U;
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
                    pResult = pGroupPtr->pResultsBufferPtr[Group];
                    DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIndex*2U)+1U];
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
                    TcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress(DmaChannel);
                    /* Configure the destination result address in TCD of the DMA channels */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
                    Mcl_DmaTcdSetDaddr(TcdAddress, (uint32)pResult);
                }
                /* Start the DMA cmd channel */
                DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][u8FifoIndex*2U];
                Mcl_DmaEnableHwRequest(DmaChannel);
                /* Start the DMA result channel */
                DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIndex*2U)+1U];
                Mcl_DmaEnableHwRequest(DmaChannel);
            }
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
        }
#if(STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        bCallNotification = Adc_Eqadc_CheckNotification(Group);
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
        /* exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13();
#if(STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        if((boolean)TRUE == bCallNotification)
        {
            pGroupPtr->Notification();
        }
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
    }
}
#endif /* #if defined(ADC_DMA_SUPPORTED) */

#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the Irq CFIFO Empt Interrupt common function for all FIFOs
*                 on all qEADC units.
* @details        This function handles Irq CFIFO Empt Interrupt common function for all FIFOs.
*
* @param[in]      u8EqadcIdx   EQADC Unit.
* @param[in]      u8FifoIndex  FIFO from 0 to 5.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_CFifoEmptyCommonFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
)
{
    VAR(Adc_ChannelIndexType, AUTOMATIC) ChannelsInGrp;
    VAR(Adc_ChannelIndexType, AUTOMATIC) ChIndex;
    VAR(uint32, AUTOMATIC) FifoCmdmsg;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit;
    VAR(Adc_GroupType, AUTOMATIC) Group;

    if(NULL_PTR != Adc_pCfgPtr)
    {
        /* Enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_14();
        /* Obtain the active group */
        Group = Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIndex];
        if(ADC_INVALID_GROUPS_ID == Group)
        {
            /* Clear the CFFF bit in FISR1 register by writing 1 to it */
            /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_FISR_CFFF_U32);
            /* exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();
            /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
            return;
        }
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
        Unit = Adc_GroupUnit(Group);
        
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
        ChannelsInGrp = Adc_pCfgPtr->pGroups[Group].AssignedChannelCount;
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
        ChIndex = Adc_GroupChannelIndex(Group, Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIndex]);
        /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
        if ((Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIndex] == (ChannelsInGrp-1U)) && \
            (ADC_CONV_MODE_ONESHOT == Adc_pCfgPtr->pGroups[Group].eMode) \
           )
        {
            /* Last ADC channel, hence set the EOQ Flag */
            /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
            FifoCmdmsg = ((Adc_pCfgPtr->pChannels[Unit][ChIndex].u32Msg)|(EQADC_RESULT_FIFO_OFFSET_U32*u8FifoIndex) |
                          EQADC_ADC_WRITE_CONFIG_EOQ_U32);
        }
        else
        {
            /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
            FifoCmdmsg = ((Adc_pCfgPtr->pChannels[Unit][ChIndex].u32Msg)|(EQADC_RESULT_FIFO_OFFSET_U32*u8FifoIndex));
        }
        
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /* Write command data to CFIFO PUSH register*/
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex), FifoCmdmsg);
        /* Clear the CFFF bit in FISR1 register by writing 1 to it */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_FISR_CFFF_U32);
        /* Increment count for number of messages transferred to CFIFO*/
        Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIndex]++;
        /* Disable till conversion is complete */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_BIT_CLEAR16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_IDCR_CFFE_U16);

        /* exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14();
    }
    else
    {
        /* Clear the CFFF bit in FISR1 register by writing 1 to it */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
       REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_FISR_CFFF_U32);
    }
}
#endif /* #IF (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_UpdateGroupState
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit;
    VAR(Adc_ChannelIndexType, AUTOMATIC) ChannelsInGrp;
    VAR(Adc_StreamNumSampleType, AUTOMATIC) GroupSamples;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn = (Std_ReturnType)E_OK;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = NULL_PTR;
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
    VAR(boolean, AUTOMATIC) bCallNotification = (boolean)FALSE;
#endif /* STD_ON == ADC_GRP_NOTIF_CAPABILITY */

    /* Obtain the active group */
    Group = Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIndex];
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    Unit = Adc_GroupUnit(Group);
    /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
    ChannelsInGrp = pGroupPtr->AssignedChannelCount;
    GroupSamples = pGroupPtr->NumSamples;

    /* Increment count for messages read from RFIFO */
    Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex]++;
    
    if (Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex] == ChannelsInGrp)
    {
        /* Clear variable for next use */
        Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIndex] = 0U;
        Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex] = 0U;
    
        /* Disable CFIFO and RFIFO interrupt */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_BIT_CLEAR16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_RFDE_U16));
    
        /* increment ResultIndex with modulo 'NumSamples' to remember that another sample is completed */
        Adc_aGroupStatus[Group].ResultIndex++;
        /* at least once the group was converted */
        Adc_aGroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;
        
        if(ADC_BUSY == Adc_aGroupStatus[Group].eConversion)
        {
            Adc_aGroupStatus[Group].eConversion = ADC_COMPLETED;
        }
    
        if(Adc_aGroupStatus[Group].ResultIndex >= GroupSamples) /* if all samples completed, wrap to 0 */
        {
            Adc_aGroupStatus[Group].eConversion = ADC_STREAM_COMPLETED;
            
            if((ADC_STREAM_BUFFER_LINEAR == pGroupPtr->eBufferMode) && (ADC_ACCESS_MODE_STREAMING == pGroupPtr->eAccessMode))
            {
                /* ADC078 Disable Interrupt Status*/
                /* Stop Conversion [ADC316] */
                /* the following func stop the conversion and abort the current group conversion,
                is important to abort the current, otherwise, another interrupt occurs after the stop */
                FuncReturn = Adc_Eqadc_FifoDisableFunc(u8EqadcIdx, u8FifoIndex);
                if ((Std_ReturnType)E_OK == FuncReturn)
                {
#if(STD_ON == ADC_HW_TRIGGER_API)
                    /* hardware triggered group */
                    if (ADC_TRIGG_SRC_HW == pGroupPtr->eTriggerSource)
                    {
                        Adc_aUnitStatus[Unit].HwNormalQueue[0] =0U;
                        /* Filled slots in the Hw queue */
                        Adc_aUnitStatus[Unit].HwNormalQueueIndex = 0U;
                        /* Disable the hardware trigger source */
                        Adc_Siu_DisableHwTrigger((uint8)u8EqadcIdx, (uint8)u8FifoIndex);
                    }
                    else
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
                    {
                        Adc_Eqadc_UpdateQueue(Unit, u8EqadcIdx, u8FifoIndex);
                    }
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
                    bCallNotification = Adc_Eqadc_CheckNotification(Group);
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
                }
                /* exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();

#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
                if((boolean)TRUE == bCallNotification)
                {
                    pGroupPtr->Notification();
                }
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
                /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
                return;
            }
            Adc_aGroupStatus[Group].ResultIndex = 0U;
        }

        if((ADC_CONV_MODE_ONESHOT == pGroupPtr->eMode) && (ADC_TRIGG_SRC_SW == pGroupPtr->eTriggerSource))
        {
            /* Disable the FIFO */
            FuncReturn = Adc_Eqadc_FifoDisableFunc(u8EqadcIdx, u8FifoIndex);
            if ((Std_ReturnType)E_OK == FuncReturn)
            {
                Adc_Eqadc_UpdateQueue(Unit, u8EqadcIdx, u8FifoIndex);
            }
        }
        else
        {
            /* Enable CFIFO Fill and RFIFO Drain Interrupts */
            /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
            REG_BIT_SET16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_RFDE_U16));
        }

        /* exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
#if(STD_ON == ADC_GRP_NOTIF_CAPABILITY)
        bCallNotification = Adc_Eqadc_CheckNotification(Group);
        if ((boolean)TRUE == bCallNotification)
        {
            /* Call group notification */
            pGroupPtr->Notification();
        }
#endif /* (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
    }
    else
    {
        /* Enable the CFIFO interrupt */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_BIT_SET16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_IDCR_CFFE_U16);
        /* exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
    }
}
#endif /* (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */

#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the Irq RFIFO Full Interrupt common function for all FIFOs
*                 on all eQADC units.
* @details        This function handles Irq RFIFO Full Interrupt common function for all FIFO.
*
* @param[in]      u8EqadcIdx    EQADC unit.
* @param[in]      u8FifoIndex  FIFO from 0 to 5.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_RFifoFullCommonFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
)
{
    VAR(boolean, AUTOMATIC) bSpurious = (boolean)FALSE;
    VAR(Adc_GroupType, AUTOMATIC) Group;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit;
    VAR(Adc_ChannelIndexType, AUTOMATIC) ChannelsInGrp;
    VAR(Std_ReturnType, AUTOMATIC) FuncReturn = (Std_ReturnType)E_OK;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) pGroupPtr = NULL_PTR;

    if(NULL_PTR != Adc_pCfgPtr)
    {
        /* enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_15();
        /* To make sure that the command is placed in the FIFO's push register to avoid any wrong result to be returned */
        if (Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIndex] != 0U)
        {
            bSpurious = (boolean)TRUE;
            /* Obtain the active group */
            Group = Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIndex];
            if(ADC_INVALID_GROUPS_ID == Group)
            {
                /* Clear the RFDF bit in FISR0 register by writing 1 to it */
                Adc_Eqadc_ClearRFifo(u8EqadcIdx, u8FifoIndex);
                /* Exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
                /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
                return;
            }
            /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
            Unit = Adc_GroupUnit(Group);
            
            /** @violates @ref Adc_Eqadc_Irq_c_REF_6 Array indexing shall be only allowed form of pointer arithmetic */
            pGroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
            ChannelsInGrp = pGroupPtr->AssignedChannelCount;
            
            FuncReturn = Adc_Eqadc_RecordResult(Unit, Group, u8EqadcIdx, u8FifoIndex);
            
            if((Std_ReturnType)E_NOT_OK == FuncReturn)
            {
                /* Increment count for messages read from RFIFO */
                Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex]++;
                if (Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex] == ChannelsInGrp)
                {
                    /* Clear variable for next use */
                    Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIndex] = 0U;
                    Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIndex] = 0U;
                    
                    /* Disable CFIFO and RFIFO interrupt */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
                    REG_BIT_CLEAR16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_RFDE_U16));
    
                    if((ADC_CONV_MODE_ONESHOT == pGroupPtr->eMode) && (ADC_TRIGG_SRC_SW == pGroupPtr->eTriggerSource))
                    {
                        /* Disable the FIFO */
                        FuncReturn = Adc_Eqadc_FifoDisableFunc(u8EqadcIdx, u8FifoIndex);
                    }
                    else /* If group is continuous or hardware trigger */
                    {
                        /* Enable CFIFO Fill and RFIFO Drain Interrupts */
                        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
                        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
                        REG_BIT_SET16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_RFDE_U16));
                    }
                }
                else
                {
                    /* Enable the CFIFO interrupt */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
                    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
                    REG_BIT_SET16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_IDCR_CFFE_U16);
                }
                /* Exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
                /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
                return;
            }
            
            Adc_Eqadc_UpdateGroupState(u8EqadcIdx, u8FifoIndex);
        }
        else
        {
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15();
        }
    }
    if ((boolean)FALSE == bSpurious)
    {
        /* Clear the RFDF bit in FISR0 register by writing 1 to it */
        Adc_Eqadc_ClearRFifo(u8EqadcIdx, u8FifoIndex);
    }
}

/**
* @brief          This function is called from the ISR to disable one of the FIFOs of an EQADC unit.
*
* @details        This function is called from the ISR to disable one of the FIFOs of an EQADC unit.
*
* @param[in]      u8EqadcIdx    eQADC unit.
* @param[in]      u8FifoIndex  FIFO from 0 to 5.
*
* @return         Std_ReturnType  Standard return type.
* @retval         E_OK: return on successful functionality execution.
* @retval         E_NOT_OK: return when the functionality is failed to execute due to production error.
*
* @api
*
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_FifoDisableFunc
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIndex
)
{
    VAR(uint32, AUTOMATIC) Timeout;
    VAR(Std_ReturnType, AUTOMATIC) TempReturn = (Std_ReturnType)E_OK;
#ifdef ADC_DMA_SUPPORTED
    VAR(Mcl_ChannelType, AUTOMATIC) DmaChannel;
#endif

    /* Disable the CFIFO */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_CFCR_MODE_DISABLED_U16);
    
    /* Reload counter */
    Timeout = ADC_TIMEOUT_COUNTER;
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    while(((REG_READ32(EQADC_CFSR_REG_ADDR32(u8EqadcIdx)) & EQADC_CFSR_FIFO_STATUS_U32(u8FifoIndex)) != EQADC_CFSR_FIFO_STATUS_IDLE_U32) && \
          (Timeout > 0UL) \
         )
    {
        /* Decrease counter */
        Timeout--;
    }
    /* Test for FIFO's Status failure. */
    if (0UL == Timeout)
    {
        TempReturn = (Std_ReturnType)E_NOT_OK;
        /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
        return(TempReturn);
    }
    /* Invalidate CFIFOi */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    REG_BIT_SET16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_CFCR_CFINV_U16);
    
    /* Disable all Interrupts and eDMA for CFIFOi */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIndex), EQADC_IDCR_CLEAR_U16);

    /* Clear RFIFO counter */
    /* Reload counter */
    Timeout = ADC_TIMEOUT_COUNTER;
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    while((((REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex))) & EQADC_FISR_RFCTR_U32) != EQADC_FISR_RFCTR_EMPTY_U32) && \
          (Timeout > (uint32)0U) \
         )
    {
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        (void)REG_READ32(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex));
        /* Decrease counter */
        Timeout--;
    }
    /* Test for FIFO's status failure. */
    if (0UL == Timeout)
    {
        TempReturn = (Std_ReturnType)E_NOT_OK;
        /** @violates @ref Adc_Eqadc_Irq_c_REF_3 Return statement before end of function. */
        return(TempReturn);
    }
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIndex), (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32));
    
#ifdef ADC_DMA_SUPPORTED
    /* Disable EQADC_AorB DMA interrupt */
    DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][u8FifoIndex*2U];
    Mcl_DmaDisableHwRequest(DmaChannel);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
    Mcl_DmaDisableNotification(DmaChannel);
#endif
    
    DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIndex*2U)+1U];
    Mcl_DmaDisableHwRequest(DmaChannel);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
    Mcl_DmaDisableNotification(DmaChannel);
#endif
#endif /* #ifdef ADC_DMA_SUPPORTED */
    
    return(TempReturn);
}
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_A Unit, RFIFO0.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult0(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_0);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_A Unit, RFIFO1.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult1(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_1);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_A Unit, RFIFO2.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult2(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_2);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_A Unit, RFIFO3.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult3(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_3);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_A Unit, RFIFO4.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult4(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_4);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_A Unit, RFIFO5.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_A_DmaPopResult5(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_5);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_B Unit, RFIFO0.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult0(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_0);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO1_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_B Unit, RFIFO1.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult1(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_1);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_B_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_B Unit, RFIFO2.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult2(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_2);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO3_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_B Unit, RFIFO3.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult3(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_3);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_B_FIFO3_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO4_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_B Unit, RFIFO4.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult4(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_4);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if (ADC_EQADC_B_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO5_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles internal ADC updates after a DMA transfer is completed.
* @details        The function is a notification called by MCL module after the transfer
*                 is completed for the EQADC_B Unit, RFIFO5.
*
* @param[in]      void.
*
* @return         void
*
* @implements     Adc_Eqadc_X_DmaPopResultN_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Eqadc_B_DmaPopResult5(void)
{
#ifdef ADC_DMA_SUPPORTED
    Adc_Eqadc_DmaInterruptCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_5);
#endif /* #ifdef ADC_DMA_SUPPORTED */
}
#endif /* #if defined(ADC_DMA_SUPPORTED) */

#if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO0 of eQADC_A is not full.
* @details        This function handles the ISR that is called when CFIFO0 of eQADC_A is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcACFifo0Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_0)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_0)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_0);
#endif /* #if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_0), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO0 has data for eQADC_A.
* @details        The function handles the ISR that is called when RFIFO0 has data for eQADC_A.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcARFifo0Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_0)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_0)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON)
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_0);
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_0);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* #if (ADC_EQADC_A_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO1 of eQADC_A is not full.
* @details        This function handles the ISR that is called when CFIFO1 of eQADC_A is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcACFifo1Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_1)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_1)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_1);
#endif /* #if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_1), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }

    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO1 has data for eQADC_A.
* @details        The function handles the ISR that is called when RFIFO1 has data for eQADC_A.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcARFifo1Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_1)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_1)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_1);
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_1);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* (ADC_EQADC_A_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO2 of eQADC_A is not full.
* @details        This function handles the ISR that is called when CFIFO2 of eQADC_A is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcACFifo2Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;

    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_2)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_2)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_2);
#endif /* #if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_2), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO2 has data for eQADC_A.
* @details        The function handles the ISR that is called when RFIFO2 has data for eQADC_A.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcARFifo2Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
  
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_2)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_2)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_2);
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_2);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* #if (ADC_EQADC_A_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO3 of eQADC_A is not full.
* @details        This function handles the ISR that is called when CFIFO3 of eQADC_A is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcACFifo3Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;

    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_3)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_3)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_3);
#endif /* #if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_3), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO3 has data for eQADC_A.
* @details        The function handles the ISR that is called when RFIFO3 has data for eQADC_A.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcARFifo3Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
  
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_3)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_3)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_3);
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_3);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* (ADC_EQADC_A_FIFO3_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO4 of eQADC_A is not full.
* @details        This function handles the ISR that is called when CFIFO4 of eQADC_A is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcACFifo4Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;

    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_4)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_4)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_4);
#endif /* #if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_4), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO4 has data for eQADC_A.
* @details        The function handles the ISR that is called when RFIFO4 has data for eQADC_A.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcARFifo4Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
  
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_4)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_4)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_4);
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_4);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* (ADC_EQADC_A_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO5 of eQADC_A is not full.
* @details        This function handles the ISR that is called when CFIFO5 of eQADC_A is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcACFifo5Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;

    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_5)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_5)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_5);
#endif /* (ADC_EQADC_A_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_5), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }

    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO5 has data for eQADC_A.
* @details        The function handles the ISR that is called when RFIFO5 has data for eQADC_A.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcARFifo5Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_A, (uint32)ADC_FIFO_5)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_A, (uint32)ADC_FIFO_5)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_5);
#endif /* #if (ADC_EQADC_A_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_A, (uint8)ADC_FIFO_5);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* #if (ADC_EQADC_A_FIFO5_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO0 of eQADC_B is not full.
* @details        This function handles the ISR that is called when CFIFO0 of eQADC_B is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBCFifo0Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;

    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_0)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_0)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_0);
#endif /* #if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_0), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO0 has data for eQADC_B.
* @details        The function handles the ISR that is called when RFIFO0 has data for eQADC_B.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBRFifo0Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_0)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_0)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_0);
#endif /* #if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_0);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* #if (ADC_EQADC_B_FIFO0_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO1_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO1 of eQADC_B is not full.
* @details        This function handles the ISR that is called when CFIFO1 of eQADC_B is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBCFifo1Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_1)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_1)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_1);
#endif /* #if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_1), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO1 has data for eQADC_B.
* @details        The function handles the ISR that is called when RFIFO1 has data for eQADC_B.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBRFifo1Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_1)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_1)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_1);
#endif /* #if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_1);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* (ADC_EQADC_B_FIFO1_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO2 of eQADC_B is not full.
* @details        This function handles the ISR that is called when CFIFO2 of eQADC_B is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBCFifo2Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_2)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_2)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_2);
#endif /* #if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_2), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO2 has data for eQADC_B.
* @details        The function handles the ISR that is called when RFIFO2 has data for eQADC_B.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBRFifo2Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_2)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_2)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_2);
#endif /* #if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_2);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* #if (ADC_EQADC_B_FIFO2_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO3_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO3 of eQADC_B is not full.
* @details        This function handles the ISR that is called when CFIFO3 of eQADC_B is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBCFifo3Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
    
    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_3)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_3)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_3);
#endif /* #if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_3), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO3 has data for eQADC_B.
* @details        The function handles the ISR that is called when RFIFO3 has data for eQADC_B.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBRFifo3Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
  
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_3)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_3)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_3);
#endif /* #if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_3);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* (ADC_EQADC_B_FIFO3_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO4_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO4 of eQADC_B is not full.
* @details        This function handles the ISR that is called when CFIFO4 of eQADC_B is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBCFifo4Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;

    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_4)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_4)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_4);
#endif /* #if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_4), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO4 has data for eQADC_B.
* @details        The function handles the ISR that is called when RFIFO4 has data for eQADC_B.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBRFifo4Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
  
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_4)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_4)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_4);
#endif /* #if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_4);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* (ADC_EQADC_B_FIFO4_ENABLED == STD_ON) */

#if (ADC_EQADC_B_FIFO5_ENABLED == STD_ON) || defined(__DOXYGEN__)
/**
* @brief          This function handles the ISR that is called when CFIFO5 of eQADC_B is not full.
* @details        This function handles the ISR that is called when CFIFO5 of eQADC_B is not full.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXCFifoNEmpty_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBCFifo5Empty)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;

    /* Get the interrupt flag status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_5)) & EQADC_FISR_CFFF_U32;
    /* Get the interrupt enable status for the corresponding DMA channel */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_5)) & EQADC_IDCR_CFFE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus))
    {
        /* Interrupt flag is cleared in Adc_Eqadc_CFifoEmptyCommonFunc */
#if (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_CFifoEmptyCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_5);
#endif /* (ADC_EQADC_B_CFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_5), EQADC_FISR_CFFF_U32);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}

/**
* @brief          This function handles the ISR that is called when RFIFO5 has data for eQADC_B.
* @details        The function handles the ISR that is called when RFIFO5 has data for eQADC_B.
*
* @param[in]      void.
*
* @return         void
*
* @implements Adc_Eqadc_EqadcXRFifoNFull_Activity
*
* @violates @ref Adc_Eqadc_Irq_c_REF_7 internal linkage vs external linkage.
*/
ISR(Adc_Eqadc_EqadcBRFifo5Full)
{
    VAR(uint32, AUTOMATIC) u32IsrStatus = 0UL;
    VAR(uint16, AUTOMATIC) u16IsrEnable = 0U;
  
    /* Get the interrupt flag status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u32IsrStatus = REG_READ32(EQADC_FISR_REG_ADDR32(ADC_EQADC_B, (uint32)ADC_FIFO_5)) & EQADC_FISR_RFDF_U32;
    /* Get the interrupt enable status */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_Irq_c_REF_10 A cast should not be performed between a pointer type and an integral type. */
    u16IsrEnable = REG_READ16(EQADC_IDCR_REG_ADDR16(ADC_EQADC_B, (uint32)ADC_FIFO_5)) & EQADC_IDCR_RFDE_U16;
    
    if ((0U != u16IsrEnable) && (0UL != u32IsrStatus) )
    {
        /* Interrupt flag is cleared in Adc_Eqadc_RFifoFullCommonFunc */
#if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) || defined(__DOXYGEN__)
        Adc_Eqadc_RFifoFullCommonFunc((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_5);
#endif /* #if (ADC_EQADC_B_RFIFO_ENABLED == STD_ON) */
    }
    else if (0UL != u32IsrStatus)
    {
        /* Clear the Interrupt flag */
        /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
        Adc_Eqadc_ClearRFifo((uint8)ADC_EQADC_B, (uint8)ADC_FIFO_5);
    }
    else
    {
        /* do nothing for MISRA */
    }
    
    /** @violates @ref Adc_Eqadc_Irq_c_REF_4 cast from unsigned int to pointer. */
    EXIT_INTERRUPT();
}
#endif /* #if (ADC_EQADC_B_FIFO5_ENABLED == STD_ON) */

#define ADC_STOP_SEC_CODE
/**
 * @violates @ref Adc_Eqadc_Irq_c_REF_1 Only preprocessor statements and comments before "#include"
 * @violates @ref Adc_Eqadc_Irq_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
