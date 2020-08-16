/**
*   @file    Lin_NonASR.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Lin - Lin NonAutosar high level interface implementation.
*   @details Lin NonAutosar high level interface implementation.
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
/*==================================================================================================
==================================================================================================*/

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section Lin_NonASR_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken
* in order to prevent the contents of a header file being included twice.
* This comes from the order of includes in the .c file and from
* include dependencies. As a safe approach, any file must include all
* its dependencies. Header files are already protected against double
* inclusions. The inclusion of MemMap.h is as per Autosar
* requirement MEMMAP003.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall
* be checked to ensure that 31 character signifiance and
* case sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have
* a file version check.
*
* @section Lin_NonASR_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, Casting operation to a pointer.
* This violation is due to the Casting pointers to other types used in macros
* for Reading or writing data from address location of controller register
*
* @section Lin_NonASR_c_REF_4
* Violates MISRA 2004 Advisory Rule 19.1, #include statements in a
* file should only be preceded by other preprocessor directives or
* comments. AUTOSAR imposes the specification of the sections in which
* certain parts of the driver must be placed.
*
* @section Lin_NonASR_c_REF_5
* Violates MISRA 2004 Required Rule 8.10, Not required from Autosar
* specification.
*
* @section Lin_NonASR_c_REF_6
* Violates MISRA 2004 Required Rule 1.2, Taking address of near auto variable
* The code is not dynamically linked. An absolute stack address is obtained
* when taking the address of the near auto variable. A source of error in writing dynamic code is
* that the stack segment may be different from the data segment.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/**
* @file           Lin_NonASR.c
*/
#include "Lin.h"
#include "Lin_NonASR.h"
#include "Lin_IPW.h"
#include "Lin_ESCI.h"

#ifdef LIN_USE_DMA
#include "CDD_Mcl.h"
#endif  /* LIN_USE_DMA */

#include "StdRegMacros.h"
/**
* @violates @ref Lin_NonASR_c_REF_1 Precautions shall be taken in order to prevent the contents
* of a header file being included twice.
*/
#include "Reg_eSys.h"
#include "Reg_eSys_ESCI.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @file           Lin_NonASR.c
*/
#define LIN_VENDOR_ID_NONASR_C                      43
#define LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C       4
#define LIN_AR_RELEASE_MINOR_VERSION_NONASR_C       0
#define LIN_AR_RELEASE_REVISION_VERSION_NONASR_C    3
#define LIN_SW_MAJOR_VERSION_NONASR_C               1
#define LIN_SW_MINOR_VERSION_NONASR_C               0
#define LIN_SW_PATCH_VERSION_NONASR_C               1
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Lin header file are of the same vendor */
#if (LIN_VENDOR_ID_NONASR_C != LIN_VENDOR_ID)
    #error "Lin_NonASR.c and Lin.h have different vendor ids"
#endif
/* Check if current file and Lin header file are of the same Autosar version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MINOR_VERSION) || \
     (LIN_AR_RELEASE_REVISION_VERSION_NONASR_C != LIN_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Lin_NonASR.c and Lin.h are different"
#endif
/* Check if current file and Lin header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_NONASR_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_NONASR_C != LIN_SW_MINOR_VERSION) || \
     (LIN_SW_PATCH_VERSION_NONASR_C != LIN_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lin_NonASR.c and Lin.h are different"
#endif
/* Check if current file and Lin_Ipw header file are of the same vendor */
#if (LIN_VENDOR_ID_NONASR_C != LIN_IPW_VENDOR_ID)
    #error "Lin_NonASR.c and Lin_NonASR.h have different vendor ids"
#endif
/* Check if current file and Lin_Ipw header file are of the same version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MAJOR_VERSION_IPW) || \
     (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MINOR_VERSION_IPW) || \
     (LIN_AR_RELEASE_REVISION_VERSION_NONASR_C != LIN_AR_RELEASE_REVISION_VERSION_IPW))
    #error "AutoSar Version Numbers of Lin_NonASR.c and Lin_Ipw.h are different"
#endif
/* Check if current file and Lin_Ipw header file are of the same version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MAJOR_VERSION_IPW) || \
     (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MINOR_VERSION_IPW) || \
     (LIN_AR_RELEASE_REVISION_VERSION_NONASR_C != LIN_AR_RELEASE_REVISION_VERSION_IPW))
    #error "AutoSar Version Numbers of Lin_NonASR.c and Lin_Ipw.h are different"
#endif
/* Check if current file and Lin_NonASR header file are of the same vendor */
#if (LIN_VENDOR_ID_NONASR_C != LIN_VENDOR_ID_NONASR)
    #error "Lin_NonASR.c and Lin_NonASR.h have different vendor ids"
#endif
/* Check if current file and Lin_NonASR header file are of the same Autosar version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MAJOR_VERSION_NONASR) || \
     (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MINOR_VERSION_NONASR) || \
     (LIN_AR_RELEASE_REVISION_VERSION_NONASR_C != LIN_AR_RELEASE_REVISION_VERSION_NONASR))
    #error "AutoSar Version Numbers of Lin_NonASR.c and Lin_NonASR.h are different"
#endif
/* Check if current file and Lin_NonASR header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_NONASR_C != LIN_SW_MAJOR_VERSION_NONASR) || \
     (LIN_SW_MINOR_VERSION_NONASR_C != LIN_SW_MINOR_VERSION_NONASR) || \
     (LIN_SW_PATCH_VERSION_NONASR_C != LIN_SW_PATCH_VERSION_NONASR))
    #error "Software Version Numbers of Lin_NonASR.c and Lin_NonASR.h are different"
#endif
/* Check if current file and uLin_ESCI header file are of the same vendor */
#if (LIN_VENDOR_ID_NONASR_C != LIN_VENDOR_ID_ESCI)
    #error "Lin_NonASR.c and uLin_ESCI.h have different vendor ids"
#endif
/* Check if current file and Lin_ESCI header file are of the same Autosar version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MAJOR_VERSION_ESCI) || \
     (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MINOR_VERSION_ESCI) || \
     (LIN_AR_RELEASE_REVISION_VERSION_NONASR_C != LIN_AR_RELEASE_REVISION_VERSION_ESCI))
    #error "AutoSar Version Numbers of Lin_NonASR.c and Lin_ESCI.h are different"
#endif
/* Check if current file and Lin_ESCI header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_NONASR_C != LIN_SW_MAJOR_VERSION_ESCI) || \
     (LIN_SW_MINOR_VERSION_NONASR_C != LIN_SW_MINOR_VERSION_ESCI) || \
     (LIN_SW_PATCH_VERSION_NONASR_C != LIN_SW_PATCH_VERSION_ESCI))
    #error "Software Version Numbers of Lin_NonASR.c and Lin_ESCI.h are different"
#endif
/* Check if current file and Reg_eSys_ESCI header file are of the same vendor */
#if (LIN_VENDOR_ID_NONASR_C != LIN_VENDOR_ID_REGESCI)
    #error "Lin_NonASR.c and Reg_eSys_ESCI.h have different vendor ids"
#endif
/* Check if current file and Reg_eSys_ESCI header file are of the same Autosar version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MAJOR_VERSION_REGESCI) || \
     (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C    != LIN_AR_RELEASE_MINOR_VERSION_REGESCI) || \
     (LIN_AR_RELEASE_REVISION_VERSION_NONASR_C != LIN_AR_RELEASE_REVISION_VERSION_REGESCI))
    #error "AutoSar Version Numbers of Lin_NonASR.c and Reg_eSys_ESCI.h are different"
#endif
/* Check if current file and Reg_eSys_ESCI header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_NONASR_C != LIN_SW_MAJOR_VERSION_REGESCI) || \
     (LIN_SW_MINOR_VERSION_NONASR_C != LIN_SW_MINOR_VERSION_REGESCI) || \
     (LIN_SW_PATCH_VERSION_NONASR_C != LIN_SW_PATCH_VERSION_REGESCI))
    #error "Software Version Numbers of Lin_NonASR.c and Reg_eSys_ESCI.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  /* Check if the source file and StdRegMacros header file are of the same version */
  #if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C != STDREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C != STDREGMACROS_AR_RELEASE_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin_NonASR.c and StdRegMacros.h are different"
  #endif
  /* Check if the source file and Reg_eSys header file are of the same version */
  #if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C != REG_ESYS_AR_RELEASE_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin_NonASR.c and Reg_eSys.h are different"
  #endif
#ifdef LIN_USE_DMA
    /* Check if the source file and CDD_Mcl header file are of the same version */
  #if ((LIN_AR_RELEASE_MAJOR_VERSION_NONASR_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_AR_RELEASE_MINOR_VERSION_NONASR_C != MCL_AR_RELEASE_MINOR_VERSION))
      #error "AutoSar Version Numbers of Lin_NonASR.c and CDD_Mcl.h are different"
  #endif
#endif  /* LIN_USE_DMA */
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
#if (defined(LIN_USE_DMA) && defined(LIN_USE_MSC))
    #define LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
    /**
    * @violates @ref Lin_NonASR_c_REF_1 Precautions shall be taken in order to prevent the contents
    * of a header file being included twice.
    */
         #include "MemMap.h"
     
    static VAR(Mcl_DmaTcdAttributesType, LIN_VAR) Lin_DmaConfigDescriptor;

    #define LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
    /**
    * @violates @ref Lin_NonASR_c_REF_1 Precautions shall be taken in order to prevent the contents
    * of a header file being included twice.
    *
    * @violates @ref Lin_NonASR_c_REF_4 #include statements in a file should only be preceded
    * by other preprocessor directives or comments.
    */
         #include "MemMap.h"
     
#endif  /* LIN_USE_DMA && LIN_USE_MSC */

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
#ifdef LIN_USE_MSC

    #define LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED
    /**
    * @violates @ref Lin_NonASR_c_REF_1 Precautions shall be taken in order to prevent the contents
    * of a header file being included twice.
    */
         #include "MemMap.h"
     
    /**
    * @brief          MSC Buffers.
    * @details        Global variable to allow the appication
    *                 to buffer data for MSC u8Channel.
    *
    */
    volatile VAR(Lin_MscDataType,LIN_VAR) Lin_MscBuffer[LIN_HW_MAX_MODULES];

    #define LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    /**
    * @violates @ref Lin_NonASR_c_REF_1 Precautions shall be taken in order to prevent the contents
    * of a header file being included twice.
    *
    * @violates @ref Lin_NonASR_c_REF_4 #include statements in a file should only be preceded
    * by other preprocessor directives or comments.
    */
         #include "MemMap.h"
     
#endif

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define LIN_START_SEC_CODE
/**
* @violates @ref Lin_NonASR_c_REF_1 Precautions shall be taken in order to prevent the contents
* of a header file being included twice.
*/
/**
* @violates @ref Lin_NonASR_c_REF_4 #include statements in a file should only be preceded
* by other preprocessor directives or comments.
*/
 #include "MemMap.h"
 
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
#if LIN_DUAL_CLOCK_MODE == STD_ON

/**
* @brief          Lin_SetClockMode.
* @details        Switch the clock mode to the alternate clock mode on
*                 all the Lin channels.
*
* @param[in]      ClockMode   New clock mode.
*
* @return                     The result of the switching clock operation.
* @retval E_OK                The switching operation was OK.
* @retval E_NOT_OK            The switching operation has failed caused by the
*                             wrong driver state.
*
* @api            Switch the clock mode to the alternate clock mode on all
*                 the Lin channels.
*
* @pre            LIN_DUAL_CLOCK_MODE must be defined and its value must be STD_ON.
*
* @implements     Lin_SetClockMode_Activity
*
* @note           Switch the clock mode to the alternate clock mode on
*                 all the Lin channels.
*/
/**
* @violates @ref Lin_NonASR_c_REF_5 All declarations and definitions of objects
* or functions at file scope shall have internal linkage unless external linkage is required.
*/
FUNC(Std_ReturnType, LIN_CODE) Lin_SetClockMode(VAR(Lin_ClockModesType, AUTOMATIC) ClockMode)
{
    VAR(Std_ReturnType, AUTOMATIC) u8TempReturn = (uint8)E_OK;
    VAR(uint8,AUTOMATIC) u8chLoop;
    VAR(uint8,AUTOMATIC) u8Lin_ESCI;
    VAR(Lin_StatusType,AUTOMATIC) LinStatus = LIN_NOT_OK;
    VAR(uint8,AUTOMATIC) *pu8linSduPtr[1];
    VAR(uint8,AUTOMATIC) au8linSdu[8] = {(uint8)0, (uint8)0, (uint8)0, (uint8)0, (uint8)0, (uint8)0, (uint8)0, (uint8)0};

    /* @violates @ref Lin_NonASR_c_REF_6 Taking address of near auto variable */
    pu8linSduPtr[0] = au8linSdu;

    for(u8chLoop=(uint8)0U; u8chLoop < LIN_HW_MAX_MODULES; u8chLoop++)
    {
        /* Get the hardware Lin u8Channel from logical u8Channel */
        u8Lin_ESCI = Lin_pChannelConfigPtr[u8chLoop]->u8LinHwChannel;

        /* @violates @ref Lin_NonASR_c_REF_6 Taking address of near auto variable */
        LinStatus = Lin_GetStatus(u8chLoop, pu8linSduPtr);

        switch (LinStatus)
        {
            case LIN_NOT_OK :
            /* If the LIN driver or some channels are not initialized it's not possible to
                change the baudrate */
                u8TempReturn = (uint8)E_NOT_OK;
                break;
            default :
                    if (LIN_NORMAL == ClockMode)
                        {
                            /* set baud rate value for normal running mode */
                            /**
                            * @violates @ref Lin_NonASR_c_REF_3 cast from unsigned int to pointer
                            */
                            REG_WRITE16(ESCI_BRR_ADDR32(u8Lin_ESCI), (uint16)((Lin_pcConfigPtr->pLin_Channel[u8chLoop]->u32Lin_BaudRate_RegValue) & (ESCI_BRR_SBR_MASK_U16)));
                        }
                    else
                        {
                            /* set baud rate value for low power mode */
                            /**
                            * @violates @ref Lin_NonASR_c_REF_3 cast from unsigned int to pointer
                            */
                            REG_WRITE16(ESCI_BRR_ADDR32(u8Lin_ESCI), (uint16)((Lin_pcConfigPtr->pLin_Channel[u8chLoop]->u32Lin_BaudRate_RegValue_Alternate) & (ESCI_BRR_SBR_MASK_U16)));
                        }
                break;
        }
    }
    return u8TempReturn;
}

#endif /* DUAL CLOCK MODE */


#ifdef LIN_USE_MSC

/**
* @brief   Msc_InitChannel
* @details Initialize Channel with MSC functionality.
*
* @param[in] Channel - MSC to be initialized.
* @param[in] Config  - Pointer to LIN Channel configuration set.
*
*/

FUNC(void, LIN_CODE) Msc_InitChannel( CONST(uint8, AUTOMATIC) u8Channel, \
                        P2CONST(Lin_ChannelConfigType, AUTOMATIC, LIN_APPL_CONST) pcConfig)
{
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    /* Check for invalid Channel */
    if (u8Channel >= LIN_HW_MAX_MODULES)
    {
        /* Invalid Channel */
    #if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_INITCHANNEL_ID,\
                          (uint8)LIN_E_INVALID_CHANNEL);
    #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        /* Check Config for not being a null pointer */
        if (pcConfig == NULL_PTR)
        {
            /* Invalid pointer */
        #if (LIN_DEV_ERROR_DETECT == STD_ON)
            /* Report error to development error tracer */
            Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_INITCHANNEL_ID,\
                          (uint8)LIN_E_INVALID_POINTER);
        #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
        else
        {
            Lin_pChannelConfigPtr[u8Channel] = pcConfig;

            if(Lin_pChannelConfigPtr[u8Channel]->u8Lin_MscEnabled == (uint8)STD_ON)
            {
                /* Initialize MSC buffer */
                Lin_MscBuffer[u8Channel].u8Data = 0U;
                Lin_MscBuffer[u8Channel].u8Errors = 0U;
                Lin_MscBuffer[u8Channel].u8Address = 0U;

                /* Update MSC Channel frame operation status to LIN_MSC_IDLE */
                Lin_MscBuffer[u8Channel].State = LIN_MSC_IDLE;

                /* Get the hardware Lin Channel from logical Channel */
                u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;


                /* Enable eSCI module */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_MDIS_MASK_U16);

                /* Set MSC frame format */
                if (Lin_pChannelConfigPtr[u8Channel]->Lin_MscFrameFormat == LIN_MSC_16_BITS)
                {
                    /* Use 16-bit format (1 start bit, 12 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains 4-bit address field and 8 data bits. */
                    /* LSB is received first. */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_M_MASK_U16);
                }
                else
                {
                    /* Use 12-bit format (1 start bit, 8 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains only 8 data bits. */
                    /* LSB is received first. */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_M_MASK_U16);
                }

                /* Set Frame Format Mode 2 value */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_SET16(ESCI_CR3_ADDR32(u8Lin_ESCI),ESCI_CR3_M2_MASK_U16);

                /* Set Parity Enable value */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_PE_MASK_U16);

                /* check the parity type for even or odd */
                if (Lin_pChannelConfigPtr[u8Channel]->Lin_MscParity == LIN_MSC_EVEN)
                {
                    /* Even parity */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_PT_MASK_U16);
                }
                else
                {
                    /* Odd parity.*/
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_PT_MASK_U16);
                }

                /* Set baud rate value */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_WRITE16(ESCI_BRR_ADDR32(u8Lin_ESCI), ((Lin_pChannelConfigPtr[u8Channel]->u16Lin_MscBaudRate_RegValue) & ESCI_BRR_SBR_MASK_U16));

                if (Lin_pChannelConfigPtr[u8Channel]->Lin_MscPolarity == LIN_MSC_NORMAL)
                {
                    /* A RX low level bit at SI is stored in the upstream Channel as logic 0. */
                    /* A RX high level bit at SI is stored in the upstream Channel as logic 1.*/
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXPOL_MASK_U16);
                }
                else
                {
                    /* A RX low level bit at SI is stored in the upstream Channel as logic 1. */
                    /* A RX high level bit at SI is stored in the upstream Channel as logic 0.*/
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXPOL_MASK_U16);
                }

                /* Enable Receiver*/
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

                if (Lin_pChannelConfigPtr[u8Channel]->u8Lin_MscPollingMode == (uint8)STD_OFF)
                {

                    /* Enable the Receive Interrupt Enable */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RIE_MASK_U16);

                    /* Enable Frame Error Interrupt */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FEIE_MASK_U16);

                    /* Enable Parity Flag Interrupt */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_PFIE_MASK_U16);

                    /* Enable Noise Flag Interrupt */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_NFIE_MASK_U16);

                    /* Enable Overrun Flag Interrupt */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_ORIE_MASK_U16);

                }
                else
                {

                    /* Enable Overrun Flag Interrupt */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR3_ADDR32(u8Lin_ESCI), ESCI_CR3_EROE_MASK_U16);

                    /* Enable Frame Error Interrupt */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR3_ADDR32(u8Lin_ESCI), ESCI_CR3_ERFE_MASK_U16);

                    /* Enable Parity Flag Interrupt */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR3_ADDR32(u8Lin_ESCI), ESCI_CR3_ERPE_MASK_U16);

                }

            #ifdef LIN_USE_DMA
                /* DMA_RX  */
                Lin_DmaConfigDescriptor.saddr = ESCI_SDR_ADDR32(u8Lin_ESCI);
                Lin_DmaConfigDescriptor.daddr = (uint32)&(Lin_MscBuffer[u8Channel].u8Data);
                Lin_DmaConfigDescriptor.ssize = 0U;
                Lin_DmaConfigDescriptor.dsize = 0U;
                Lin_DmaConfigDescriptor.soff = 0U;
                Lin_DmaConfigDescriptor.doff = 1U;
                Lin_DmaConfigDescriptor.smod = 0U;
                Lin_DmaConfigDescriptor.dmod = 0U;
                Lin_DmaConfigDescriptor.num_bytes = 1U;
                Lin_DmaConfigDescriptor.iter = 1U;
                Mcl_DmaConfigChannel(Lin_pChannelConfigPtr[u8Channel]->u8Lin_RxDMAChannel, &Lin_DmaConfigDescriptor);
                Mcl_DmaEnableHwRequest(Lin_pChannelConfigPtr[u8Channel]->u8Lin_RxDMAChannel);
                /**
                * @violates @ref Lin_NonASR_c_REF_3 cast from unsigned int to pointer
                */
                Mcl_DmaTcdSetIntMaj((uint32 *)Mcl_DmaGetChannelTcdAddress(Lin_pChannelConfigPtr[u8Channel]->u8Lin_RxDMAChannel));
            #endif  /* LIN_USE_DMA */

                /* Update MSC Channel frame operation status to LIN_MSC_READY */
                Lin_MscBuffer[u8Channel].State = LIN_MSC_READY;

                /* Map configured hardware Channel to logical Channel */
                Lin_as8ChannelHardwareMap[Lin_pChannelConfigPtr[u8Channel]->u8LinChannelID] = (sint8)Lin_pChannelConfigPtr[u8Lin_ChLoop]->u8LinHwChannel;
            }
        }

    }

    return;
}

/**
* @brief   Msc_DeInitChannel
* @details De-Inits a Channel with MSC functionality.
*
* @param[in] Channel - MSC to be de-initialized.
*
*/

FUNC(void, LIN_CODE) Msc_DeInitChannel( CONST(uint8, AUTOMATIC) u8Channel)
    {
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    /* Check for invalid Channel */
    if (u8Channel >= LIN_HW_MAX_MODULES) /* Invalid Channel */
        {

#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_DEINITCHANNEL_ID,\
                (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
    else
        {

        if (Lin_pChannelConfigPtr[u8Channel]->u8Lin_MscEnabled == (uint8)STD_ON)
            {

            /* Clear MSC buffer */
            Lin_MscBuffer[u8Channel].u8Data = 0U;
            Lin_MscBuffer[u8Channel].u8Errors = 0U;
            Lin_MscBuffer[u8Channel].u8Address = 0U;

            /* Get the hardware Lin Channel from logical Channel */
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;

            /* Disable eSCI module */
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_MDIS_MASK_U16);

            /* Write the reset value of Control Register 1 (eSCI_CR1)*/
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            REG_WRITE16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RESET_MASK_U16);

            /* Disable Parity Enable value */
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_PE_MASK_U16);

            /* set default parity type */
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_PT_MASK_U16);

            /* Write the reset value of Baud Rate Register (eSCI_BRR)*/
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            REG_WRITE16(ESCI_BRR_ADDR32(u8Lin_ESCI), ESCI_BRR_RESET_MASK_U16);

            if (Lin_pChannelConfigPtr[u8Channel]->u8Lin_MscPollingMode == (uint8)STD_OFF)
                {
                /* Disable the Receive Interrupt Enable */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RIE_MASK_U16);

                /* Disable Frame Error Interrupt */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FEIE_MASK_U16);

                /* Disable Parity Flag Interrupt */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_PFIE_MASK_U16);

                /* Disable Noise Flag Interrupt */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_NFIE_MASK_U16);

                /* Disable Overrun Flag Interrupt */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_ORIE_MASK_U16);

                }
            else
                {

                /* Disable Overrun Flag Interrupt */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR3_ADDR32(u8Lin_ESCI), ESCI_CR3_EROE_MASK_U16);

                /* Disable Frame Error Interrupt */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR3_ADDR32(u8Lin_ESCI), ESCI_CR3_ERFE_MASK_U16);

                /* Disable Parity Flag Interrupt */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR3_ADDR32(u8Lin_ESCI), ESCI_CR3_ERPE_MASK_U16);

                }

#ifdef LIN_USE_DMA
            if(Lin_pChannelConfigPtr[u8Channel]->u8Lin_DMAEnabled == (uint8)STD_ON)
                {
                /* DMA is used */


                /* Receive DMA disabled */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);

                /* Disable the interrupt for RX DMA Channel */
                Mcl_DmaDisableNotification(Lin_pChannelConfigPtr[u8Channel]->u8Lin_RxDMAChannel);

                }
#endif  /* LIN_USE_DMA */

            /* Disable Receiver*/
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

            /* Update MSC Channel frame operation status to LIN_MSC_IDLE */
            Lin_MscBuffer[u8Channel].State = LIN_MSC_IDLE;

            /* Remove Channel from hardware map */
            Lin_as8ChannelHardwareMap[Lin_pChannelConfigPtr[u8Channel]->u8LinChannelID] = -1;

            }

        }

    return;

    }

/**
* @brief   Msc_GetStatus
* @details Gets the status of the Channel with MSC functionality.
*
* @param[in] Channel - MSC to be initialized.
*
* @param[out] Lin_SduPtr   Pointer to pointer to a shadow
*                          buffer or memory mapped eSCI Hardware
*                          receive buffer where the current data is
*                          stored.
* @return Msc_StatusType   The MSC Channel status.
* - LIN_MSC_IDLE            Receiver is disabled and no
*                       reception is running.
* - LIN_MSC_READY           Receiver is enabled and no
*                       reception is running.
* - LIN_MSC_RUN             Receiver is enabled and
*                       reception is running.
* - LIN_MSC_WAKEUP          Receiver is in wakeup mode.
* - LIN_MSC_OVERRUN_ERROR   Erroneous reception due to
*                       an OR error.
* - LIN_MSC_FRAMING_ERROR   Erroneous reception due to
*                       a FE error.
* - LIN_MSC_PARITY_ERROR    Erroneous reception due to
*                       a PE error.
* - LIN_MSC_NOISE_ERROR     Erroneous reception due to
*                       an NF error.
*
*/

FUNC(Msc_StatusType, LIN_CODE) Msc_GetStatus( CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    VAR(Msc_StatusType, AUTOMATIC) MSC_State = LIN_MSC_IDLE;

    /* Check for invalid Channel */
    if (u8Channel >= LIN_HW_MAX_MODULES) /* Invalid Channel */
    {
    #if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_GETSTATUS_ID,\
                (uint8)LIN_E_INVALID_CHANNEL);
    #endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {
        if (Lin_pChannelConfigPtr[u8Channel]->u8Lin_MscEnabled == (uint8)STD_ON)
        {
            /* Get the hardware Lin Channel from logical Channel */
            u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;


            switch (Lin_MscBuffer[u8Channel].State)
            {
                case LIN_MSC_IDLE :
                    /* Check if RE Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_IFSR1_RACT_MASK_U16 != (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_RACT_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_READY;
                    }

                    break;
                case LIN_MSC_READY :
                    /* Check if RACT Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_IFSR1_RACT_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_RACT_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_RUN;
                    }

                    /* Check if RWU Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_WAKEUP;
                    }

                    /* Check if RE Flag is reset */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_IFSR1_RACT_MASK_U16 != (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_RACT_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_IDLE;
                    }

                    break;
                case LIN_MSC_RUN :
                    /* Check if RE Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_IFSR1_RACT_MASK_U16 != (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_RACT_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_READY;
                    }

                    /* Check if RWU Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_WAKEUP;
                    }

                    /* Check if RE Flag is reset */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_IFSR1_RACT_MASK_U16 != (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_RACT_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_IDLE;
                    }

                    /* Check if OR Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_IFSR1_OR_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_OR_MASK_U16)) && \
                        (ESCI_SDR_ERR_MASK_U16 == (REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_ERR_MASK_U16)) \
                       )
                    {
                        /* Overrun Error flag */
                        /*
                        * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_OR_MASK_U16);

                        Lin_MscBuffer[u8Channel].State = LIN_MSC_OVERRUN_ERROR;
                    }

                    /* Check if FE Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if (ESCI_IFSR1_FE_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_FE_MASK_U16)) && \
                        (ESCI_SDR_ERR_MASK_U16 == (REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_ERR_MASK_U16)) \
                       )
                    {
                        /* Framing Error flag */
                        /*
                        * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                        Lin_MscBuffer[u8Channel].State = LIN_MSC_FRAMING_ERROR;
                    }

                    /* Check if NF Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_IFSR1_NF_MASK_U16 == (REG_READ16(ESCI_IFSR1(u8Lin_ESCI)) & ESCI_IFSR1_NF_MASK_U16)) && \
                        (ESCI_SDR_ERR_MASK_U16 == (REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_ERR_MASK_U16)) \
                       )
                    {
                        /* Noise Error flag */
                        /*
                        * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

                        Lin_MscBuffer[u8Channel].State = LIN_MSC_NOISE_ERROR;
                    }

                    /* Check if PF Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_IFSR1_PF_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_PF_MASK_U16)) && \
                        (ESCI_SDR_ERR_MASK_U16 == (REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_ERR_MASK_U16)) \
                       )
                    {
                        /* Parity Error flag */
                        /*
                        * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_PF_MASK_U16);

                        Lin_MscBuffer[u8Channel].State = LIN_MSC_PARITY_ERROR;
                    }

                    break;
                case LIN_MSC_WAKEUP :
                    /* Check if RE Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_IFSR1_RACT_MASK_U16 != (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_RACT_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_READY;
                    }

                    /* Check if RACT Flag is set */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    if ((ESCI_CR1_RE_MASK_U16 == (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RE_MASK_U16)) && \
                        (ESCI_IFSR1_RACT_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_RACT_MASK_U16)) && \
                        (ESCI_CR1_RWU_MASK_U16 != (REG_READ16(ESCI_CR1_ADDR32(u8Lin_ESCI)) & ESCI_CR1_RWU_MASK_U16)) \
                       )
                    {
                        Lin_MscBuffer[u8Channel].State = LIN_MSC_RUN;
                    }
                        break;
                case LIN_MSC_OVERRUN_ERROR :
                case LIN_MSC_FRAMING_ERROR :
                case LIN_MSC_PARITY_ERROR :
                case LIN_MSC_NOISE_ERROR :
                default :
                    /* Disable Receiver*/
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK);

#ifdef LIN_USE_DMA
                    /* Receive DMA disabled */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);
#endif  /* LIN_USE_DMA */

                    /* Enable Receiver */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

#ifdef LIN_USE_DMA
                    /* Receive DMA enabled */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);
#endif  /* LIN_USE_DMA */

                    Lin_MscBuffer[u8Channel].u8Errors = 0U;

                    Lin_MscBuffer[u8Channel].State = LIN_MSC_READY;

                    break;
            }

                /* Get the MSC Channel state */
            MSC_State = Lin_MscBuffer[u8Channel].State;

        }

    }

    return MSC_State;

}

#ifdef MSC_RX_POLLING_MODE

/**
 * @brief   Msc_Polling
 * @details Tests the RDRF flag to know if something was received by
 *          the Channel with MSC functionality and in that case fill the
 *          buffer with the received data.
 *
 * @param[in] Channel - MSC to be initialized.
 * @param[out] Lin_SduPtr   Pointer to pointer to a shadow
 *                            buffer or memory mapped eSCI Hardware
 *                            receive buffer where the current data is
 *                            stored.
 *
 */
FUNC(void, LIN_CODE) Msc_Polling( CONST(uint8, AUTOMATIC) u8Channel)
    {
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    /* Check for invalid Channel */
    if (u8Channel >= LIN_HW_MAX_MODULES) /* Invalid Channel */
        {

#if (LIN_DEV_ERROR_DETECT == STD_ON)
        /* Report error to development error tracer */
        Det_ReportError((uint16)LIN_MODULE_ID,(uint8)0,(uint8)MSC_POLLING_ID,\
                (uint8)LIN_E_INVALID_CHANNEL);
#endif /* (LIN_DEV_ERROR_DETECT == STD_ON) */
        }
    else
        {

        if (((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u8Lin_MscPollingMode) && \
            ((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u8Lin_MscEnabled) \
           )
        {
            /* Get the hardware Lin Channel from logical Channel */
            u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;

            /* If something was received and there are no errors */
            /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
            if((ESCI_IFSR1_RDRF_MASK_U16 == (REG_READ16(ESCI_IFSR1(offset)) & ESCI_IFSR1_RDRF_MASK_U16)) && \
                (ESCI_SDR_ERR_MASK_U16 != (REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_ERR_MASK_U16)) \
              )
            {
                /* Update MSC Channel frame operation status to LIN_MSC_RUN */
                Lin_MscBuffer[u8Channel].State = LIN_MSC_RUN;

                /* No errors occurred on RX. */
                Lin_MscBuffer[u8Channel].u8Errors = 0U;

                /* Read the data from Data Register and store into the addressed Channel's Lin_MscBuffer */
                /*
            * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
            */
                Lin_MscBuffer[u8Channel].u8Data = (uint8)(REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_RD_TD_7_0_MASK_U16);

                /* Which is the MSC frame format ? */
                if (Lin_pChannelConfigPtr[u8Channel]->Lin_MscFrameFormat == LIN_MSC_16_BITS)
                {
                    /* Use 16-bit format (1 start bit, 12 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains 4-bit address field and 8 data bits. */
                    /* LSB is received first. */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    Lin_MscBuffer[u8Channel].u8Address = (uint8)(REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_RD_11_8_MASK_U16);
                }
                else
                {
                    /* Use 12-bit format (1 start bit, 8 data bits, 1 parity bit, 2 stop bits) */
                    /* The frame contains only 8 data bits. */
                    /* LSB is received first. */
                    Lin_MscBuffer[u8Channel].u8Address = 0U;
                }

                /* Clear Receive Data Register Full Interrupt Flag */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_RDRF_MASK_U16);
            }

            /* there is an error set the corresponding flag in the MSC buffer */
            else
            {

                /* An error occurred on RX: it can be an Overrun, Framing, Noise or Parity error. */
                Lin_MscBuffer[u8Channel].u8Errors = 1U;

                /* Check if OR Flag is set */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                if (ESCI_IFSR1_OR_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_OR_MASK_U16))
                {

                    /* Overrun Error flag */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_OR_MASK_U16);

                    Lin_MscBuffer[u8Channel].State = LIN_MSC_OVERRUN_ERROR;
                }

                /* Check if FE Flag is set */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                if (ESCI_IFSR1_FE_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_FE_MASK_U16))
                {
                    /* Framing Error flag */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                    Lin_MscBuffer[u8Channel].State = LIN_MSC_FRAMING_ERROR;
                }

                /* Check if NF Flag is set */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                if (ESCI_IFSR1_NF_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_NF_MASK_U16))
                {

                    /* Noise Error flag */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

                    Lin_MscBuffer[u8Channel].State = LIN_MSC_NOISE_ERROR;

                }

                /* Check if PF Flag is set */
                /*
                * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                */
                if (ESCI_IFSR1_PF_MASK_U16 == (REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_PF_MASK_U16))
                {

                    /* Parity Error flag */
                    /*
                    * @violates @ref Lin_NonASR_c_REF_5 Cast from unsigned long to pointer
                    */
                    REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_PF_MASK_U16);

                    Lin_MscBuffer[u8Channel].State = LIN_MSC_PARITY_ERROR;

                }

            }

        }

    }

    return;

}

#endif /* MSC_RX_POLLING_MODE */

#endif /* LIN_USE_MSC */
#define LIN_STOP_SEC_CODE
/**
* @violates @ref Lin_NonASR_c_REF_1 Precautions shall be taken in order to prevent the contents
* of a header file being included twice.
*
* @violates @ref Lin_NonASR_c_REF_4 #include statements in a file should only be preceded
* by other preprocessor directives or comments.
*/
 #include "MemMap.h"
 
#ifdef __cplusplus
}
#endif
/** @} */
