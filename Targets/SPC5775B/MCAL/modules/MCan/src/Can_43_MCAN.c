/**
*   @file    Can_43_MCAN.c
*   @implements Can.c_Artifact
*   @version 1.0.1
*   @file    Can.c
*   @implements Can_module
*
*   @brief   AUTOSAR MCan - module interface
*   @details API implementation for CAN driver.
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
* @section Can_43_MCAN_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Can_43_MCAN_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* here are different kinds of execution code sections.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Can_43_MCAN_c_REF_4
* Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used
* This violation is due to the structure of the types used.
*
* @section Can_43_MCAN_c_REF_5
* Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* The respective code could not be made static because of layers architecture design of the driver.
*
* @section Can_43_MCAN_c_REF_6
* Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between a pointer type and an integral type.
*
* @section Can_43_MCAN_c_REF_7
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
* is passed to  a macro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).
*
* @section Can_43_MCAN_c_REF_8
* Violates MISRA 2004 Required Rule 8.7, Global variables containing the generated configuration
* shall be defined in a separate source file and can't be defined inside a function although it is accessed
* by a single function.
*
* @section Can_43_MCAN_c_REF_9
* Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type
*
*@section Can_43_MCAN_c_REF_10
* Violates MISRA 2004 Required Rule 16.10, Ignore value is ignored as return value 
* is always the same and the value itself is not needed.
* 
*/


/*
Driver Limitations:
    1. The maximum number of Can_43_MCAN_DisableControllerInterrupts levels of nesting is 127. (variable "sint8" used for nesting level: -128 .. +127)
    2. This file contains 2 types of functions: first are the Autosar APIs and then are some user defined functions.
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/*
* @file           Can.c
*/
#include "Can_43_MCAN.h"
#include "Can_43_MCAN_IPW.h"
#include "CanIf_Cbk.h"
#include "Std_Types.h"

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*  (CAN111) Can.c shall check if the correct version of Can.h is included.
            This shall be done by a preprocessor check of the version numbers CAN_43_MCAN_SW_MAJOR_VERSION, CAN_43_MCAN_SW_MINOR_VERSION and CAN_43_MCAN_SW_PATCH_VERSION.
*/
/**
* @file           Can.c
*/
#define CAN_43_MCAN_VENDOR_ID_C                      43
#define CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_C       4
#define CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_C       0
#define CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_C    3
#define CAN_43_MCAN_SW_MAJOR_VERSION_C               1
#define CAN_43_MCAN_SW_MINOR_VERSION_C               0
#define CAN_43_MCAN_SW_PATCH_VERSION_C               1


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CAN header file are of the same vendor */
#if (CAN_43_MCAN_VENDOR_ID_C != CAN_43_MCAN_VENDOR_ID)
    #error "Can_43_MCAN.c and Can_43_MCAN.h have different vendor ids"
#endif
/* Check if current file and CAN header file are of the same Autosar version */
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_C    != CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_C    != CAN_43_MCAN_AR_RELEASE_MINOR_VERSION) || \
     (CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_C != CAN_43_MCAN_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Can_43_MCAN.c and Can_43_MCAN.h are different"
#endif
/* Check if current file and CAN header file are of the same Software version */
#if ((CAN_43_MCAN_SW_MAJOR_VERSION_C != CAN_43_MCAN_SW_MAJOR_VERSION) || \
     (CAN_43_MCAN_SW_MINOR_VERSION_C != CAN_43_MCAN_SW_MINOR_VERSION) || \
     (CAN_43_MCAN_SW_PATCH_VERSION_C != CAN_43_MCAN_SW_PATCH_VERSION))
    #error "Software Version Numbers of Can_43_MCAN.c and Can_43_MCAN.h are different"
#endif


/* Check if current file and CAN_IPW header file are of the same vendor */
#if (CAN_43_MCAN_VENDOR_ID_C != CAN_43_MCAN_IPW_VENDOR_ID_H)
    #error "Can_43_MCAN.c and Can_43_MCAN_IPW.h have different vendor ids"
#endif
/* Check if current file and CAN_IPW header file are of the same Autosar version */
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_C    != CAN_43_MCAN_IPW_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_C    != CAN_43_MCAN_IPW_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_C != CAN_43_MCAN_IPW_AR_RELEASE_REVISION_VERSION_H))
    #error "AutoSar Version Numbers of Can_43_MCAN.c and Can_43_MCAN_IPW.h are different"
#endif
/* Check if current file and CAN_IPW header file are of the same Software version */
#if ((CAN_43_MCAN_SW_MAJOR_VERSION_C != CAN_43_MCAN_IPW_SW_MAJOR_VERSION_H) || \
     (CAN_43_MCAN_SW_MINOR_VERSION_C != CAN_43_MCAN_IPW_SW_MINOR_VERSION_H) || \
     (CAN_43_MCAN_SW_PATCH_VERSION_C != CAN_43_MCAN_IPW_SW_PATCH_VERSION_H))
    #error "Software Version Numbers of Can_43_MCAN.c and Can_43_MCAN_IPW.h are different"
#endif

/* Check if current file and DET header file are of the same version */
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
  #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Can_43_MCAN.c and Det.h are different"
    #endif
  #endif
#endif

/* Check if current file and CANIF_CBK header file are of the same version */
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
  #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_C != CANIF_CBK_AR_RELEASE_MAJOR_VERSION) || \
         (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_C != CANIF_CBK_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Can_43_MCAN.c and CanIf_Cbk.h are different"
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

#define CAN_43_MCAN_START_SEC_VAR_INIT_UNSPECIFIED
/* @violates @ref Can_43_MCAN_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_43_MCAN_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"


#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)

/**
* @brief          This variable holds the state of the driver.
* @details        This variable holds the state of the driver. After reset is UNINIT. The output of Can_43_MCAN_Init() function
*                 (only to first call) should set this variable into READY state.
*                  CAN_43_MCAN_UNINIT = The CAN controller is not initialized. All registers belonging to the CAN module are in reset state, CAN interrupts are disabled.
*                  The CAN Controller is not participating on the CAN bus.
*                  The Can module must only implement a variable for the module state, when the development error tracing is switched on.
*                  When the development error tracing is switched off, the Can module does not need to implement this 'state machine',
*                  because the state information is only needed to check if Can_43_MCAN_Init was called prior to any Can module function.
*
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
VAR(Can_43_MCAN_StatusType, CAN_43_MCAN_VAR) Can_43_MCAN_eDriverStatus = CAN_43_MCAN_UNINIT;
#endif

/* Pointer to the current Driver Configuration (passed to the driver during initialization). Initialized by Can_43_MCAN_Init(). */
P2CONST(Can_43_MCAN_ConfigType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCAN_pCurrentConfig = NULL_PTR;
P2CONST(Can_43_MCAN_ControlerDescriptorType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCAN_pControlerDescriptors = NULL_PTR;
P2CONST(Can_43_MCANStatic_ControlerDescriptorType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCANStatic_pControlerDescriptors = NULL_PTR;
P2CONST(Can_43_MCANStatic_ConfigType, CAN_43_MCAN_VAR, CAN_43_MCAN_APPL_CONST) Can_43_MCANStatic_pCurrentConfig = NULL_PTR;
#define CAN_43_MCAN_STOP_SEC_VAR_INIT_UNSPECIFIED
/*
* @violates @ref Can_43_MCAN_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* @violates @ref Can_43_MCAN_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/

#include "MemMap.h"


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define CAN_43_MCAN_START_SEC_CODE
/*
* @violates @ref Can_43_MCAN_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* @violates @ref Can_43_MCAN_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/

#include "MemMap.h"


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/


/*================================================================================================*/


/*
(CAN252) The function Can_GetVersionInfo shall be pre compile time configurable (ON/Off) by the configuration parameter: CanVersionInfoApi
*/

#if (CAN_43_MCAN_VERSION_INFO_API == STD_ON)
/**
* @brief          Returns the version information of this module. SID is 0x07
* @details        This routine is called by:
*                - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      versioninfo A pointer to location to store version info
*                             Must be omitted if the function does not have parameters.
*
* @return         void
*
*
* @pre            The CAN_43_MCAN_VERSION_INFO_API define must be configured on.
* @post           The version information is return if the parameter versionInfo is not a null pointer.
*
* @implements     Can_43_MCAN_GetVersionInfo_Activity
* @api
*
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, CAN_43_MCAN_APPL_DATA) versioninfo)
{

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /*
    (CAN177) If development error detection for the Can module is enabled: The function Can_43_MCAN_GetVersionInfo shall
                 raise the error CAN_43_MCAN_E_PARAM_POINTER if the parameter versionInfo is a null pointer.
    */
    if ( NULL_PTR == versioninfo )
    {
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_GET_VERSION_INFO, (uint8)CAN_43_MCAN_E_PARAM_POINTER);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
        /*
        (CAN105) The function Can_43_MCAN_GetVersionInfo shall return the version information of this module. The version information
                     includes: Module Id, Vendor Id, Vendor specific version numbers.
        */
        versioninfo->vendorID         = (uint16)CAN_43_MCAN_VENDOR_ID;
        versioninfo->moduleID         = (uint16)CAN_43_MCAN_MODULE_ID;
        versioninfo->sw_major_version = (uint8)CAN_43_MCAN_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = (uint8)CAN_43_MCAN_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = (uint8)CAN_43_MCAN_SW_PATCH_VERSION;
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
}
#endif /* (CAN_43_MCAN_VERSION_INFO_API == STD_ON) */

/*================================================================================================*/
/**
* @brief          Initialize the CAN driver. SID is 0x00.
* @details        Initialize all the controllers.
*                 The CAN module shall be initialized by Can_43_MCAN_Init(<&Can_43_MCAN_Configuration>) service call during the start-up.
*                 This routine is called by:
*                - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Config Pointer to driver configuration.
*
* @return         void
*
*
* @pre            Can_43_MCAN_Init shall be called at most once during runtime.
* @post           Can_43_MCAN_Init shall initialize all the controllers and set the driver in READY state.
*
* @implements     Can_43_MCAN_Init_Activity
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*/
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_Init( P2CONST(Can_43_MCAN_ConfigType, AUTOMATIC, CAN_43_MCAN_APPL_CONST) Config)
{
    /* Variable for indexing the controllers. */
    VAR(uint8, AUTOMATIC) can_controller = 0U;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /*
       (CAN027) Detected development errors shall be reported to the Det_ReportError service of the Development Error Tracer (DET)
               if the pre-processor switch CanDevErrorDetection is set.
       (CAN083) If the CanDevErrorDetection switch is enabled API parameter checking is enabled.
       (CAN028)Development Errors call the Development Error Tracer when DET is switched on and the Can module detects an error.

    */
    if ( CAN_43_MCAN_READY == Can_43_MCAN_eDriverStatus )
    {
        /*
        (CAN247) The Can module environment shall call Can_43_MCAN_Init at most once during runtime.
        (CAN091) After return of the DET the Can module function that raised the development error shall return immediately.
        (CAN174) If development error detection for the Can module is enabled: The function Can_43_MCAN_Init shall raise the
                   error CAN_43_MCAN_E_TRANSITION if the driver is not in 'uninitialized' state.
        (CAN248) The function Can_43_MCAN_Init shall report the error CAN_43_MCAN_E_UNINIT, if Can_43_MCAN_Init was called prior to any Can module function.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_INIT, (uint8)CAN_43_MCAN_E_TRANSITION);
    }
    else
    {
#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_ON)

        /* Update config pointer with default configuration if precompile support on. */
        Can_43_MCAN_pCurrentConfig = (NULL_PTR == Config) ? &Can_43_MCAN_ConfigSet_PC : Config;
        Can_43_MCAN_pControlerDescriptors = Can_43_MCAN_pCurrentConfig->ControlerDescriptors;

#endif /* #if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_ON) */
#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_OFF)
        if (NULL_PTR == Config)       
        {
            /*
            (CAN175) If development error detection for the Can module is enabled: The function Can_43_MCAN_Init shall raise the
                       error CAN_43_MCAN_E_PARAM_POINTER if a NULL pointer was given as config parameter.
            */
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_INIT, (uint8)CAN_43_MCAN_E_PARAM_POINTER);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
#endif /* CAN_43_MCAN_PRECOMPILE_SUPPORT */

#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_OFF)
            /* Copy pointer to current Can Driver configuration. */
            Can_43_MCAN_pCurrentConfig = Config;
            Can_43_MCAN_pControlerDescriptors = Config->ControlerDescriptors;
#else
            /* Update config pointer with default configuration if precompile support on. */
            Can_43_MCAN_pCurrentConfig = (NULL_PTR == Config) ? &Can_43_MCAN_ConfigSet_PC : Config;
            Can_43_MCAN_pControlerDescriptors = Can_43_MCAN_pCurrentConfig->ControlerDescriptors;
        
#endif /* CAN_43_MCAN_PRECOMPILE_SUPPORT */
            Can_43_MCANStatic_pCurrentConfig = &Can_43_MCANStatic_ConfigSet;
            Can_43_MCANStatic_pControlerDescriptors = Can_43_MCANStatic_pCurrentConfig->StaticControlerDescriptors;

            /* Initialisation of usefull indicators. */
            Can_43_MCAN_IPW_InitVariables();

#if (STD_ON == CAN_43_MCAN_ENABLE_USER_MODE_SUPPORT)
    #ifdef CAN_43_MCAN_HAS_CONTROLLER_UNDER_REG_PROT
            Can_43_MCAN_IPW_SetUserAccessAllowed();
    #endif
#endif

            /* Loop through all Can controllers configured based CanControllerId parameter. */
            for ( can_controller = 0U; can_controller < (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured; can_controller++)
            {
                /* The initialization is skipped for the controllers that are not enabled. */
                /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                if ( CAN_43_MCAN_NULL_OFFSET != (Can_43_MCANStatic_pControlerDescriptors[can_controller].u8ControllerOffset))
                {
                    /* Init - ControllerState, uFirstHrhIndex, HthOffset, DefaultConfigIndex, u8MaxMBCount, Freeze controller and more ... */
                    /*
                       (CAN239) The function Can_43_MCAN_Init shall initialize all on-chip hardware resources that are used by the CAN controller.
                    */
                    Can_43_MCAN_IPW_Init( can_controller);

                    /*
                        (CAN250) The function Can_43_MCAN_Init shall initialize: static variables, including flags, Common setting for the
                               complete CAN HW unit, CAN controller specific settings for each CAN controller.
                       (CAN245) The function Can_43_MCAN_Init shall initialize all CAN controllers according to their configuration.
                       (CAN053) Can module/controller initalization - registers of CAN controller hardware resources that are not used.
                    */
                    /* @violates @ref Can_43_MCAN_c_REF_9 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */ 
                    /* @violates @ref Can_43_MCAN_c_REF_10 Violates MISRA 2004 Required Rule 16.10 , Ignore value is ignored as return value is always the same and the value itself is not needed.*/
                    Can_43_MCAN_IPW_ChangeBaudrate( can_controller);
                }
            }
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
            /*
              (CAN246) After initializing all controllers inside the HW Unit, the function Can_43_MCAN_Init shall change the module state to CAN_43_MCAN_READY.
            */
            Can_43_MCAN_eDriverStatus = CAN_43_MCAN_READY;
#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_OFF)
    #if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        }
    #endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
#endif /* # CAN_43_MCAN_PRECOMPILE_SUPPORT */   
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
}

#if (CAN_43_MCAN_CHANGE_BAUDRATE_API == STD_ON)
/*================================================================================================*/
/**
* @brief          Initialize the CAN controllers baudrate. SID is 0x0D.
* @details        Initialize the controller based on ID input parameter.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Controller Can controller to be initialized - based on configuration order list (CanControllerId).
* @param[in]      Baudrate Baudrate for which the controller shall be initialised.
*
* @retval         E_OK  request to change the Baudrate accepted.
* @retval         E_NOT_OK  request to change the Baudrate not accepted.
*
*
* @pre            Before controller re-initalization of baudrate the driver must be initialized and the controllers must be in Stop state.
* @post           Interrupts and MBs must be configured for respond to CAN bus.
*
* @implements     Can_43_MCAN_ChangeBaudrate_Activity
*
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*/
FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_ChangeBaudrate( VAR(uint8, AUTOMATIC) Controller, CONST(uint16, AUTOMATIC) Baudrate)
{
    /* Returns the result of change baudrate*/
    VAR(Std_ReturnType, AUTOMATIC) eReturnValue = (uint8)E_NOT_OK;
    VAR(uint8, AUTOMATIC) u8BaudrateIndex = 0U;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* If Can_43_MCAN_eDriverStatus is CAN_43_MCAN_UNINIT then the driver was not initialised yet. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN450) If development error detection for the Can module is enabled: The function Can_ChangeBaudrate shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CHANGE_BAUDRATE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        /* The Controller ID must be within range and the selected controller must be configured for use in the config tool. */

        if ( (Controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
        /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[Controller].u8ControllerOffset)) 
           )
        {
            /*
               (CAN452) If development error detection for the Can module is enabled: The function Can_ChangeBaudrate shall raise the
                       error CAN_43_MCAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CHANGE_BAUDRATE, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
            if ( CAN_43_MCAN_STOPPED != Can_43_MCAN_ControllerStatuses[Controller].ControllerState )
            {
                /*
                  (CAN453) If development error detection for the Can module is enabled: if the controller is not in state CANIF_CS_STOPPED,
                           the function Can_ChangeBaudrate shall raise the error CAN_43_MCAN_E_TRANSITION.
                  (CAN256) The Can module environment shall only call Can_ChangeBaudrate when the CAN controller is in state CANIF_CS_STOPPED.
                */
                    
                (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CHANGE_BAUDRATE, (uint8)CAN_43_MCAN_E_TRANSITION);
            }
            else
            {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

                /* Check the Baudrate */
                /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Advisory Rule 17.4 */
                for ( u8BaudrateIndex = 0U; u8BaudrateIndex < Can_43_MCAN_pControlerDescriptors[Controller].u8MaxBaudRateCount; u8BaudrateIndex++)
                {
                    /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Advisory Rule 17.4 */
                    if (Baudrate == (uint16)(Can_43_MCAN_pControlerDescriptors[Controller].pControllerBaudrateConfigsPtr[u8BaudrateIndex].u16ControllerBaudRate))
                    {
                        /* Baudrate is Valid */                                        
                        /* Copy the index of Valid Baudrate into the Can_43_MCAN_ControllerStatuses as u8CurrentBaudRateIndex */
                        Can_43_MCAN_ControllerStatuses[Controller].u8CurrentBaudRateIndex = u8BaudrateIndex;

                        eReturnValue = (uint8)E_OK;
                        break;
                    }
                }
                
                if ( (uint8)E_OK != eReturnValue )
                {
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
                    /*
                    (CAN451) If development error detection for the Can module is enabled: The function Can_ChangeBaudrate shall raise
                           the error CAN_43_MCAN_E_PARAM_BAUDRATE if the parameter Baudrate has an invalid value.
                    */
                            
                    (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CHANGE_BAUDRATE, (uint8)CAN_43_MCAN_E_PARAM_BAUDRATE);
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    /*
                      (CAN062) The function Can_ChangeBaudrate shall re-initialize the CAN controller and the controller specific settings.
                      (CAN255) The function Can_ChangeBaudrate shall only affect register areas that contain specific configuration for a single CAN controller.
                        */
                    Can_43_MCAN_IPW_ChangeBaudrate(Controller);
                }
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
            }
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
    return (eReturnValue);
}

/*================================================================================================*/
/**
* @brief          Check the CAN controllers Baudrate. SID is 0x0E.
* @details        Check the controller's configured baudrate.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Controller Can controller to be initialized - based on configuration order list (CanControllerId).
* @param[in]      Baudrate Baudrate for which the controller shall be initialised.
*
* @retval         E_OK  Baudrate is configred for the controller.
* @retval         E_NOT_OK  Baudrate is not configured for the controller.
*
*
* @pre            Before controller re-initalization the driver must be initialized.
* @post           Interrupts and MBs must be configured for respond to CAN bus.
*
* @implements     Can_43_MCAN_CheckBaudrate_Activity
*
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*/
FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_CheckBaudrate( VAR(uint8, AUTOMATIC) Controller, CONST(uint16, AUTOMATIC) Baudrate )
{
    /* Returns the result of check baudrate*/
    VAR(Std_ReturnType, AUTOMATIC) eReturnValue = (uint8)E_NOT_OK;
    VAR(uint8, AUTOMATIC) u8BaudrateIndex = 0U;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* If Can_43_MCAN_eDriverStatus is CAN_43_MCAN_UNINIT then the driver was not initialised yet. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN456) If development error detection for the Can module is enabled: The function Can_43_MCAN_CheckBaudrate shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CHECK_BAUDRATE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        /* The Controller ID must be within range and the selected controller must be configured for use in the config tool. */

        if ( (Controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
        /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[Controller].u8ControllerOffset)) 
           )
        {
            /*
               (CAN457) If development error detection for the Can module is enabled: The function Can_43_MCAN_CheckBaudrate shall raise the
                       error CAN_43_MCAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CHECK_BAUDRATE, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

            /* Check the Baudrate */
            /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Advisory Rule 17.4 */
            for ( u8BaudrateIndex = 0U; u8BaudrateIndex < Can_43_MCAN_pControlerDescriptors[Controller].u8MaxBaudRateCount; u8BaudrateIndex++)
            {
                /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Advisory Rule 17.4 */
                if (Baudrate == (uint16)(Can_43_MCAN_pControlerDescriptors[Controller].pControllerBaudrateConfigsPtr[u8BaudrateIndex].u16ControllerBaudRate))
                {
                    eReturnValue = (uint8)E_OK;
                    break;
                }
            }
                    
            if ( (uint8)E_OK != eReturnValue )                
            {
/* Invalid Baudrate */
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
                /*
                   (CAN458) If development error detection for the Can module is enabled: The function Can_43_MCAN_CheckBaudrate shall raise
                           the error CAN_43_MCAN_E_PARAM_BAUDRATE if the parameter Baudrate has an invalid value.
                */
                
                (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CHECK_BAUDRATE, (uint8)CAN_43_MCAN_E_PARAM_BAUDRATE);
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
            }

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
    return (eReturnValue);
}
#endif /* (CAN_43_MCAN_CHANGE_BAUDRATE_API == STD_ON) */

/*================================================================================================*/
/**
* @brief          Put the controller into a required state. SID is 0x03.
* @details        Switch the controller from one state to another.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Controller - Can controller for which the status shall be changed - based on configuration order list (CanControllerId).
* @param[in]      Transition - Possible transitions (CAN_T_STOP , CAN_T_START , CAN_T_SLEEP , CAN_T_WAKEUP)
* @return         Can_ReturnType  Result of the transition.
* @retval         CAN_OK   Transition initiated.
* @retval         CAN_NOT_OK  Development or production error.
*
*
* @pre            Before changing the controller state the driver must be initialized.
* @post           After the transition to the new state the interrupts required for that state must be enebaled.
*
* @implements     Can_43_MCAN_SetControllerMode_Activity
*
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*/
FUNC(Can_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_SetControllerMode( VAR(uint8, AUTOMATIC) Controller,
                                                      VAR(Can_StateTransitionType, AUTOMATIC) Transition 
                                                    )
{
    /* Returns the result of transition mode. */
    VAR(Can_ReturnType, AUTOMATIC)  eReturnValue = CAN_NOT_OK;

    /*
       (CAN089) The Can module environment shall indicate development errors only in the return values of a function of the Can module when DET
               is switched on and the function provides a return value. The returned value is CAN_NOT_OK.
    */
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* If Can_43_MCAN_pCurrentConfig is NULL_PTR then the Driver was not initialised yet. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN198) If development error detection for the Can module is enabled: if the module is not yet initialized, the
                   function Can_43_MCAN_SetControllerMode shall raise development error CAN_43_MCAN_E_UNINIT and return CAN_NOT_OK.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        /* Controller ID must be within range and the selected Controller must be configured for use in the config tool. */
        if ( (Controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
        /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[Controller].u8ControllerOffset)) 
           )
        {
            /*
               (CAN199) If development error detection for the Can module is enabled: if the parameter Controller is out of range,
                       the function Can_43_MCAN_SetControllerMode shall raise development error CAN_43_MCAN_E_PARAM_CONTROLLER and return CAN_NOT_OK.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_SET_CONTROLLER_MODE, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
            /* Call the IPW function for transition execution. */
            /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            /* @violates @ref Can_43_MCAN_c_REF_9 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */ 
            eReturnValue = (VAR(Can_ReturnType, AUTOMATIC))Can_43_MCAN_IPW_SetControllerMode( Controller, &(Can_43_MCAN_pCurrentConfig->ControlerDescriptors[Controller]), Transition,(boolean)TRUE);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT==STD_ON)  */

    return (eReturnValue);
}


/*================================================================================================*/
/**
* @brief          Disable INTs. SID is 0x04.
* @details        Switch OFF the controller's interrupts.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Controller Can controller for which interrupts shall be disabled - based on configuration order list (CanControllerId).
*
* @return         void
*
*
* @pre            Driver must be initalzied before changing the interrupts state (en or dis).
* @post           Controller must not respond to any interrupt assertion.
*
* @implements     Can_43_MCAN_DisableControllerInterrupts_Activity
*
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*/
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_DisableControllerInterrupts( VAR(uint8, AUTOMATIC) Controller)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* If Can_43_MCAN_pCurrentConfig is NULL_PTR then the driver was not initialised yet. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN205) If development error detection for the Can module is enabled: The function Can_43_MCAN_DisableControllerInterrupts shall
                   raise the error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_DISABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        /* The Controller ID must be within range and the selected Controller must be configured for use in the config tool. */
        if ( (Controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
        /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[Controller].u8ControllerOffset)) 
           )
        {
            /*
               (CAN206) If development error detection for the Can module is enabled: The function Can_43_MCAN_DisableControllerInterrupts shall
                       raise the error CAN_43_MCAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_DISABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
            /* Call the IPW function for disabling interrupts. */
            /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            Can_43_MCAN_IPW_DisableControllerInterrupts( Controller);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
}


/*================================================================================================*/
/**
* @brief          Enable INTs. SID is 0x05.
* @details        Switch ON the controller's interrupts.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Controller Can controller for which interrupts shall be disabled - based on configuration order list (CanControllerId).
*
* @return         void
*
*
* @pre            Driver must be initalzied before changing the interrupts state (en or dis).
* @post           Controller must respond to interrupt assertion.
*
* @implements     Can_43_MCAN_EnableControllerInterrupts_Activity
 * @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
 * @api
*/
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_EnableControllerInterrupts( VAR(uint8, AUTOMATIC) Controller)
{

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* If Can_43_MCAN_pCurrentConfig is NULL_PTR then the driver was not initialised yet. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN209) If development error detection for the Can module is enabled: The function Can_43_MCAN_EnableControllerInterrupts shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_ENABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        /* Controller ID must be within range and the selected Controller must be configured for use in the config tool. */
        if ( (Controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
         /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[Controller].u8ControllerOffset)) 
           )
        {
            /*
               (CAN210) If development error detection for the Can module is enabled: The function Can_43_MCAN_EnableControllerInterrupts shall
                       raise the error CAN_43_MCAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_ENABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
            /* Call the IPW function for enabling interrupts. */
            /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used  */
            Can_43_MCAN_IPW_EnableControllerInterrupts( Controller, &(Can_43_MCAN_pCurrentConfig->ControlerDescriptors[Controller]));
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
}


/*================================================================================================*/
/**
* @brief          Transmit information on CAN bus. SID is 0x06.
* @details        Can_43_MCAN_Write checks if hardware transmit object that is identified by the HTH is free.
*                    Can_43_MCAN_Write checks if another Can_43_MCAN_Write is ongoing for the same HTH.
*                     a) hardware transmit object is free:
*                         The mutex for that HTH is set to 'signaled' the ID, DLC and SDU are put in a format appropriate for
*                           the hardware (if necessary) and copied in the appropriate hardware registers or buffers.
*                        All necessary control operations to initiate the transmit are done.
*                         The mutex for that HTH is released. The function returns with CAN_OK.
*                    b) hardware transmit object is busy with another transmit request.
*                         The function returns with CAN_BUSY.
*                     c) A preemptive call of Can_43_MCAN_Write has been issued, that could not be handled reentrant (i.e. a call with the same HTH).
*                        The function returns with CAN_BUSY the function is non blocking
*                     d) The hardware transmit object is busy with another transmit request for an L-PDU that has lower priority than that for the current request
*                        The transmission of the previous L-PDU is cancelled (asynchronously).
*                        The function returns with CAN_BUSY.
*                   This routine is called by:
*                   - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Hth Information which HW-transmit handle shall be used for transmit.
*                 Implicitly this is also the information about the controller to use because the Hth numbers are unique inside one hardware unit.
* @param[in]      PduInfo Pointer to SDU user memory, DLC and Identifier.
* @return         Can_ReturnType   Result of the write operation.
* @retval         CAN_OK   Write command has been accepted.
* @retval         CAN_NOT_OK  Development error occured.
* @retval         CAN_BUSY   No of TX hardware buffer available or preemtive call of Can_43_MCAN_Write() that can't be implemented reentrant.
*
*
* @pre            Driver must be initialized and MB must be configured for Tx.
* @post           The data can be transmitted or rejected because of another data with a higher priority.
*
* @implements     Can_43_MCAN_Write_Activity
*
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*/
FUNC(Can_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_Write( VAR(Can_HwHandleType, AUTOMATIC) Hth,
                                          P2CONST(Can_PduType, AUTOMATIC, CAN_43_MCAN_APPL_CONST) PduInfo 
                                        )
{
    /* Variable for return status */
    VAR(Can_ReturnType, AUTOMATIC)  eReturnValue = CAN_NOT_OK;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* If Can_43_MCAN_pCurrentConfig is NULL_PTR then the driver was not initialised yet. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN216) If development error detection for the Can module is enabled: The function Can_43_MCAN_Write shall raise the error CAN_43_MCAN_E_UNINIT if
                   the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
        eReturnValue = CAN_NOT_OK;
    }
    else
    {
        /* Hth must be below uMessageBufferConfigCount and should be a Tx MB type. */
        if ( (Hth >= Can_43_MCAN_pCurrentConfig->u32CanMaxObjectId) ||
              (CAN_43_MCAN_TRANSMIT != (Can_43_MCAN_ObjType)Can_43_MCAN_pCurrentConfig->eObjectTypeMapping[Hth]) 
            )

        {
            /*
               (CAN217) If development error detection for the Can module is enabled: The function Can_43_MCAN_Write shall raise the error CAN_43_MCAN_E_PARAM_HANDLE
                       if the parameter Hth is not a configured Hardware Transmit Handle.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_WRITE, (uint8)CAN_43_MCAN_E_PARAM_HANDLE);
            eReturnValue = CAN_NOT_OK;
        }
        else
        {
            if ( (NULL_PTR == PduInfo) || (NULL_PTR == PduInfo->sdu) )
            {
                /*
                (CAN219) If development error detection for the Can module is enabled: The function Can_43_MCAN_Write shall raise the
                        error CAN_43_MCAN_E_PARAM_POINTER if the parameter PduInfo or the SDU pointer inside PduInfo is a null-pointer.
                */
                
                (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_WRITE, CAN_43_MCAN_E_PARAM_POINTER);
                eReturnValue = CAN_NOT_OK;
            }
            else
            {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

                            /* Call the IPW function for transmitting data. */
                            /* @violates @ref Can_43_MCAN_c_REF_9 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */ 
                            eReturnValue = (Can_ReturnType)Can_43_MCAN_IPW_Write(Hth,PduInfo);

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
            }
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
    return (eReturnValue);
}

/*================================================================================================*/
/*================================================================================================*/

#if (CAN_43_MCAN_TXPOLL_SUPPORTED == STD_ON)
    

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
/* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
        (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionWrite();
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}


#ifdef CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE
#if (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE==STD_ON)

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_0
/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_0( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(0U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif
#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_1
/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_1( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(1U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif
#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_2
/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_2( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(2U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_3


/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_3( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(3U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_4

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_4( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(4U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_5

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_5( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(5U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_6

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_6( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(6U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_7

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_7( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(7U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_8

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_8( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(8U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_9

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_9( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(9U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_WRITE_10

/**
* @brief          Function called at fixed cyclic time. SID is 0x01.
* @details        Service for performs the polling of TX confirmation and TX cancellation confirmation when CAN_TX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Send the data from that MB that is configured for Tx.
*
* @implements     Can_43_MCAN_MainFunction_Write_Activity
* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Write_10( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {       
        /*
           (CAN179) If development error detection for the module Can is enabled: The function Can_43_MCAN_MainFunction_Write shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_WRITE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */ 
        /* Poll all controllers for Tx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(10U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */     
}
#endif
#endif /*CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE==STD_ON*/
#endif /*ifdef (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_WRITE)*/
#endif /*(CAN_43_MCAN_TXPOLL_SUPPORTED == STD_ON)   */


/*================================================================================================*/

#if (CAN_43_MCAN_RXPOLL_SUPPORTED  == STD_ON)
   
/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionRead();
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}

#ifdef CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ
#if (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ == STD_ON)
#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_0    
/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_0( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(0U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_1
/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_1( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(1U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_2

/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_2( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(2U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif


#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_3
/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_3( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(3U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif


#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_4

/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_4( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(4U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif


#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_5

/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_5( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(5U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_6
/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_6( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(6U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_7 

/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_7( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(7U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_8

/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_8( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(8U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_9

/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_9( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(9U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif

#ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_10

/**
* @brief          Function called at fixed cyclic time.  SID is 0x08.
* @details        Service for performs the polling of RX indications when CAN_RX_PROCESSING is set to POLLING.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Receive the data from that MB that is configured for Rx.
*
* @implements     Can_43_MCAN_MainFunction_Read_Activity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Read_10( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {    
        /*
           (CAN181) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Read shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_READ, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
        /* Poll all controllers for Rx MB statuses. */
        Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(10U);
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}
#endif /*ifdef CAN_43_MCAN_MAINFUNCTION_PERIOD_READ_10*/
#endif /*(CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ == STD_ON)*/
#endif /* ifdef (CAN_43_MCAN_MAINFUNCTION_MULTIPLE_READ)*/
#endif /* (CAN_43_MCAN_RXPOLL_SUPPORTED == STD_ON) */


/*================================================================================================*/

#if (CAN_43_MCAN_BUSOFFPOLL_SUPPORTED == STD_ON)
/**
* @brief          Function called at fixed cyclic time. SID is 0x09.
* @details        Service for performs the polling of BusOff events that are configured statically as 'to be polled'.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Handle the Busoff event.
*
* @implements     Can_43_MCAN_MainFunction_BusOff_ACtivity
* @api
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_BusOff( void)
{
    /* Variable for indexing the controllers */
    VAR(uint8, AUTOMATIC) can_controller = 0U;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN184) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_BusOff shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_BUS_OFF, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
        /* Loop through all Can controllers configured based CanControllerId parameter. */
        for ( can_controller = (uint8)0U; can_controller < (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured; can_controller++)
        {
            /*
               (CAN109) The function Can_43_MCAN_MainFunction_BusOff shall perform the polling of bus-off events that are configured statically as 'to be polled'.
            */
/* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
            if ( (CAN_43_MCAN_NULL_OFFSET !=(Can_43_MCANStatic_pControlerDescriptors[can_controller].u8ControllerOffset))  &&
            /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                 ((CAN_43_MCAN_CONTROLLERCONFIG_BOPOL_EN_U32 & (uint32)(Can_43_MCANStatic_pControlerDescriptors[can_controller].u32Options)) != (uint32)0x0U)
               )
            {
                /* Check for BusOff status. */
                if ( (uint8)E_OK == Can_43_MCAN_IPW_CheckBusOff(can_controller) )
                {
                    /* Process BusOff event. */
                    /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
                    /* @violates @ref Can_43_MCAN_c_REF_9 Violates MISRA 2004 Required Rule 10.1 , prohibited Implicit Conversion: Non-constant argument to function, Implicit conversion of integer to smaller type */ 
                    if ( CAN_OK == (VAR(Can_ReturnType, AUTOMATIC))Can_43_MCAN_IPW_SetControllerMode( can_controller,  &(Can_43_MCAN_pCurrentConfig->ControlerDescriptors[can_controller]), CAN_T_STOP,(boolean)FALSE) )
                    {
                        Can_43_MCAN_IPW_ProcessBusOff(can_controller);
                        CanIf_ControllerBusOff(can_controller);
                    }

                }
            }
        }
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}

#endif /* (CAN_43_MCAN_BUSOFFPOLL_SUPPORTED == STD_ON) */

/*================================================================================================*/
/**
* @brief          Function called at fixed cyclic time. SIDis 0x0C.
* @details        Service for performs performs the polling of CAN status register flags to detect transition of CAN Controller state
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
* @post           Handle the transition of Can Controller state.
*
* @implements     Can_43_MCAN_MainFunction_Mode_Activity
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*/

FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_Mode( void)
{
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {            
        /*
           (CAN379) If development error detection for the Can module is enabled: The function Can_43_MCAN_MainFunction_Mode shall raise the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_MAIN_FUNCTION_MODE, (uint8)CAN_43_MCAN_E_UNINIT);             
    }
    else
    {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */       
        /* Check for main function mode. */
        Can_43_MCAN_IPW_MainFunctionMode();
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)        
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */    
}

/*================================================================================================*/
/**
* @brief          Process check of WakeUp condition. SID is 0x0B.
* @details        This service shall evaluate the WakeupSource parameter to get the information,
*                 which dedicate wakeup source needs to be checked, either a CAN transceiver or controller device.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      controller Can controller ID - based on configuration order list (CanControllerId).
* @return         Std_ReturnType Result of the wakeup verification.
* @retval         E_OK  Wakeup was detected for the given controller.
* @retval         E_NOT_OK  No wakeup was detected for the given controller.
*
*
* @pre            Driver must be initialized.
* @post           Return the Wakeup event occurence.
*
* @implements     Can_43_MCAN_CheckWakeup_Activity
* Compiler_Warning: This warning is thrown because it doesn't exist hardware support for Wakeup, and parameter "controller" it is not used.
* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* @api
*
*/

FUNC(Can_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_CheckWakeup( VAR(uint8, AUTOMATIC) controller)
{
    /* E_NOT_OK is defined as (uint8)0x01 */
    VAR(Can_ReturnType, AUTOMATIC) eReturnValue = CAN_NOT_OK;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test whether the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN362) If development error detection for the Can module is enabled: The function Can_43_MCAN_CheckWakeup shall raise
                   the error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CBK_CHECK_WAKEUP, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        /*
           (CAN363) If development error detection for the Can module is enabled: The function Can_43_MCAN_CheckWakeup shall raise the
                   error CAN_43_MCAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
        */
        if ( (controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
        /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[controller].u8ControllerOffset))
           )
        {
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_CBK_CHECK_WAKEUP, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

            eReturnValue = CAN_NOT_OK;    
                
    #if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

    return (eReturnValue);
}



/*================================================================================================*/

#if ((CAN_43_MCAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON))
/**
* @brief          Process a message buffer abort
* @details        This function write a abort code (b'1001) to MBCS[CODE] field of the MB.
*                This routine is called by:
*                - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      Hth - HW-transmit handler
*
*
* @pre            Driver must be initialized and the current MB transmission should be ready for transmit.
*
*
* @note           Not AUTOSAR required. This is user implementation.
* @implements     Can_43_MCAN_AbortMb_Activity
* @api
*
*/
 /* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_AbortMb( VAR(Can_HwHandleType, AUTOMATIC) Hth )
{

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test if the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_ABORT_MB, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        if ( (Hth >= Can_43_MCAN_pCurrentConfig->u32CanMaxObjectId) ||
             (CAN_43_MCAN_TRANSMIT != (Can_43_MCAN_ObjType)Can_43_MCAN_pCurrentConfig->eObjectTypeMapping[Hth])
           )

        {
            /*
            (CAN217) If development error detection for the Can module is enabled: The function Can_43_MCAN_Write shall raise the error CAN_43_MCAN_E_PARAM_HANDLE
                    if the parameter Hth is not a configured Hardware Transmit Handle.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_ABORT_MB, (uint8)CAN_43_MCAN_E_PARAM_HANDLE);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
        
            Can_43_MCAN_IPW_AbortMb(Hth);
            
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
}
#endif /* ((CAN_43_MCAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON)) */


/*================================================================================================*/

#if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)
/**
* @brief          Process a transition from one clock source to another.
* @details        This function is configuring Can controllers to run on the same baudrate, but having a different MCU source clock.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
* @param[in]      can_controller controller ID
* @param[in]      can_clk_mode clock mode selection
* @return         Std_ReturnType Result of the clock switch operation.
* @retval         E_OK  Switch clock operation was ok.
* @retval         E_NOT_OK  Switch clock operation was not ok.
*
*
* @pre            Driver must be initialized and all the controllers must be in Stop state.
*
*
* @note           Not AUTOSAR required. This is user implementation.
* @implements     Can_43_MCAN_SetClockMode_Activity
* @api
*
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_SetClockMode( VAR(uint8, AUTOMATIC) can_controller, VAR(Can_43_MCAN_ClockModeType, AUTOMATIC) can_clk_mode)
{
    /* Returns the result of CAN clock mode */
    VAR(Std_ReturnType, AUTOMATIC) eReturnValue = (uint8)E_NOT_OK;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* Test if the driver is already initialised. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_SETCLOCKMODE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        if ( (can_controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
         /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[can_controller].u8ControllerOffset)) 
           )
        {
            /*
               (CAN210) If development error detection for the Can module is enabled: The function Can_43_MCAN_EnableControllerInterrupts shall
                       raise the error CAN_43_MCAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
            */
            
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_ENABLE_CONTROLLER_INTERRUPTS, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

            if ( CAN_43_MCAN_STOPPED == Can_43_MCAN_ControllerStatuses[can_controller].ControllerState )
            {
                eReturnValue = Can_43_MCAN_IPW_SetClockMode( can_controller, can_clk_mode);
            }
            
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        
       }
    }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

    return (eReturnValue);
}

#endif /* CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON */
#ifdef CAN_43_MCAN_SUPPORT_MRAF_EVENT
  #if (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON)
    #if (CAN_43_MCAN_MRAFPOLL_SUPPORTED == STD_ON)
/**
* @brief          Do check Message RAM Access Failure event.
* @details        This is polling function to check whether Message RAM Access Failure.
*                 This routine is called by:
*                 - CanIf or an upper layer according to Autosar requirements.
*
*
* @pre            Driver must be initialized.
*
* @implements     Can_43_MCAN_MainFunction_CheckMRAF_Activity
* @api
*/
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_MainFunction_CheckMRAF( void)
{
    #if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        if ( CAN_43_MCAN_UNINIT != Can_43_MCAN_eDriverStatus )
        {
    #endif 
            Can_43_MCAN_IPW_MainFunction_CheckMRAF();
    #if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
        }
    #endif 
}
    #endif
  #endif /* (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_OFF) */
#endif /* defined(CAN_43_MCAN_SUPPORT_MRAF_EVENT) */
#ifdef CAN_43_MCAN_SET_BAUDRATE_API
#if (CAN_43_MCAN_SET_BAUDRATE_API == STD_ON)
/*================================================================================================*/
/**
* @brief         This function set baudrate 
* @details       This routine is called by an upper layer.
* 
* @param[in]     Controller controller ID
* @param[in]     BaudRateConfigID baudrateID selection
* 
* @return       
* @retval        E_OK  Switch baudrate operation was ok.
* @retval        E_NOT_OK  Switch baudrate operation was not ok.
* 
* @pre           Driver must be initialized.
* @implements    Can_43_MCAN_SetBaudrate_Activity
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(Std_ReturnType, CAN_43_MCAN_CODE) Can_43_MCAN_SetBaudrate( VAR(uint8, AUTOMATIC) Controller,
                                                CONST(uint16, AUTOMATIC) BaudRateConfigID
                                              )
{
    /* Returns the result of CAN set baudrate */
    VAR(Std_ReturnType, AUTOMATIC) eReturnValue = (uint8)E_NOT_OK;
    VAR(uint8, AUTOMATIC) u8BaudrateIndex = 0U;

#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    /* If Can_43_MCAN_eDriverStatus is CAN_43_MCAN_UNINIT then the driver was not initialised yet. */
    if ( CAN_43_MCAN_UNINIT == Can_43_MCAN_eDriverStatus )
    {
        /*
           (CAN450) If development error detection for the Can module is enabled: The function Can_ChangeBaudrate shall raise the
                   error CAN_43_MCAN_E_UNINIT if the driver is not yet initialized.
        */
            
        (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_SET_BAUDRATE, (uint8)CAN_43_MCAN_E_UNINIT);
    }
    else
    {
        /* The Controller ID must be within range and the selected controller must be configured for use in the config tool. */

        if ( (Controller >= (uint8)Can_43_MCANStatic_pCurrentConfig->u8ControllersConfigured) ||
        /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used */
             (CAN_43_MCAN_NULL_OFFSET == (Can_43_MCANStatic_pControlerDescriptors[Controller].u8ControllerOffset))
           )
        {
            /*
               (CAN452) If development error detection for the Can module is enabled: The function Can_ChangeBaudrate shall raise the
                       error CAN_43_MCAN_E_PARAM_CONTROLLER if the parameter Controller is out of range.
            */
                
            (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_SET_BAUDRATE, (uint8)CAN_43_MCAN_E_PARAM_CONTROLLER);
        }
        else
        {
            if ( CAN_43_MCAN_STOPPED != Can_43_MCAN_ControllerStatuses[Controller].ControllerState )
            {
                /*
                  (CAN453) If development error detection for the Can module is enabled: if the controller is not in state CANIF_CS_STOPPED,
                           the function Can_ChangeBaudrate shall raise the error CAN_43_MCAN_E_TRANSITION.
                  (CAN256) The Can module environment shall only call Can_ChangeBaudrate when the CAN controller is in state CANIF_CS_STOPPED.
                */
                        
                (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_SET_BAUDRATE, (uint8)CAN_43_MCAN_E_TRANSITION);
            }
            else
            {
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */

                /* Check the Baudrate */
                /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Advisory Rule 17.4 */
                for ( u8BaudrateIndex = 0U; u8BaudrateIndex < Can_43_MCAN_pControlerDescriptors[Controller].u8MaxBaudRateCount; u8BaudrateIndex++)
                {
                    /* Check the Baudrate */
                    /* @violates @ref Can_43_MCAN_c_REF_4 Violates MISRA 2004 Advisory Rule 17.4 */
                    if (BaudRateConfigID == (uint16)(Can_43_MCAN_pControlerDescriptors[Controller].pControllerBaudrateConfigsPtr[u8BaudrateIndex]. u16ControllerBaudRateConfigID))
                    {
                        /* Baudrate is Valid */                                        
                        /* Copy the index of Valid Baudrate into the Can_43_MCAN_ControllerStatuses as u8CurrentBaudRateIndex */
                        Can_43_MCAN_ControllerStatuses[Controller].u8CurrentBaudRateIndex = u8BaudrateIndex;

                        eReturnValue = (uint8)E_OK;
                        break;
                    }
                }
                
                if ( (uint8)E_OK != eReturnValue )
                {
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
                    /*
                    (CAN451) If development error detection for the Can module is enabled: The function Can_ChangeBaudrate shall raise
                        the error CAN_43_MCAN_E_PARAM_BAUDRATE if the parameter Baudrate has an invalid value.
                    */
                            
                    (void)Det_ReportError( (uint16)CAN_43_MCAN_MODULE_ID, (uint8)CAN_43_MCAN_INSTANCE, (uint8)CAN_43_MCAN_SID_SET_BAUDRATE, (uint8)CAN_43_MCAN_E_PARAM_BAUDRATE);
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
                }
                else
                {
                    /*
                      (CAN062) The function Can_ChangeBaudrate shall re-initialize the CAN controller and the controller specific settings.
                      (CAN255) The function Can_ChangeBaudrate shall only affect register areas that contain specific configuration for a single CAN controller.
                    */
                    Can_43_MCAN_IPW_ChangeBaudrate(Controller);
                }
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
            }
        }
   }
#endif /* (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON) */
    return (eReturnValue);
}
#endif
#endif

#ifdef ERR_IPV_MCAN_0002 
  #if (ERR_IPV_MCAN_0002 == STD_ON)
  /**
* @brief          This is dummy function to clear all data receive.
* @details        When Message RAM Access Failure occurred by e9145, the data received is invalid. 
* User can decide to use this function to clear all received messages.
*
* @pre            Driver must be initialized.
*   @implements Can_43_MCAN_DummyRead
'* @api
*/
/* @violates @ref Can_43_MCAN_c_REF_5 Violates MISRA 2004 Required Rule 8.10, external ... could be made static */
FUNC(void, CAN_43_MCAN_CODE) Can_43_MCAN_DummyRead( VAR(uint8, AUTOMATIC) u8Controller)
{
 #if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    if ( CAN_43_MCAN_UNINIT != Can_43_MCAN_eDriverStatus )
    {
 #endif
        Can_43_MCAN_IPW_DummyRead(u8Controller);
 #if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)       
    }
 #endif
}
  #endif
#endif


#define CAN_43_MCAN_STOP_SEC_CODE

/*
* @violates @ref Can_43_MCAN_c_REF_1 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives.
* @violates @ref Can_43_MCAN_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*/

#include "MemMap.h"


#ifdef __cplusplus
}
#endif


/** @} */
