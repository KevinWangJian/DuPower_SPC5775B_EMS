/**
*   @file    Adc_Eqadc.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - low level driver source file.
*   @details This is the low level driver source file,mainly implemented for the ADCDig hardware IP.
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
* @section Adc_Eqadc_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
* This is an Autosar memory management requirement.
*
* @section Adc_Eqadc_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Adc_Eqadc_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned int to pointer. This macro compute the
* address of any register by using the hardware offset of the controller. The address calculated as an
* unsigned int is passed to a macro for initializing the pointer with that address.
*
* @section Adc_Eqadc_c_REF_4
* Violates MISRA 2004 Required Rule 14.7, return statement before end of function. The return
* statement are used to simplify the code structure and easier readability.
*
* @section Adc_Eqadc_c_REF_5
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only allowed form of pointer 
* arithmetic but used due to the code complexity.
*
* @section Adc_Eqadc_c_REF_6
* Violates MISRA 2004 Required Rule 8.10,
* All declarations and definitions of objects or functions at file scope 
* shall have internal linkage unless external linkage is required.
*
 * @section Adc_Eqadc_c_REF_7
 * Violates MISRA 2004 Required Rule 8.7,
 * Objects shall be defined at block scope 
 * if they are only accessed from within a single function.
 *
* @section Adc_Eqadc_c_REF_8
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 
* 31 character significance and case sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Eqadc_c_REF_9
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and
* functions shall not be reused. Symbols defined are not library macros or objects.
*
* @section Adc_Eqadc_c_REF_11
* Violates MISRA 2004 Required Rule 10.1, The value of an expression of integer type shall not be 
* implicitly converted to a different underlying type
*
* @section Adc_Eqadc_c_REF_12
* Violates MISRA 2004 Advisory Rule 11.3,
* A cast should not be performed between a pointer type and an integral type.
*
* @section Adc_Eqadc_c_REF_13
* Violates MISRA 2004 Required Rule 12.4,
* The right-hand operand of a logical && or || operator shall not contain side effects.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers shall not more than 31 characters
* Violation is needed because of Autosar restrictions for naming File version check macros.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this Unit
==================================================================================================*/
#include "Adc_Ipw.h"
#define USER_MODE_REG_PROT_ENABLED                (ADC_USER_MODE_REG_PROT_ENABLED)
#include "SilRegMacros.h"
#include "Adc_Reg_eSys_Eqadc.h"
#include "Adc_Eqadc_CfgEx.h"
#include "SchM_Adc.h"
#include "Adc_Eqadc.h"
#include "Adc_Siu.h"

#ifdef ADC_DMA_SUPPORTED
    #include "CDD_Mcl.h"
#endif

#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
    #include "Dem.h"
#endif
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_AR_VENDOR_ID_EQADC_C                 43
/** @violates @ref Adc_Eqadc_c_REF_8 MISRA-C:2004 Rule 1.4: Identifier clash. */
#define ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C     4
/** @violates @ref Adc_Eqadc_c_REF_8 MISRA-C:2004 Rule 1.4: Identifier clash. */
#define ADC_AR_RELEASE_MINOR_VERSION_EQADC_C     0
/** @violates @ref Adc_Eqadc_c_REF_8 MISRA-C:2004 Rule 1.4: Identifier clash. */
#define ADC_AR_RELEASE_REVISION_VERSION_EQADC_C  3
#define ADC_SW_MAJOR_VERSION_EQADC_C             1
#define ADC_SW_MINOR_VERSION_EQADC_C             0
#define ADC_SW_PATCH_VERSION_EQADC_C             1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC IPW header file are from the same vendor */
#if (ADC_AR_VENDOR_ID_EQADC_C != ADC_VENDOR_ID_IPW_H)
    #error "Adc_Eqadc.c and Adc_Ipw.h have different vendor ids"
#endif

/* Check if source file and ADC IPW header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_AR_RELEASE_REVISION_VERSION_EQADC_C != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AutoSar Version Numbers of Adc_Eqadc.c and Adc_Ipw.h are different"
#endif

/* Check if source file and ADC IPW header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_EQADC_C != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_SW_MINOR_VERSION_EQADC_C != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_SW_PATCH_VERSION_EQADC_C != ADC_SW_PATCH_VERSION_IPW_H) \
    )
    #error "Software Version Numbers of Adc_Eqadc.c and Adc_Ipw.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Eqadc header file are of the same vendor */
#if (ADC_AR_VENDOR_ID_EQADC_C != ADC_VENDOR_ID_REG)
    #error "Adc_Eqadc.c and Adc_Reg_eSys_Eqadc.h have different vendor ids"
#endif

/* Check if source file and Adc_Reg_eSys_Eqadc header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != ADC_AR_RELEASE_MAJOR_VERSION_REG) || \
     (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != ADC_AR_RELEASE_MINOR_VERSION_REG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_EQADC_C != ADC_AR_RELEASE_REVISION_VERSION_REG) \
    )
    #error "AutoSar Version Numbers of Adc_Eqadc.c and Adc_Reg_eSys_Eqadc.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Eqadc header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_EQADC_C != ADC_SW_MAJOR_VERSION_REG) || \
     (ADC_SW_MINOR_VERSION_EQADC_C != ADC_SW_MINOR_VERSION_REG) || \
     (ADC_SW_PATCH_VERSION_EQADC_C != ADC_SW_PATCH_VERSION_REG) \
    )
    #error "Software Version Numbers of Adc_Eqadc.c and Adc_Reg_eSys_Eqadc.h are different"
#endif

/* Check if source file and Adc_Eqadc_CfgEx header file are of the same vendor */
#if (ADC_AR_VENDOR_ID_EQADC_C != ADC_VENDOR_ID_EQADC_CFGEX)
    #error "Adc_Eqadc.c and Adc_Eqadc_CfgEx.h have different vendor ids"
#endif

/* Check if source file and Adc_Eqadc_CfgEx header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != ADC_AR_RELEASE_MAJOR_VERSION_EQADC_CFGEX) || \
     (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != ADC_AR_RELEASE_MINOR_VERSION_EQADC_CFGEX) || \
     (ADC_AR_RELEASE_REVISION_VERSION_EQADC_C != ADC_AR_RELEASE_REVISION_VERSION_EQADC_CFGEX) \
    )
    #error "AutoSar Version Numbers of Adc_Eqadc.c and Adc_Eqadc_CfgEx.h are different"
#endif

/* Check if source file and Adc_Eqadc_CfgEx header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_EQADC_C != ADC_SW_MAJOR_VERSION_EQADC_CFGEX) || \
     (ADC_SW_MINOR_VERSION_EQADC_C != ADC_SW_MINOR_VERSION_EQADC_CFGEX) || \
     (ADC_SW_PATCH_VERSION_EQADC_C != ADC_SW_PATCH_VERSION_EQADC_CFGEX) \
    )
    #error "Software Version Numbers of Adc_Eqadc.c and Adc_Eqadc_CfgEx.h are different"
#endif

/* Check if source file and Adc_Eqadc header file are from the same vendor */
#if (ADC_AR_VENDOR_ID_EQADC_C != ADC_VENDOR_ID_EQADC)
    #error "Adc_Eqadc.c and Adc_Eqadc.h have different vendor ids"
#endif

/* Check if source file and Adc_Eqadc header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != ADC_AR_RELEASE_MAJOR_VERSION_EQADC) || \
     (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != ADC_AR_RELEASE_MINOR_VERSION_EQADC) || \
     (ADC_AR_RELEASE_REVISION_VERSION_EQADC_C != ADC_AR_RELEASE_REVISION_VERSION_EQADC) \
    )
    #error "AutoSar Version Numbers of Adc_Eqadc.c and Adc_Eqadc.h are different"
#endif

/* Check if source file and Adc_Eqadc header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_EQADC_C != ADC_SW_MAJOR_VERSION_EQADC) || \
     (ADC_SW_MINOR_VERSION_EQADC_C != ADC_SW_MINOR_VERSION_EQADC) || \
     (ADC_SW_PATCH_VERSION_EQADC_C != ADC_SW_PATCH_VERSION_EQADC) \
    )
    #error "Software Version Numbers of Adc_Eqadc.c and Adc_Eqadc.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#ifdef ADC_DMA_SUPPORTED
/* Check if source file and DMA header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != MCL_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Adc_Eqadc.c and CDD_Mcl.h are different"
#endif
#endif
#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
 /* Check if source file and Dem header file are of the same version */
 #if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != DEM_AR_RELEASE_MINOR_VERSION) \
     )
    #error "AutoSar Version Numbers of Adc_Eqadc.c and Dem.h are different"
 #endif
#endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
  /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Eqadc.c and Mcal.h are different"
 #endif 
   /* Check if source file and SilREgMacros header file are of the same AutoSar version */
 #if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_AR_RELEASE_MINOR_VERSION_EQADC_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Eqadc.c and SilRegMacros.h are different"
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
#define ADC_START_SEC_CONST_32
/**
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"
/**
* @brief base address array for EQADC
*
* @violates @ref Adc_Eqadc_c_REF_9 Reuse of C90 identifier pattern
*/
CONST(uint32, ADC_CONST) EQADC_BASE_ADDR[ADC_EQADC_MAX_U8] =
{
#ifdef EQADC0_BASEADDR
    EQADC0_BASEADDR,
#endif
#ifdef EQADC1_BASEADDR
    EQADC1_BASEADDR
#endif
};

#define ADC_STOP_SEC_CONST_32
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"

#ifdef ADC_DMA_SUPPORTED
#define ADC_START_SEC_VAR_NO_INIT_32
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"

/**
* @brief          DMA Common queue
*/
static VAR(uint32, ADC_VAR) Adc_Eqadc_u32DmaCmdQueue[ADC_MAX_HW_UNITS][ADC_MAX_GROUP_CHANNELS];

#define ADC_STOP_SEC_VAR_NO_INIT_32
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/** @violates @ref Adc_Eqadc_c_REF_8 The used compilers use more than 31 chars for identifiers. */
#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/**
 * @violates @ref Adc_Eqadc_c_REF_1 MemMap.h is included after each section define in order to set the current memory section as defined by AUTOSAR
 * @violates @ref Adc_Eqadc_c_REF_2 This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
 */
#include "MemMap.h"

/**
 * @brief          Internal buffer used by DMA to transfer blocks with gaps.
 * @violates @ref Adc_Eqadc_c_REF_6 internal This warning appears when defining functions or objects that will be used by the upper layers.
 * @violates @ref Adc_Eqadc_c_REF_7 Objects shall be defined at block scope
 */
VAR(Adc_ValueGroupType,ADC_VAR) Adc_Eqadc_DmaInternalResultBuffer[ADC_MAX_HW_UNITS];

/** @violates @ref Adc_Eqadc_c_REF_8 The used compilers use more than 31 chars for identifiers. */
#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/**
 * @violates @ref Adc_Eqadc_c_REF_1 MemMap.h is included after each section define in order to set the current memory section as defined by AUTOSAR
 * @violates @ref Adc_Eqadc_c_REF_2 This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
 */
#include "MemMap.h"
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
#endif /* #ifdef ADC_DMA_SUPPORTED */

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"
/**
* @brief          Number of messages transferred to CFIFO.
*/
VAR(Adc_ChannelIndexType, ADC_VAR) Adc_Eqadc_CFifoChannelCount[ADC_EQADC_MAX_U8][ADC_EQADC_MAX_FIFO_U8];

/**
* @brief          Number of messages read from RFIFO
*/
VAR(Adc_ChannelIndexType, ADC_VAR) Adc_Eqadc_RFifoChannelCount[ADC_EQADC_MAX_U8][ADC_EQADC_MAX_FIFO_U8];

/**
* @brief          EQADCA/EQADCB Fifo ongoing group array
*/
VAR(Adc_GroupType, ADC_VAR) Adc_Eqadc_FifoOngoingGroup[ADC_EQADC_MAX_U8][ADC_EQADC_MAX_FIFO_U8];

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"

#define ADC_START_SEC_CONST_8
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"
/**
* @brief          EQADCA/EQADCB Fifo array
* @violates @ref Adc_Eqadc_c_REF_7 Objects shall be defined at block scope
*/
static CONST(uint8, ADC_CONST) Adc_Eqadc_au8FifoArray[ADC_EQADC_MAX_U8][ADC_EQADC_MAX_FIFO_U8] =
{
    {
        (uint8)ADC_EQADC_A_FIFO0_ENABLED,
        (uint8)ADC_EQADC_A_FIFO1_ENABLED,
        (uint8)ADC_EQADC_A_FIFO2_ENABLED,
        (uint8)ADC_EQADC_A_FIFO3_ENABLED,
        (uint8)ADC_EQADC_A_FIFO4_ENABLED,
        (uint8)ADC_EQADC_A_FIFO5_ENABLED
    },
    {
        (uint8)ADC_EQADC_B_FIFO0_ENABLED,
        (uint8)ADC_EQADC_B_FIFO1_ENABLED,
        (uint8)ADC_EQADC_B_FIFO2_ENABLED,
        (uint8)ADC_EQADC_B_FIFO3_ENABLED,
        (uint8)ADC_EQADC_B_FIFO4_ENABLED,
        (uint8)ADC_EQADC_B_FIFO5_ENABLED
    }
};

#define ADC_STOP_SEC_CONST_8
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define ADC_START_SEC_CODE
/**
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"

#ifdef ADC_DMA_SUPPORTED
/**
* @brief          Copy Queue Data to DMA command buffer
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_CopyQueueData2DmaCmdBuffer
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIdx
);

LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_StartDmaOperation
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIdx
);
#endif /* #ifdef ADC_DMA_SUPPORTED */

#if (STD_ON == ADC_CALIBRATION)
/**
* @brief          Adc_Eqadc_CalculateCalConst()  This routine calculates the EQADC gain and offset calibration constants
*                 (GCC and OCC) from the conversion results of 25%Vref and 75%Vref.
*                 The calibration constants are returned in a format defined by the ADC0/1
*                 Gain and Offset Calibration Constant Registers (ADC0/1_GCCR and
*                 ADC0/1_OCCR).
*
* @param[in]      u16RawResult25  - conversion result for 25%Vref.
* @param[in]      u16RawResult75  - conversion result for 75%Vref.
* @param[out]     pGcc - pointer to variable where the gain calibration.
* param[out]      pOcc - pointer to variable where offset calibration constant is returned.
*
* @return         void.
*
*/
LOCAL_INLINE FUNC (void, ADC_CODE) Adc_Eqadc_CalculateCalConst
(
    VAR(uint16, AUTOMATIC) u16RawResult25,
    VAR(uint16, AUTOMATIC) u16RawResult75,
    P2VAR(uint16, AUTOMATIC, ADC_APPL_DATA) pGcc,
    P2VAR(sint16, AUTOMATIC, ADC_APPL_DATA) pOcc
);
#endif /* #if (STD_ON == ADC_CALIBRATION) || defined(__DOXYGEN__) */

LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_DisableFifo
(
    VAR(uint8, AUTOMATIC) u8Eqadc,
    VAR(uint8, AUTOMATIC) u8Fifo
);

LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_DemReportStatus
(
    VAR(uint32, AUTOMATIC) u32Timeout,
    VAR(Std_ReturnType, AUTOMATIC) RetFlag
);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/**
* @brief          This function disables the CFIFO depends on the hardware Unit and fifo Index.
* @details        This function disables the CFIFO depends on the hardware Unit and fifo Index.
*
* @param[in]      u8Eqadc   - eQADC number.
* @param[in]      u8Fifo - the fifo number.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_DisableFifo
(
    VAR(uint8, AUTOMATIC) u8Eqadc,
    VAR(uint8, AUTOMATIC) u8Fifo
)
{
    VAR(uint32, AUTOMATIC) Timeout;
    
    /* Disable CFIFOi */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8Eqadc, (uint32)u8Fifo), EQADC_CFCR_MODE_DISABLED_U16);
    /* Reload counter */
    Timeout = ADC_TIMEOUT_COUNTER;
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    while(((REG_READ32(EQADC_CFSR_REG_ADDR32(u8Eqadc)) & EQADC_CFSR_FIFO_STATUS_U32(u8Fifo)) != EQADC_CFSR_FIFO_STATUS_IDLE_U32) && \
          (Timeout > 0UL) \
         )
    {
        /* Decrease counter */
        Timeout--;
    }
    /* Test for FIFO's Status failure. */
    if (0UL == Timeout)
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
        return (Std_ReturnType)E_NOT_OK;
    }
    /* Invalidate CFIFOi */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_BIT_SET16(EQADC_CFCR_REG_ADDR16(u8Eqadc, (uint32)u8Fifo), EQADC_CFCR_CFINV_U16);
    
    /* Disable all Interrupts and eDMA for CFIFOi */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8Eqadc, (uint32)u8Fifo), EQADC_IDCR_CLEAR_U16);

    /* Clear all Interrupts and eDMA flags for CFIFOi */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE32(EQADC_FISR_REG_ADDR32(u8Eqadc, (uint32)u8Fifo), (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32));
    
    /* Clear RFIFO */
    Adc_Eqadc_ClearRFifo(u8Eqadc, u8Fifo);
    
    return (Std_ReturnType)E_OK;
}

#if (STD_ON == ADC_CALIBRATION)
/**
* @brief          Adc_Eqadc_CalculateCalConst(). This routine calculates the EQADC gain and offset calibration constants
*                 (GCC and OCC) from the conversion results of 25%Vref and 75%Vref.
*                 The calibration constants are returned in a format defined by the ADC0/1
*                 Gain and Offset Calibration Constant Registers (ADC0/1_GCCR and
*                 ADC0/1_OCCR).
*
* @param[in]      u16RawResult25  - conversion result for 25%Vref.
* @param[in]      u16RawResult75  - conversion result for 75%Vref.
* @param[out]     pGcc - pointer to variable where the gain calibration.
* param[out]      pOcc - pointer to variable where offset calibration constant is returned.
*
* @return         void.
*
*/
LOCAL_INLINE FUNC (void, ADC_CODE) Adc_Eqadc_CalculateCalConst
(
    VAR(uint16, AUTOMATIC) u16RawResult25,
    VAR(uint16, AUTOMATIC) u16RawResult75,
    P2VAR(uint16, AUTOMATIC, ADC_APPL_DATA) pGcc,
    P2VAR(sint16, AUTOMATIC, ADC_APPL_DATA) pOcc
)
{
    VAR(uint32, AUTOMATIC) u32CalGcc;
    VAR(uint32, AUTOMATIC) u32CalOcc;
    
    u32CalGcc = (uint32)((uint32)ADC_CAL_GCC_U8 / (uint32)((uint32)u16RawResult75 - (uint32)u16RawResult25));
    *pGcc = (uint16)u32CalGcc;
    u32CalOcc = EQADC_ADC_IDEAL_RES75_U32 - ((u32CalGcc * (uint32)u16RawResult75) >> 14U);
    *pOcc = (sint16)u32CalOcc;
}
#endif /* ADC_CALIBRATION */

#ifdef ADC_DMA_SUPPORTED
/**
* @brief          This function  extracts the conversion commands from the configure structure and copies it the RAM Buffers.
* @details        This function  extracts the conversion commands from the configure structure and copies it the RAM Buffers.
*                 This function should be called with the ADC Unit on idle or busy.
*
* @param[in]      Unit            The used hw Unit.
* @param[in]      u8EqadcIdx      The used EQADC Unit.
* @param[in]      u8FifoIdx       The used FIFO number.
*
* @return         void
*
*/
LOCAL_INLINE FUNC (void, ADC_CODE) Adc_Eqadc_CopyQueueData2DmaCmdBuffer
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIdx
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group;
    VAR(Adc_ChannelIndexType, AUTOMATIC) ChCount;
    VAR(Adc_ChannelIndexType, AUTOMATIC) Index;
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(uint32, AUTOMATIC) u32FifoCmdmsg;
    VAR(uint32, AUTOMATIC) u32EndOfQueue = 0U;

    Group = Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx];
    if(ADC_INVALID_GROUPS_ID == Group)
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
        return;
    }
    
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    ChCount = Adc_pCfgPtr->pGroups[Group].AssignedChannelCount;

    u32FifoCmdmsg = (EQADC_RESULT_FIFO_OFFSET_U32*u8FifoIdx);
    for(Index = 0U;  Index < ChCount; Index++)
    {
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
        ChIndex = Adc_GroupChannelIndex(Group, Index);
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
        if ((Index == (ChCount-1U)) && (ADC_CONV_MODE_ONESHOT == Adc_pCfgPtr->pGroups[Group].eMode))
        {
            /* Last ADC channel, hence set the EOQ Flag */
            u32EndOfQueue = EQADC_ADC_WRITE_CONFIG_EOQ_U32;
        }
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
        Adc_Eqadc_u32DmaCmdQueue[Unit][Index] = (Adc_pCfgPtr->pChannels[Unit][ChIndex].u32Msg | u32FifoCmdmsg | u32EndOfQueue);
    }
}

/**
* @brief          This function programs the DMA transfers involved in the ADC conversion process.
* @details        This function should be called with the ADC Unit on standby (no ADC interruptions
*                 allowed because its code is not protected by critical regions) - no conversions must
*                 be running.
*
* @param[in]      Unit            The used hw Unit.
* @param[in]      u8EqadcIdx      The used EQADC Unit.
* @param[in]      u8FifoIdx       The used FIFO number.
*
* @return         void
*
*/
LOCAL_INLINE FUNC(void, ADC_CODE) Adc_Eqadc_StartDmaOperation
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIdx
)
{
    VAR(Adc_GroupType, AUTOMATIC) Group;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) GroupPtr;
    VAR(Adc_ChannelIndexType, AUTOMATIC) ChCount;
    VAR(uint32, AUTOMATIC) u32SlastCommandValue;
    VAR(uint32, AUTOMATIC) u32DlastDataValue = 0U;
    VAR(uint32, AUTOMATIC) u32DestOffset;
    VAR(uint32, AUTOMATIC) u32DesAddr;
    P2VAR(Mcl_DmaTcdType, AUTOMATIC, ADC_APPL_DATA) pTcdAddress;
    static VAR(Mcl_DmaTcdAttributesType, AUTOMATIC) DmaTcdConfig;
    VAR(Mcl_ChannelType, AUTOMATIC) DmaChannel;
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

    /* Get the Group ID of the current active group */
    Group = Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx];
    if(ADC_INVALID_GROUPS_ID == Group)
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
        return;
    }
    
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    GroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
    ChCount = GroupPtr->AssignedChannelCount;

    if ((uint8)STD_ON == Adc_pCfgPtr->Misc.au8Adc_HwUnit[Unit])
    {
        /* Disable DMA command channel */
        DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIdx << 1U)];
        Mcl_DmaDisableHwRequest(DmaChannel);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
        Mcl_DmaDisableNotification(DmaChannel);
#endif
        /* Disable DMA result channel */
        DmaChannel = (Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIdx << 1U)+1U];
        Mcl_DmaDisableHwRequest(DmaChannel);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
        Mcl_DmaDisableNotification(DmaChannel);
#endif
    }

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    ChIndex = Adc_GroupChannelIndex(Group, 0U);
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    if((boolean)TRUE == Adc_ChannelsLimitCheckingCfg[Unit][ChIndex].bChannelLimitCheck)
    {
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        u32DesAddr = (uint32)&Adc_Eqadc_DmaInternalResultBuffer[Unit];
        u32DestOffset  = 0UL;
    }
    else
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
    {
        /* update result address of channel 0 and destination offset to support format of streaming buffer */
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        u32DesAddr = (uint32)(GroupPtr->pResultsBufferPtr[Group] + Adc_aGroupStatus[Group].ResultIndex);
        u32DestOffset = (uint32)(sizeof(Adc_ValueGroupType) * (uint32)GroupPtr->NumSamples);
        if(ADC_ACCESS_MODE_SINGLE == GroupPtr->eAccessMode)
        {
            u32DlastDataValue = (uint32)ChCount << 1U;
        }
        else
        {
            u32DlastDataValue = (((uint32)ChCount*(uint32)GroupPtr->NumSamples) - 1UL) << 1U;
        }
    }
    u32SlastCommandValue = (uint32)((uint32)ChCount << 2U);
    
    if((uint8)STD_ON == Adc_pCfgPtr->Misc.au8Adc_HwUnit[Unit])
    {
        /* Configure for transfer Fifo commands */
        DmaChannel = Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIdx << 1U)];
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        DmaTcdConfig.u32saddr = (uint32)(&Adc_Eqadc_u32DmaCmdQueue[Unit][0]);
        DmaTcdConfig.u32ssize = (uint32)DMA_SIZE_4BYTES;
        DmaTcdConfig.u32dsize = (uint32)DMA_SIZE_4BYTES;
        DmaTcdConfig.u32soff = (uint32)4;
        DmaTcdConfig.u32num_bytes = (uint32)4;
        DmaTcdConfig.u32daddr = (uint32)(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
        DmaTcdConfig.u32iter = (uint32)ChCount;
        DmaTcdConfig.u32doff = (uint32)0;
        DmaTcdConfig.u32smod = (uint32)0;
        DmaTcdConfig.u32dmod = (uint32)0;
    
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        pTcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress((Mcl_ChannelType)DmaChannel);
        Mcl_DmaConfigTcd(pTcdAddress, &DmaTcdConfig);
        Mcl_DmaTcdSetFlags(pTcdAddress, (uint8)DMA_TCD_DISABLE_REQ_U32);
        Mcl_DmaTcdSetSlast(pTcdAddress, -(sint32)u32SlastCommandValue);
        /* Start the DMA channel */
        Mcl_DmaEnableHwRequest(DmaChannel);
    
        /* Configure for transfer Fifo results */
        DmaChannel = Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(uint8)(u8FifoIdx << 1U)+1U];
        DmaTcdConfig.u32saddr = (uint32)(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)+2U);
        DmaTcdConfig.u32ssize = (uint32)DMA_SIZE_2BYTES;
        DmaTcdConfig.u32dsize = (uint32)DMA_SIZE_2BYTES;
        DmaTcdConfig.u32soff = (uint32)0;
        DmaTcdConfig.u32num_bytes = (uint32)2;
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer */
        DmaTcdConfig.u32daddr = u32DesAddr;
        DmaTcdConfig.u32iter = (uint32)ChCount;
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        DmaTcdConfig.u32doff = (uint32)u32DestOffset;
        DmaTcdConfig.u32smod = (uint32)0;
        DmaTcdConfig.u32dmod = (uint32)0;
    
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
       pTcdAddress = (Mcl_DmaTcdType *)Mcl_DmaGetChannelTcdAddress((Mcl_ChannelType)DmaChannel);
        Mcl_DmaConfigTcd(pTcdAddress, &DmaTcdConfig);
        Mcl_DmaTcdSetFlags(pTcdAddress, (uint8)(DMA_TCD_DISABLE_REQ_U32 | DMA_TCD_INT_MAJOR_U32));
        Mcl_DmaTcdSetDlast(pTcdAddress, -(sint32)u32DlastDataValue);
        /* Start the DMA channel */
        Mcl_DmaEnableHwRequest(DmaChannel);
    }
}
#endif /* #if defined(ADC_DMA_SUPPORTED) || defined(__DOXYGEN__) */

LOCAL_INLINE FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_DemReportStatus
(
    VAR(uint32, AUTOMATIC) u32Timeout,
    VAR(Std_ReturnType, AUTOMATIC) RetFlag
)
{
    VAR(Std_ReturnType, AUTOMATIC) RetVal = (Std_ReturnType)E_OK;
    
    if((0UL == u32Timeout) || ((Std_ReturnType)E_NOT_OK == RetFlag))
    {
#if (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if ((uint32)STD_ON == Adc_E_TimeoutCfg.state)
        {
            /* Report production error and Return from function.  */
            Dem_ReportErrorStatus((Dem_EventIdType)Adc_E_TimeoutCfg.id, DEM_EVENT_STATUS_FAILED);
        }
#endif /* (ADC_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */
        RetVal = (Std_ReturnType)E_NOT_OK;
    }
    return RetVal;
}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief          This function clear results FIFO.
* @details        This function clear results FIFO.
*
* @param[in]      u8EqadcIdx     EQADC Index (EQADCA/EQADCB).
* @param[in]      u8FifoIdx      Fifo Index (0-5).
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Eqadc_ClearRFifo
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIdx
)
{
    VAR(uint8, AUTOMATIC) u8Index;

    /* To clear RFDF flag */
    for(u8Index = 0U; u8Index < EQADC_FIFO_MAX_DEPTH_U8; u8Index++)
    {
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        (void)REG_READ32(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
    }
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_RFDF_U32);
}

/**
* @brief          This function initializes the ADC hardware module, and the ADC driver.
* @details        This function initializes the ADC hardware module, and the ADC driver.
*
* @param[in]      CfgPtr      Configuration data pointer.
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Eqadc_Init
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
)
{
    VAR(uint8, AUTOMATIC) u8EqadcIdx;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint32, AUTOMATIC) u32CBuffer;
    VAR(uint32, AUTOMATIC) u32Timeout;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit;
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex;
    VAR(Std_ReturnType, AUTOMATIC) RetVal;
    
    /* Enter critical region to avoid ISRs during register reset */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
    
    for(u8EqadcIdx = 0U; u8EqadcIdx < ADC_EQADC_MAX_U8; u8EqadcIdx++)
    {
        for(u8FifoIdx = 0U; u8FifoIdx < ADC_EQADC_MAX_FIFO_U8; u8FifoIdx++)
        {
            Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx] = ADC_INVALID_GROUPS_ID;

            if((uint8)STD_ON == Adc_Eqadc_au8FifoArray[u8EqadcIdx][u8FifoIdx])
            {
                RetVal = Adc_Eqadc_DisableFifo(u8EqadcIdx, u8FifoIdx);
                /* Exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();
                /* Test for FIFO's status failure. */
                if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(1UL, RetVal))
                {
                    /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                    return;
                }
                /* Enter critical region */
                SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
                
                /* To clear RFDF flag */
                Adc_Eqadc_ClearRFifo(u8EqadcIdx, u8FifoIdx);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32  | EQADC_FISR_RFDF_U32    | EQADC_FISR_CFUF_U32 | \
                                                                                  EQADC_FISR_NCF_U32   | EQADC_FISR_TORF_U32    | EQADC_FISR_PF_U32   | \
                                                                                  EQADC_FISR_SSS_U32   | EQADC_FISR_CFFF_U32    | EQADC_FISR_RFOF_U32 | \
                                                                                  EQADC_FISR_CFCTR_U32 | EQADC_FISR_TNXTPTR_U32 | EQADC_FISR_RFCTR_U32  \
                           );
            }
        }
#if (STD_ON == ADC_HW_TRIGGER_API)
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
       REG_WRITE32(EQADC_ETDFR_REG_ADDR32(u8EqadcIdx), pCfgPtr->Misc.au8ETriggerDigitalFilter[u8EqadcIdx]);
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */
    }
    
    u8EqadcIdx = (uint8)ADC_EQADC_A;
    for(Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
    {
        if(Unit == 2U)
        {
            u8EqadcIdx = (uint8)ADC_EQADC_B;
        }

        /* If HW Unit is configured to use, enable it and update the calibration constants */
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            /* Get the index of hardware Unit*/
            HwIndex = Adc_pCfgPtr->Misc.aHwLogicalId[Unit];
            /* If ADC0 of EQADC-A/B  */
            if(0U == (Unit % 2U))
            {
                /* command buffer to be used is ZERO */
                u32CBuffer = EQADC_ADC_CONV_COM_BN0_U32;
            }
            else /* ADC1 of EQADC-A/B */
            {
                u32CBuffer = EQADC_ADC_CONV_COM_BN1_U32;
            }
            
            /* Get the 1st fifo that is configured for the hardware which is being used for the ADC calibration */
            u8FifoIdx = pCfgPtr->Misc.au8FirstFifo[Unit];
            
            /* Enable the ADC Unit 0 and set the Prescaler using CFIFOi, where i is configured fifo */
            /* ADCn_EN=1, ADCn_EMUX=0, ADCn_CLK_PS=ADC[HwIndex].Prescale */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | EQADC_ADC_WRITE_CONFIG_EOQ_U32 | (uint32)EQADC_ADC_CR_U8) | \
                        ((uint32)pCfgPtr->pAdc[HwIndex].u32AdcControlConfig << 8U) \
                       );

            /* Set SW SS mode and Start the Queue for the CFIFOi */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));

            /* Wait for EOQ flag to be set */
            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }
            /* Enter critical region */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
            
            /* Disable the Queue and Clear the EOQ flag */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);

            /* Configure the Alternate register ADC_ACR1 is used for 10BIT  and EQADC_ADC_ACR2_U8 is used for the 8BIT ADC channel's resolution for eQADC-A and eQADC_B  */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | EQADC_ADC_WRITE_CONFIG_EOQ_U32 | \
                        ((uint32)ADC_ACR1_RESSEL_10BIT_U8 << 8U) | (uint32)EQADC_ADC_ACR1_U8) \
                       );
            /* Set SW SS mode and Start the Queue for the CFIFOi */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
            
            /* Wait for EOQ flag to be set */
            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }
            /* Enter critical region */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
            
            /* Disable the Queue and Clear the EOQ flag */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | EQADC_ADC_WRITE_CONFIG_EOQ_U32 | \
                        ((uint32)ADC_ACR2_RESSEL_8BIT_U8 << 8U) | (uint32)EQADC_ADC_ACR2_U8) \
                       );
            /* Set SW SS mode and Start the Queue for the CFIFO0 */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
            
            /* Wait for EOQ flag to be set */
            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }
            /* Enter critical region */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03();
            /* Disable the Queue and Clear the EOQ flag */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);
        }
    }
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03();
}

#if (STD_ON == ADC_DEINIT_API)
/**
* @brief          This function de-initializes the ADC driver, and the ADC hardware.
* @details        This function de-initializes the ADC driver, and ensures that the ADC hardware
*                 will be in the power on after reset state.
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Eqadc_DeInit(void)
{
    VAR(uint8, AUTOMATIC) u8EqadcIdx;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint32, AUTOMATIC) u32Timeout;
    VAR(uint32, AUTOMATIC) u32CBuffer;
    VAR(Std_ReturnType, AUTOMATIC) RetVal;
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    VAR(Adc_GroupType,AUTOMATIC) GroupIdx = 0U;
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

    /* enter critical region to avoid ISRs during register reset */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_06();

    for(u8EqadcIdx = 0U; u8EqadcIdx < ADC_EQADC_MAX_U8; u8EqadcIdx++)
    {
        for(u8FifoIdx = 0U; u8FifoIdx < ADC_EQADC_MAX_FIFO_U8; u8FifoIdx++)
        {
            Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx] = ADC_INVALID_GROUPS_ID;
            
            if(Adc_Eqadc_au8FifoArray[u8EqadcIdx][u8FifoIdx] == (uint8)STD_ON)
            {
                RetVal = Adc_Eqadc_DisableFifo(u8EqadcIdx, u8FifoIdx);
                /* Exit critical region */
                SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_06();
                if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(1UL, RetVal))
                {
                    /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                    return;
                }
                /* Enter critical region */
                SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_06();
                /* To clear RFDF flag */
                Adc_Eqadc_ClearRFifo(u8EqadcIdx, u8FifoIdx);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32));
            }
        }
    }

    u8EqadcIdx = (uint8)ADC_EQADC_A;
    for(Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
    {
        if(2U == Unit)
        {
            u8EqadcIdx = (uint8)ADC_EQADC_B;
        }

        /* If HW Unit is configured to use, enable it and update the calibration constants */
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            /* If ADC0 of EQADC-A/B  */
            if(0U == (Unit % 2U))
            {
                /* command buffer to be used is ZERO */
                u32CBuffer = EQADC_ADC_CONV_COM_BN0_U32;
            }
            else /* ADC1 of EQADC-A/B */
            {
                u32CBuffer = EQADC_ADC_CONV_COM_BN1_U32;
            }
            
            /* Get the 1st fifo that is configured for in the hardware*/
            u8FifoIdx = Adc_pCfgPtr->Misc.au8FirstFifo[Unit];
            
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_MCR_REG_ADDR32(u8EqadcIdx), EQADC_REG32_RESET_VALUE_U32);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_ETDFR_REG_ADDR32(u8EqadcIdx), EQADC_REG32_RESET_VALUE_U32);

            /* write command messages with reset default values of registers
             ADCn_CR, ADCn_GCCR and ADCn_OCCR */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | ((uint32)ADC_CFPR0_GCCR_U8 << 8U) | EQADC_ADC_GCCR_U8) \
                       );
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), (u32CBuffer | 0x0UL | EQADC_ADC_OCCR_U8));
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (EQADC_ADC_WRITE_CONFIG_EOQ_U32 | u32CBuffer | ((uint32)EQADC_ADC_CLK_PS_31_U8 << 8U) | (uint32)EQADC_ADC_CR_U8) \
                       );
            /* start CFIFO and wait until it is completed (EOQ flag set) */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
            
            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /* wait until calibration constants are written to ADC */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
            {
                u32Timeout--;
            }
            /* exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_06();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }
            /* Enter critical region */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_06();
            /* disable CFIFO and clear flags */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32));
        }
    }
#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
    for(GroupIdx = 0U; GroupIdx < (Adc_GroupType)ADC_MAX_GROUPS; GroupIdx++)
    {
        Adc_aGroupStatus[GroupIdx].eNotification = ADC_NOTIFICATION_DISABLED;
    }
#endif /* (ADC_GRP_NOTIF_CAPABILITY == STD_ON)*/
    
#if (STD_ON == ADC_HW_TRIGGER_API)
    /* set SIU_ISEL(4-7) default reset value */
    Adc_Siu_ResetAllHwTrigger();
#endif /* ADC_HW_TRIGGER_API */

    /* exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_06();
}
#endif /* #if (STD_ON == ADC_DEINIT_API) */

#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API)
/**
* @brief          This function stops the current conversion of a group.
* @details        This function stops the current conversion of a group.
*
* @param[in]      Unit      The hardware Unit.
* @param[in]      Group     The group id.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            If the conversion has stopped as expected.
* @retval         E_NOT_OK        In case of time-out while waiting for adc hardware to stop a conversion.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_StopCurrentConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(boolean, AUTOMATIC) bStartApi
)
{
    VAR(uint8, AUTOMATIC) u8EqadcIdx = (uint8)ADC_EQADC_A;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint8, AUTOMATIC) u8FifoPop;
    VAR(uint32, AUTOMATIC) u32TempBuffer;
    VAR(uint32, AUTOMATIC) u32ConvTimeOut = 0UL;
    VAR(Std_ReturnType, AUTOMATIC) RetVal;

    if(Unit > (Adc_HwUnitType)ADC_UNIT_1)
    {
        u8EqadcIdx = (uint8)ADC_EQADC_B;
    }
    
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    u8FifoIdx = Adc_pCfgPtr->pGroups[Group].u8AdcGroupFifo;

    /* Disable FIFO for this group */
    RetVal = Adc_Eqadc_DisableFifo(u8EqadcIdx, u8FifoIdx);
    if ((boolean)TRUE == bStartApi)
    {
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_07();
    }
    else
    {
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_08();
    }
    /* Test for FIFO's status failure. */
    if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(1UL, RetVal))
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
        return (Std_ReturnType)E_NOT_OK;
    }
    if ((boolean)TRUE == bStartApi)
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_07();
    }
    else
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_08();
    }
#ifdef ADC_DMA_SUPPORTED
    if (ADC_DMA == Adc_pCfgPtr->Misc.u8Adc_DmaInterruptSoftware[Unit])
    {
        Mcl_DmaDisableHwRequest((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][u8FifoIdx*2U]);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
        Mcl_DmaDisableNotification((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][u8FifoIdx*2U]);
#endif
        
        Mcl_DmaDisableHwRequest((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIdx*2U)+1U]);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
        Mcl_DmaDisableNotification((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIdx*2U)+1U]);
#endif
    }
#endif /* ADC_DMA_SUPPORTED  */
    
    /* Re-Enable CFIFO to execute a ADC on-chip register command. The completion of
     * this additional command will ensure that all the pending conversion commands have also been completed. */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_IDCR_CLEAR_U16);
    
    /* Issue the read command */
    if(0U == (Unit % 2U))
    {
        /* If ADC0 of EQADC-A/B  */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                    EQADC_ADC_WRITE_CONFIG_EOQ_U32 | EQADC_ADC_CONV_COM_BN0_U32 | \
                    EQADC_ADC_CR_U8 | ((uint32)u8FifoIdx << 20U) | EQADC_ADC_READ_CONFIG_R_U32 \
                   );
    }
    else
    {
        /* If ADC1 of EQADC-A/B  */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                    EQADC_ADC_WRITE_CONFIG_EOQ_U32 | EQADC_ADC_CONV_COM_BN1_U32 | \
                    EQADC_ADC_CR_U8 | ((uint32)u8FifoIdx << 20U) | EQADC_ADC_READ_CONFIG_R_U32 \
                   );
    }

    /* Wait until the CR register value pops out of the RFIFO.*/
    for(u8FifoPop = 0U; u8FifoPop <= (EQADC_FIFO_MAX_DEPTH_U8 + EQADC_CBUFFER_DEPTH_U8); u8FifoPop++)
    {
        u32ConvTimeOut = ADC_CFG_CONV_TIMEOUT;
        /* Wait for a value to appear in the RFIFO.*/
        do
        {
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            u32TempBuffer = REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
            u32ConvTimeOut--;
        }
        while ((u32ConvTimeOut != 0x0UL) && (0UL == (u32TempBuffer & EQADC_FISR_RFDF_U32)));
        
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        u32TempBuffer = REG_READ32(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
        /* Clear the RFDF to ensure that we do not read undefined results next time */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_RFDF_U32);
        u32TempBuffer = u32TempBuffer & (uint32)EQADC_ADC_STATUS_U16;
        if ((0UL == u32ConvTimeOut) || ((uint32)EQADC_ADC_EN_U16 == u32TempBuffer))
        {
            break;
        }
    }

    /* Disable FIFO again for this group */
    RetVal = Adc_Eqadc_DisableFifo(u8EqadcIdx, u8FifoIdx);
    if ((boolean)TRUE == bStartApi)
    {
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_07();
    }
    else
    {
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_08();
    }
    /* Test for FIFO's status failure. */
    if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32ConvTimeOut, RetVal))
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
        return (Std_ReturnType)E_NOT_OK;
    }
    if ((boolean)TRUE == bStartApi)
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_07();
    }
    else
    {
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_08();
    }
    
    Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
    Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
    /* Remove group from the array */
    Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx] = ADC_INVALID_GROUPS_ID;
    
    return (Std_ReturnType)E_OK;
}
#endif /* (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) */

#if (ADC_READ_GROUP_API == STD_ON)
/**
* @brief          This function reads the converted data for the requested group.
* @details        Reads the converted data for the requested group.
*
* @param[in]      Group           The group number.
* @param[in]      pDataPtr         Pointer to a buffer which will be filled by the
*                                 conversion results.
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            In case of successful read of the converted data.
* @retval         E_NOT_OK        In case of an ongoing conversion.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_ReadGroup
(
    CONST(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pDataPtr,
    P2VAR(boolean, AUTOMATIC, ADC_APPL_DATA) pFlag
)
{
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(Adc_ChannelIndexType, AUTOMATIC) Index = 0U;
    VAR(uint32, AUTOMATIC) DestOffset;
    VAR(Adc_StreamNumSampleType, AUTOMATIC) ResultIndex;
    VAR(Std_ReturnType, AUTOMATIC) ReadGroupRet = (Std_ReturnType)E_OK;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint8, AUTOMATIC) u8EqadcIdx = (uint8)ADC_EQADC_A;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit;
    VAR(Adc_ValueGroupType, AUTOMATIC) AdcCdrvalue;
    VAR(uint32, AUTOMATIC) u32TempBuffer;
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) ResultPtr;
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_DATA) pGroupPtr;
#if ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) || ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) && (ADC_ENABLE_LIMIT_CHECK == STD_ON)))
    VAR(uint8, AUTOMATIC) u8Shift;
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)... */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    VAR(Adc_ValueGroupType, AUTOMATIC) AdcTemp = 0U;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
    
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    pGroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
    u8FifoIdx = pGroupPtr->u8AdcGroupFifo;
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    Unit = Adc_GroupUnit(Group);
    if(Unit > (Adc_HwUnitType)ADC_UNIT_1)
    {
        u8EqadcIdx = (uint8)ADC_EQADC_B;
    }
  
    /* If the group is configured for without interrupts*/
    if((uint8)STD_ON == pGroupPtr->u8AdcWithoutInterrupt)
    {
        /* Enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_09();
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        u32TempBuffer = REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
        u32TempBuffer = u32TempBuffer & EQADC_FISR_RFCTR_U32;
        if((0U == Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIdx]) || \
           (0U == u32TempBuffer) \
          )
        {
            /* Exit critical region */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_09();
            /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
            return (Std_ReturnType)E_NOT_OK;
        }
        
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
        ChIndex = Adc_GroupChannelIndex(Group, 0U);
#if ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) || ((ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) && (ADC_ENABLE_LIMIT_CHECK == STD_ON)))
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
        u8Shift = (14U - Adc_pCfgPtr->pChannels[Unit][ChIndex].Res);
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)... */

        /* Read RFIFO into RAM buffer after right aligned */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        AdcCdrvalue = REG_READ16(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx) + 2U);
        /* Clear the RFDF bit in FISR0 register by writing 1 to it */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_RFDF_U32);
    
#if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT)
        AdcCdrvalue = (Adc_ValueGroupType)((uint32)AdcCdrvalue & EQADC_DATA_MASK_U32) >> u8Shift;
#endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_RIGHT) */

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
        if((boolean)TRUE == Adc_ChannelsLimitCheckingCfg[Unit][ChIndex].bChannelLimitCheck)
        {
    #if (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT)
            AdcTemp = (Adc_ValueGroupType)((uint32)AdcCdrvalue >> u8Shift);
    #else
            AdcTemp = AdcCdrvalue;
    #endif /* (ADC_RESULT_ALIGNMENT == ADC_ALIGN_LEFT) */
            (*pFlag) = (boolean)Adc_CheckConversionValuesInRange(AdcTemp, Unit, ChIndex);
            if ((*pFlag) == (boolean)TRUE)
            {
                /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
                pDataPtr[0] = (Adc_ValueGroupType)AdcCdrvalue;
            }
            else
            {
                Adc_aGroupStatus[Group].eAlreadyConverted = ADC_ALREADY_CONVERTED;
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
            pDataPtr[0] = (Adc_ValueGroupType)AdcCdrvalue;
        }
#else
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
        pDataPtr[0] = (Adc_ValueGroupType)AdcCdrvalue;
        (*pFlag) = (boolean)TRUE;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
        
        Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_09();
    }
    else
    {
        /* Enter critical region */
        SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_09();
        if (Adc_aGroupStatus[Group].eConversion == ADC_BUSY)
        {
            ReadGroupRet = (Std_ReturnType)E_NOT_OK;
        }
        else
        {
            /* get Index of last completed sample */
            if (0U == Adc_aGroupStatus[Group].ResultIndex)
            {
                ResultIndex = pGroupPtr->NumSamples - 1U;
            }
            else
            {
                ResultIndex = Adc_aGroupStatus[Group].ResultIndex - 1U;
            }
            /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
            ResultPtr = pGroupPtr->pResultsBufferPtr[Group] + ResultIndex;
            DestOffset = pGroupPtr->NumSamples;
        
            for(Index = 0U; Index < pGroupPtr->AssignedChannelCount; Index++)
            {
                /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
                pDataPtr[Index] = (*ResultPtr);
                /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
                ResultPtr += DestOffset;
            }
        }
        /* Exit critical region */
        SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_09();
        
        (*pFlag) = (boolean)TRUE;
    }
    
    return(ReadGroupRet);
}
#endif /* #if (STD_ON == ADC_READ_GROUP_API) */

#if (STD_ON == ADC_HW_TRIGGER_API)
/**
* @brief          This function enables the hardware triggers for the specified group.
* @details        This function enables the hardware triggers for the specified group.
*
* @param[in]      Group           The group for which the hardware triggers will be enabled.
* @param[in]      Unit            The hardware Unit. (on other platforms there are more hw units)
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Eqadc_EnableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) GroupPtr;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint8, AUTOMATIC) u8EqadcIdx = (uint8)ADC_EQADC_A;

    if(Unit > (Adc_HwUnitType)ADC_UNIT_1)
    {
        u8EqadcIdx = (uint8)ADC_EQADC_B;
    }
    
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    GroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
    u8FifoIdx = GroupPtr->u8AdcGroupFifo;
    /* Store the group Id into array */
    Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx] = Group;

    /* Clear RFIFO status */
    Adc_Eqadc_ClearRFifo(u8EqadcIdx, u8FifoIdx);
    
    /* init EQADC_IDCRx registers depending on selected hw Unit */
#ifdef ADC_DMA_SUPPORTED
    /* prepare conversion command messages */
    Adc_Eqadc_CopyQueueData2DmaCmdBuffer(Unit, u8EqadcIdx, u8FifoIdx);
    /* start eDMA channels, one to fill CFIFO and the another one to drain RFIFO */
    Adc_Eqadc_StartDmaOperation(Unit, u8EqadcIdx, u8FifoIdx);
    /* Configure IDCR register for the DMA mode */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), \
                (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_CFFS_U16 | EQADC_IDCR_RFDE_U16 | EQADC_IDCR_RFDS_U16) \
               );
#else
    Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
    Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
    /* Enable CFIFO Fill and RFIFO Drain Interrupts */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_RFDE_U16));
#endif /* ADC_DMA_SUPPORTED */

    /* Initiate SW conversion i.e. set transfer mode according to the group settings */
    /* Select the Triggering Source using the HW Trigger SelectorSIU_ISEL(4-5)  is used for the EQADC_A and SIU_ISEL(6-7)  is used for the EQADC_B */
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    Adc_Siu_EnableHwTrigger(GroupPtr->pHwResource[0], u8EqadcIdx, u8FifoIdx);

    if (ADC_HW_TRIG_RISING_EDGE == GroupPtr->eTriggerEdge)
    {
        /* hardware trigger continuous scan rising edge trigger source */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_HWCS_RED_U16);
    }
    else if(ADC_HW_TRIG_FALLING_EDGE == GroupPtr->eTriggerEdge)
    {
        /* hardware trigger continuous scan falling edge trigger source */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_HWCS_FED_U16);
    }
    else
    {
        /* hardware trigger continuous scan both edge trigger source */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_HWCS_BED_U16);
    }
}

/**
* @brief          This function disables the hardware triggers for the specified group.
* @details        This function disables the hardware triggers for the specified group.
*
* @param[in]      Group           The group for which the hardware triggers will be enabled.
* @param[in]      Unit            The hardware Unit. (on other platforms there are more hw units)
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Eqadc_DisableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    VAR(uint8, AUTOMATIC) u8EqadcIdx = (uint8)ADC_EQADC_A;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint8, AUTOMATIC) u8FifoPop;
    VAR(uint32, AUTOMATIC) u32ConvTimeOut = 0UL;
    VAR(uint32, AUTOMATIC) u32TempBuffer;
    VAR(Std_ReturnType, AUTOMATIC) RetVal;

    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();
    
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    u8FifoIdx = Adc_pCfgPtr->pGroups[Group].u8AdcGroupFifo;
    if(Unit > (Adc_HwUnitType)ADC_UNIT_1)
    {
        u8EqadcIdx = (uint8)ADC_EQADC_B;
    }
    
    /* Disable the hardware trigger source */
    Adc_Siu_DisableHwTrigger((uint8)u8EqadcIdx, (uint8)u8FifoIdx);
    
    RetVal = Adc_Eqadc_DisableFifo(u8EqadcIdx, u8FifoIdx);
    
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();
    /* Test for FIFO's status failure. */
    if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(1UL, RetVal))
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
        return;
    }
    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();
    
#ifdef ADC_DMA_SUPPORTED
    if (ADC_DMA == Adc_pCfgPtr->Misc.u8Adc_DmaInterruptSoftware[Unit])
    {
        Mcl_DmaDisableHwRequest((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][u8FifoIdx*2U]);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
        Mcl_DmaDisableNotification((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][u8FifoIdx*2U]);
#endif
        
        Mcl_DmaDisableHwRequest((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIdx*2U)+1U]);
#if (MCL_DMA_NOTIFICATION_SUPPORTED == STD_ON)
        Mcl_DmaDisableNotification((Mcl_ChannelType)Adc_pCfgPtr->Misc.aDmaChannel[u8EqadcIdx][(u8FifoIdx*2U)+1U]);
#endif
    }
#endif /* ADC_DMA_SUPPORTED  */
    
    /* Re-Enable CFIFO to execute a ADC on-chip register command. The completion of
     * this additional command will ensure that all the pending conversion commands
     * have also been completed. */
     /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_IDCR_CLEAR_U16);
    
    /* Issue the read command */
    if(0U == (Unit % 2U))
    {
        /* If ADC0 of EQADC-A/B  */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                    EQADC_ADC_WRITE_CONFIG_EOQ_U32 | EQADC_ADC_CONV_COM_BN0_U32 | \
                    EQADC_ADC_CR_U8 | ((uint32)u8FifoIdx << 20U) | EQADC_ADC_READ_CONFIG_R_U32 \
                   );
    }
    else
    {
        /* If ADC1 of EQADC-A/B  */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                    EQADC_ADC_WRITE_CONFIG_EOQ_U32 | EQADC_ADC_CONV_COM_BN1_U32 | \
                    EQADC_ADC_CR_U8 | ((uint32)u8FifoIdx << 20U) | EQADC_ADC_READ_CONFIG_R_U32 \
                   );
    }

    /* Wait until the CR register value pops out of the RFIFO.*/
    for(u8FifoPop = 0U; u8FifoPop < (EQADC_FIFO_MAX_DEPTH_U8 + EQADC_CBUFFER_DEPTH_U8 + 1U); u8FifoPop++)
    {
        u32ConvTimeOut = ADC_CFG_CONV_TIMEOUT;
        /* Wait for a value to appear in the RFIFO.*/
        do
        {
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            u32TempBuffer = REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
            u32ConvTimeOut--;
        }
        while ((u32ConvTimeOut != 0x0UL) && (0UL == (u32TempBuffer & EQADC_FISR_RFDF_U32)));
        
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        u32TempBuffer = REG_READ32(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
        /* Clear the RFDF to ensure that we do not read undefined results next time */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_RFDF_U32);
        u32TempBuffer = u32TempBuffer & (uint32)EQADC_ADC_STATUS_U16;
        if ((0UL == u32ConvTimeOut) || ((uint32)EQADC_ADC_EN_U16 == u32TempBuffer))
        {
            break;
        }
    }
    /* Disable the CFIFO again */
    RetVal = Adc_Eqadc_DisableFifo(u8EqadcIdx, u8FifoIdx);
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();
    if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32ConvTimeOut, RetVal))
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
        return;
    }
    /* Enter critical region */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11();

    Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
    Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
    /* Remove group from the array */
    Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx] = ADC_INVALID_GROUPS_ID;
    
    /* Exit critical region */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11();
}
#endif /* #if (ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
/**
* @brief          This function starts the conversion on the specified hardware Unit.
* @details        This function starts the conversion on the specified hardware Unit.
*                 This function should be called with the ADC Unit on standby (no ADC interruptions
*                 allowed because its code is not protected by critical regions) - no conversions must
*                 be running.
*
* @param[in]      Unit            the used hw Unit.
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Eqadc_StartNormalConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
)
{
    P2CONST(Adc_GroupConfigurationType, AUTOMATIC, ADC_APPL_CONST) GroupPtr; /* Pointer to AdcGroup */
    VAR(Adc_GroupType, AUTOMATIC) Group;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint8, AUTOMATIC) u8EqadcIdx = (uint8)ADC_EQADC_A;
#ifndef ADC_DMA_SUPPORTED
    VAR(Adc_ChannelType, AUTOMATIC) ChIndex;
    VAR(uint32, AUTOMATIC) u32FifoCmdmsg;
#endif

    if(Unit > (Adc_HwUnitType)ADC_UNIT_1)
    {
        u8EqadcIdx = (uint8)ADC_EQADC_B;
    }
    
    /* Get the Group ID of the current active group */
    Group = Adc_aUnitStatus[Unit].SwNormalQueue[0]; /* Load the first group in the queue */
    
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    if(((boolean)TRUE == Adc_aGroupStatus[Group].bLimitCheckFailed) && (ADC_CONV_MODE_ONESHOT == Adc_pCfgPtr->pGroups[Group].eMode))
    {
        /** @violates @ref Adc_Eqadc_c_REF_4 Return statement before end of function. */
        return;
    }
#endif /* ADC_ENABLE_LIMIT_CHECK == STD_ON */

    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    u8FifoIdx = Adc_pCfgPtr->pGroups[Group].u8AdcGroupFifo;
    /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
    GroupPtr = &(Adc_pCfgPtr->pGroups[Group]);
    /* Store the group Id into array */
    Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx] = Group;

    /* Clear RFIFO status */
    Adc_Eqadc_ClearRFifo(u8EqadcIdx, u8FifoIdx);

    /* Initiate SW conversion i.e. set transfer mode according to the group settings */
    if(ADC_CONV_MODE_ONESHOT == GroupPtr->eMode)
    {
        /* Software trigger single scan mode */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
    }
    else
    {
        /* Software trigger continuous scan mode */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_SWCS_U16);
    }
#ifdef ADC_DMA_SUPPORTED
    /* prepare conversion command messages */
    Adc_Eqadc_CopyQueueData2DmaCmdBuffer(Unit, u8EqadcIdx, u8FifoIdx);
    /* start eDMA channels, one to fill CFIFO and the another one to drain RFIFO */
    Adc_Eqadc_StartDmaOperation(Unit, u8EqadcIdx, u8FifoIdx);
    /* Configure IDCR register for the DMA mode */
    /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
    /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
    REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), \
                (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_CFFS_U16 | EQADC_IDCR_RFDE_U16 | EQADC_IDCR_RFDS_U16) \
               );
#else
    Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;
    Adc_Eqadc_RFifoChannelCount[u8EqadcIdx][u8FifoIdx] = 0U;

    if((uint8)STD_OFF == GroupPtr->u8AdcWithoutInterrupt)
    {
        /* Enable CFIFO Fill and RFIFO Drain Interrupts */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_RFDE_U16));
    }
    else
    {
        /* Increment count for number of messages transferred to CFIFO*/
        Adc_Eqadc_CFifoChannelCount[u8EqadcIdx][u8FifoIdx]++;
        /* Disable CFIFO Fill and RFIFO Drain Interrupts */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_BIT_CLEAR16(EQADC_IDCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_IDCR_CFFE_U16 | EQADC_IDCR_RFDE_U16));
        /* Last ADC channel, hence set the EOQ Flag */
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
        ChIndex = Adc_GroupChannelIndex(Group, 0U);
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be only allowed form of pointer arithmetic */
        u32FifoCmdmsg = (Adc_pCfgPtr->pChannels[Unit][ChIndex].u32Msg | (EQADC_RESULT_FIFO_OFFSET_U32*u8FifoIdx) | EQADC_ADC_WRITE_CONFIG_EOQ_U32);
        /* Write command data to CFIFO PUSH register*/
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), u32FifoCmdmsg);
        /* Clear the CFFF bit in FISR1 register by writing 1 to it */
        /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
        /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
        REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_CFFF_U32);
    }
#endif /* ADC_DMA_SUPPORTED */
}
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (STD_ON == ADC_CALIBRATION)
/**
* @brief          Executes high accuracy calibration of a ADC HW Unit.
* @details        This function calibrates the ADC HW Unit and updates calibration related registers
*
* @param[in]      Unit      ADC Unit Id.
* @param[in]      pStatus   Status of the ADC HW Unit calibration and
*                           list of failed/passed tests.
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Eqadc_Calibrate
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    P2VAR(Adc_CalibrationStatusType , AUTOMATIC, ADC_APPL_DATA) pStatus
)
{
    VAR(uint16, AUTOMATIC) u16Res25;
    VAR(uint16, AUTOMATIC) u16Res75;
    static VAR(uint16, AUTOMATIC) u16CalGcc;
    static VAR(sint16, AUTOMATIC) s16Occ;
    VAR(uint8, AUTOMATIC) u8EqadcIdx = (uint8)ADC_EQADC_A;
    VAR(uint8, AUTOMATIC) u8FifoIdx = 0U;
    VAR(uint32, AUTOMATIC) u32CBuffer = 0UL;
    VAR(uint32, AUTOMATIC) u32Timeout;
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex;
    
    /* Enter critical section */
    SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16();
    pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_OK;

    /* If HW Unit is configured to use, enable it and update the calibration constants */
    if((uint8)STD_ON == ADC_HW_UNITS(Unit))
    {
        if(Unit >= ADC_UNIT_2)
        {
            u8EqadcIdx = (uint8)ADC_EQADC_B;
        }
        /* Get the index of hardware Unit*/
        HwIndex = Adc_pCfgPtr->Misc.aHwLogicalId[Unit];
        /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
        if ((boolean)TRUE == Adc_pCfgPtr->pAdc[HwIndex].bCalibration)
        {
            /* Get the 1st fifo that is configured for the hardware which is being used for the ADC calibration */
            u8FifoIdx = Adc_pCfgPtr->Misc.au8FirstFifo[Unit];
            
            /* If ADC0 of EQADC-A/B  */
            if(0U == (Unit % 2U))
            {
                /* command buffer to be used is ZERO */
                u32CBuffer = EQADC_ADC_CONV_COM_BN0_U32;
            }
            else /* ADC1 of EQADC-A/B */
            {
                u32CBuffer = EQADC_ADC_CONV_COM_BN1_U32;
            }
            /* calibration: convert 25% and 75% VREF, compute calibration constants and write them into GCC and OCC registers */
            /* write command messages to sample 25% and 75% VREF */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | (EQADC_RESULT_FIFO_OFFSET_U32*u8FifoIdx) | EQADC_COMMAND_CAL_CHANNEL25_U32) \
                       );
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | (EQADC_RESULT_FIFO_OFFSET_U32*u8FifoIdx) | EQADC_COMMAND_CAL_CHANNEL75_U32 | EQADC_ADC_WRITE_CONFIG_EOQ_U32) \
                       );
            /* Start conversion */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));

            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((((REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_RFCTR_U32) >> 4U) < 2U) && \
                   (u32Timeout > 0UL) \
                  )
            {
                u32Timeout--;
            }
            /* Exit critical section */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }
            /* Enter critical section */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16();
            /* read results and compute calibration register values */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            u16Res25 = (uint16)REG_READ32(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            u16Res75 = (uint16)REG_READ32(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
            
            Adc_Eqadc_CalculateCalConst(u16Res25, u16Res75, &u16CalGcc, &s16Occ);
            
            /* write command messages to write u16CalGcc and s16Occ calibration constants into */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | ((uint32)u16CalGcc << 8UL) | EQADC_ADC_GCCR_U8) \
                       );
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | (((uint32)s16Occ & ADC_OCC_REG_U8) << 8UL) | ADC_CAL_CONST_U8 | EQADC_ADC_OCCR_U8 | EQADC_ADC_WRITE_CONFIG_EOQ_U32) \
                       );
            
            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /* wait until calibration constants are written to ADC */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((EQADC_FISR_EOQF_U32 != ((REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx))) & EQADC_FISR_EOQF_U32)) && \
                   (u32Timeout > 0UL) \
                  )
            {
                u32Timeout--;
            }
            
            /* Exit critical section */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }
            /* Enter critical section */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16();

            /* disable CFIFO and clear flags */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32) \
                       );

            /* write command messages to write u16CalGcc and s16Occ calibration constants into ADC0/ADC1 Alternate Gain/Offset 1 Register */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | ((uint32)u16CalGcc << 8UL) | EQADC_ADC_AG1R_U8) \
                       );
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | (((uint32)s16Occ & ADC_OCC_REG_U8) << 8UL) | ADC_CAL_CONST_U8 | EQADC_ADC_AO1R_U8 | EQADC_ADC_WRITE_CONFIG_EOQ_U32) \
                       );

            /* start conversion */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
            
            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /* wait until calibration constants are written to ADC */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((EQADC_FISR_EOQF_U32 != ((REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx))) & EQADC_FISR_EOQF_U32)) && \
                   (u32Timeout > 0UL) \
                  )
            {
                u32Timeout--;
            }
            /* Exit critical section */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }

            /* Enter critical section */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16();
            
            /* disable CFIFO and clear flags */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32) \
                       );

            /* write command messages to write u16CalGcc and s16Occ calibration constants into ADC0/ADC1 Alternate Gain/Offset 2 Register */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | ((uint32)u16CalGcc << 8UL) | EQADC_ADC_AG2R_U8) \
                       );
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (u32CBuffer | (((uint32)s16Occ & ADC_OCC_REG_U8) << 8UL) | ADC_CAL_CONST_U8 | EQADC_ADC_AO2R_U8 | EQADC_ADC_WRITE_CONFIG_EOQ_U32) \
                       );
            
            /* start conversion */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));
            
            /* Reload counter */
            u32Timeout = ADC_TIMEOUT_COUNTER;
            /* wait until calibration constants are written to ADC */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            while ((EQADC_FISR_EOQF_U32 != ((REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx))) & EQADC_FISR_EOQF_U32)) && \
                   (u32Timeout > 0UL) \
                  )
            {
                u32Timeout--;
            }
            /* Exit critical section */
            SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
            /* Test for FIFO's status failure. */
            if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
            {
                pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
                /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                return;
            }
            /* Enter critical section */
            SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16();
            
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            (void)REG_READ32(EQADC_RFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx));
            
            /* disable CFIFO and clear flags */
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
            /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
            /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
            REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                        (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32) \
                       );
        }
        else
        {
            pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        pStatus->Adc_UnitSelfTestStatus = (Std_ReturnType)E_NOT_OK;
    }
    /* Exit critical section */
    SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16();
}
#endif /* (STD_ON == ADC_CALIBRATION) */

#if (ADC_DUAL_CLOCK_MODE == STD_ON)
/**
* @brief          This function sets the Prescaler value only when ADC is in power down mode.
* @details        Set prescaler clock divider only in power down mode.
*
* @param[in]      eClockMode       ADC_NORMAL, ADC_ALTERNATE.
*
* @return         Std_ReturnType  E_OK or E_NOT_OK.
* @retval         E_OK            In case of successful set mode.
* @retval         E_NOT_OK        In case of unsuccessful set mode.
*
*/
FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_SetClockMode
(
   VAR(Adc_DualClockModeType, AUTOMATIC) eClockMode
)
{
    VAR(uint8, AUTOMATIC) u8EqadcIdx;
    VAR(uint8, AUTOMATIC) u8FifoIdx;
    VAR(uint32, AUTOMATIC) u32CBuffer;
    VAR(Adc_HwUnitType, AUTOMATIC) Unit = 0U; /* Hardware Unit index */
    VAR(Adc_HwUnitType, AUTOMATIC) HwIndex; /* Index of hardware Unit */
    VAR(volatile uint32, AUTOMATIC) u32Timeout;
    VAR(Std_ReturnType, AUTOMATIC) RetVal;
    P2CONST(Adc_Eqadc_HwUnitConfigurationType, AUTOMATIC, ADC_APPL_CONST) UnitConfigPtr; /* Pointer to Hw Unit config */

    for(u8EqadcIdx = 0U; u8EqadcIdx < ADC_EQADC_MAX_U8; u8EqadcIdx++)
    {
        for(u8FifoIdx = 0U; u8FifoIdx < ADC_EQADC_MAX_FIFO_U8; u8FifoIdx++)
        {
            Adc_Eqadc_FifoOngoingGroup[u8EqadcIdx][u8FifoIdx] = ADC_INVALID_GROUPS_ID;
            if((uint8)STD_ON == Adc_Eqadc_au8FifoArray[u8EqadcIdx][u8FifoIdx])
            {
                RetVal = Adc_Eqadc_DisableFifo(u8EqadcIdx, u8FifoIdx);
                if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(1UL, RetVal))
                {
                    /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                    return ((Std_ReturnType)E_NOT_OK);
                }
                /* To clear RFDF flag */
                Adc_Eqadc_ClearRFifo(u8EqadcIdx, u8FifoIdx);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_FISR_EOQF_U32 | EQADC_FISR_RFDF_U32 | EQADC_FISR_CFUF_U32));
            }
        }
    }
    
    u8EqadcIdx = (uint8)ADC_EQADC_A;
    for(Unit = 0U; Unit < (Adc_HwUnitType)ADC_MAX_HW_UNITS; Unit++)
    {
        if(Unit == 2U)
        {
            u8EqadcIdx = (uint8)ADC_EQADC_B;
        }

        /* If HW Unit is configured to use, enable it and update the calibration constants */
        if((uint8)STD_ON == ADC_HW_UNITS(Unit))
        {
            /* Get the index of hardware Unit*/
            HwIndex = Adc_pCfgPtr->Misc.aHwLogicalId[Unit];
            /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
            UnitConfigPtr = &(Adc_pCfgPtr->pAdc[HwIndex]);
            /* If ADC0 of EQADC-A/B  */
            if(0U == (Unit % 2U))
            {
                /* command buffer to be used is ZERO */
                u32CBuffer = EQADC_ADC_CONV_COM_BN0_U32;
            }
            else /* ADC1 of EQADC-A/B */
            {
                u32CBuffer = EQADC_ADC_CONV_COM_BN1_U32;
            }
            /* Get the 1st fifo that is configured for the hardware which is being used for the ADC calibration */
            u8FifoIdx = Adc_pCfgPtr->Misc.au8FirstFifo[Unit];       

            if ((Adc_DualClockModeType)ADC_NORMAL == eClockMode)
            {
                /* Disable ADC by set ADC0/1_EN of ADC0_CR and ADC1_CR register to 0 */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                            (u32CBuffer | EQADC_ADC_WRITE_CONFIG_EOQ_U32 | (uint32)EQADC_ADC_CR_U8) & \
                            (~((uint32)EQADC_ADC_EN_U16 << 8U)));
                /* Set SW SS mode and Start the Queue for the CFIFOi */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));

                /* Wait for EOQ flag to be set */
                /* Reload counter */
                u32Timeout = ADC_TIMEOUT_COUNTER;
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                /** @violates @ref Adc_Eqadc_c_REF_13 The right-hand operand of a logical && or || operator shall not contain side effects. */                
                while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
                {
                    u32Timeout--;
                }
                /* Test for FIFO's status failure. */
                if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
                {
                    /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                    return ((Std_ReturnType)E_NOT_OK);
                }                
                
                /* Disable the Queue and Clear the EOQ flag */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);

                /* Write the configuration clock into ADC0_CR and ADC1_CR register */
                /* Enable the ADC Unit 0 and set the Prescaler using CFIFOi, where i is configured fifo */
                /* ADCn_EN=1, ADCn_EMUX=0, ADCn_CLK_PS=ADC[HwIndex].Prescale */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                            (u32CBuffer | EQADC_ADC_WRITE_CONFIG_EOQ_U32 | (uint32)EQADC_ADC_CR_U8) | \
                            ((uint32)UnitConfigPtr->u32AdcControlConfig << 8U) \
                           );
                /* Set SW SS mode and Start the Queue for the CFIFOi */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));

                /* Wait for EOQ flag to be set */
                /* Reload counter */
                u32Timeout = ADC_TIMEOUT_COUNTER;
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                /** @violates @ref Adc_Eqadc_c_REF_13 The right-hand operand of a logical && or || operator shall not contain side effects. */                
                while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
                {
                    u32Timeout--;
                }
                /* Test for FIFO's status failure. */
                if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
                {
                    /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                    return ((Std_ReturnType)E_NOT_OK);
                }
                /* Disable the Queue and Clear the EOQ flag */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);
            }
            else
            {
                /* Disable ADC by set ADC0/1_EN of ADC0_CR and ADC1_CR register to 0 */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                            (u32CBuffer | EQADC_ADC_WRITE_CONFIG_EOQ_U32 | (uint32)EQADC_ADC_CR_U8) & \
                            (~((uint32)EQADC_ADC_EN_U16 << 8U)));
                /* Set SW SS mode and Start the Queue for the CFIFOi */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));

                /* Wait for EOQ flag to be set */
                /* Reload counter */
                u32Timeout = ADC_TIMEOUT_COUNTER;
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                /** @violates @ref Adc_Eqadc_c_REF_13 The right-hand operand of a logical && or || operator shall not contain side effects. */                
                while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
                {
                    u32Timeout--;
                }
                /* Test for FIFO's status failure. */
                if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
                {
                    /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                    return ((Std_ReturnType)E_NOT_OK);
                }                
                
                /* Disable the Queue and Clear the EOQ flag */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);

                /* Disable the Queue and Clear the EOQ flag */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);

                /** @violates @ref Adc_Adcdig_c_REF_9 cast from unsigned long to pointer */
                /** @violates @ref Adc_Adcdig_c_REF_3 A cast should not be performed between a pointer type and an integral type. */
                /* Write the configuration clock into ADC0_CR and ADC1_CR register */
                /* Enable the ADC Unit 0 and set the Prescaler using CFIFOi, where i is configured fifo */
                /* ADCn_EN=1, ADCn_EMUX=0, ADCn_CLK_PS=ADC[HwIndex].Prescale */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_5 Array indexing shall be the only allowed form of pointer arithmetic */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_CFPR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), \
                            (u32CBuffer | EQADC_ADC_WRITE_CONFIG_EOQ_U32 | (uint32)EQADC_ADC_CR_U8) | \
                            ((uint32)UnitConfigPtr->u32AdcAltPrescale << 8U) \
                           );
                /* Set SW SS mode and Start the Queue for the CFIFOi */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), (EQADC_CFCR_SSE_U16 | EQADC_CFCR_MODE_SWSS_U16));

                /* Wait for EOQ flag to be set */
                /* Reload counter */
                u32Timeout = ADC_TIMEOUT_COUNTER;
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                 /** @violates @ref Adc_Eqadc_c_REF_13 The right-hand operand of a logical && or || operator shall not contain side effects. */                
               while ((EQADC_FISR_EOQF_U32 != (REG_READ32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx)) & EQADC_FISR_EOQF_U32)) && (u32Timeout > 0UL))
                {
                    u32Timeout--;
                }
                /* Test for FIFO's status failure. */
                if((Std_ReturnType)E_NOT_OK == Adc_Eqadc_DemReportStatus(u32Timeout, (Std_ReturnType)E_OK))
                {
                    /** @violates @ref Adc_Eqadc_c_REF_4 return statement before end of function. */
                    return ((Std_ReturnType)E_NOT_OK);
                }
                /* Disable the Queue and Clear the EOQ flag */
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE16(EQADC_CFCR_REG_ADDR16(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_CFCR_MODE_DISABLED_U16);
                /** @violates @ref Adc_Eqadc_c_REF_3 cast from unsigned int to pointer. */
                /** @violates @ref Adc_Eqadc_c_REF_12 A cast should not be performed between a pointer type and an integral type. */
                REG_WRITE32(EQADC_FISR_REG_ADDR32(u8EqadcIdx, (uint32)u8FifoIdx), EQADC_FISR_EOQF_U32);
            }                       
        }
    }
    return ((Std_ReturnType)E_OK);
}
#endif /* (ADC_DUAL_CLOCK_MODE == STD_ON) */


#define ADC_STOP_SEC_CODE
/** 
 * @violates @ref Adc_Eqadc_c_REF_1 Only preprocessor statements and comments before '#include'
 * @violates @ref Adc_Eqadc_c_REF_2 Repeated include file MemMap.h 
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */