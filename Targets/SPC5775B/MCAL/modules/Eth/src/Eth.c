/**
*   @file    Eth.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Eth driver interface.
*   @details This file contains implementation of the AUTOSAR Ethernet driver
*            and provides whole API except the interrupt handlers.
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

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Eth_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, #include statements should only be
* preceded by other preprocessor directives or comments.
* The usage of the MemMap.h file violates this advisory rule, but this
* mechanism is used to properly place the code and variables into their
* sections.
*
* @section Eth_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file. Precautions
* shall be taken in order to prevent the contents of a header file being
* included twice. This is an approved violation
* of usage MemMap.h file used to create linkage sections.
*
* @section Eth_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, A compiler/linker shall be checked to
* ensure that 31 character significance and case sensitivity are supported for 
* external identifiers. Name length of the macros is unfortunately longer than 
* 31 characters which is required by  the agreed macro format and cannot be 
* changed. 
*
* @section Eth_c_REF_4
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only
* allowed form of pointer arithmetic. Array indexing shall only be applied
* to objects defined as an array type. Handling with pointer without explicit
* length is defined by AUTOSAR specification. But the length of MAC address
* is strictly six bytes and used index is never out of the bounds.
*
* @section Eth_c_REF_5
* Violates MISRA 2004 Required Rule 13.7, Boolean operations whose results
* are invariant shall not be permitted. This condition is invariant only for
* PreCompile variant where is this behavior expected.
*
* @section Eth_c_REF_6
* Violates MISRA 2004 Required Rule 1.2, No reliance shall be placed
* on undefined or unspecified behavior. This rely to using of pointer to
* variable on stack. In this case is ensured that a local variable and its
* address is used only in the valid content.
*
* @section Eth_c_REF_7
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless
* external linkage is required. The APIs always require the external
* linkage. MISRA analysis tool does not see the linkage from upper layers
* therefore there is no violation.
*
* @section Eth_c_REF_8
* Violates MISRA 2004 Required Rule 17.4, Array indexing shall be the only
* allowed form of pointer arithmetic. The MISRA analysis tool reports this
* violation badly if array of pointers is accessed  even with the array
* indexing arithmetics - this is used in a post build configuration variant
* to access the configuration parameters. It is no violation but the tool
* bug however it must be documented anyway.
*
* @section Eth_c_REF_9
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless
* external linkage is required. This is aimed to be GLOBAL variable.
* MISRA analysis tool does not see the linkage from upper layers
* therefore there is no violation.
*
* @section Eth_c_REF_10
* Violates MISRA 2004 Required Rule 5.1, Identifiers shall not rely on the significance of more
* than 31 characters. Name length of the macros is unfortunately longer than 31 characters 
* which is required by the agreed macros format and cannot be changed. 
*
* @section Eth_c_REF_11
* Violates MISRA 2004 Required Rule 11.1, Pointer to a function shall not be converted to anything
* else than integral type. This rule is not violated however the tool used for checks reports it
* therefore it must be commented here.
*
* @section Eth_c_REF_14
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
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Eth.h" /* Includes also Eth_GeneralTypes.h, Eth_Cfg.h,  
                    Eth_ComStack_Types.h, Dem.h, Det.h and Mcal.h */
#include "Eth_Ipw.h"     /* LLD driver API */

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define ETH_VENDOR_ID_C                      43
#define ETH_AR_RELEASE_MAJOR_VERSION_C       4
#define ETH_AR_RELEASE_MINOR_VERSION_C       0
/** @violates @ref Eth_c_REF_3 MISRA rule 1.4 
* @violates @ref Eth_c_REF_10 MISRA rule 5.1  */
#define ETH_AR_RELEASE_REVISION_VERSION_C    3
#define ETH_SW_MAJOR_VERSION_C               1
#define ETH_SW_MINOR_VERSION_C               0
#define ETH_SW_PATCH_VERSION_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and ETH header file are of the same vendor */
#if(ETH_VENDOR_ID_C != ETH_VENDOR_ID)
    #error "Eth.c and Eth.h have different vendor ids"
#endif
/* Check if current file and ETH header file are of the same Autosar version */
#if((ETH_AR_RELEASE_MAJOR_VERSION_C    != ETH_AR_RELEASE_MAJOR_VERSION) || \
     (ETH_AR_RELEASE_MINOR_VERSION_C    != ETH_AR_RELEASE_MINOR_VERSION) || \
     (ETH_AR_RELEASE_REVISION_VERSION_C != ETH_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Eth.c and Eth.h are different"
#endif
/* Check if current file and ETH header file are of the same Software version */
#if((ETH_SW_MAJOR_VERSION_C != ETH_SW_MAJOR_VERSION) || \
     (ETH_SW_MINOR_VERSION_C != ETH_SW_MINOR_VERSION) || \
     (ETH_SW_PATCH_VERSION_C != ETH_SW_PATCH_VERSION))
    #error "Software Version Numbers of Eth.c and Eth.h are different"
#endif
/* Check if current file and Eth_LLD header file are of the same Autosar version */
#if ((ETH_AR_RELEASE_MAJOR_VERSION_C    != ETH_AR_RELEASE_MAJOR_VERSION_ETHIPW_H) || \
     (ETH_AR_RELEASE_MINOR_VERSION_C    != ETH_AR_RELEASE_MINOR_VERSION_ETHIPW_H) || \
     (ETH_AR_RELEASE_REVISION_VERSION_C != ETH_AR_RELEASE_REVISION_VERSION_ETHIPW_H))
    #error "AutoSar Version Numbers of Eth.c and Eth_Ipw.h are different"
#endif
/* Check if current file and Eth_LLD header file are of the same Software version */
#if ((ETH_SW_MAJOR_VERSION_C != ETH_SW_MAJOR_VERSION_ETHIPW_H) || \
     (ETH_SW_MINOR_VERSION_C != ETH_SW_MINOR_VERSION_ETHIPW_H) || \
     (ETH_SW_PATCH_VERSION_C != ETH_SW_PATCH_VERSION_ETHIPW_H))
    #error "Software Version Numbers of Eth.c and Eth_Ipw.h are different"
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
/** @violates @ref Eth_c_REF_3 MISRA rule 1.4 
* @violates @ref Eth_c_REF_10 MISRA rule 5.1  */
#define ETH_START_SEC_VAR_INIT_UNSPECIFIED
/**
 * @violates @ref Eth_c_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"
/**
* @brief         State of the Eth module
* @details       Used to store state of the Ethernet controller driver i.e Eth
*                module. It is initialized to ETH_STATE_UNINIT
*/
/** @violates @ref Eth_c_REF_9 MISRA rule 8.10 */
VAR(volatile Eth_StateType, ETH_VAR) Eth_CtrlState[ETH_MAXCTRLS_SUPPORTED] = {ETH_STATE_UNINIT};

/** @violates @ref Eth_c_REF_3 MISRA rule 1.4 
* @violates @ref Eth_c_REF_10 MISRA rule 5.1  */
#define ETH_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
 * @violates @ref Eth_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_c_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"

#if STD_ON == DEBUG_VARIABLES
#define ETH_START_SEC_VAR_INIT_32
/**
 * @violates @ref Eth_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_c_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"
/**
* @brief         Debug variable counting receive buffer ring overflows
* @details       Debug variable used to count events of receive buffer ring
*                overflow due to reception of too long frame which does not fit
*                into the whole ring.
*/
VAR(uint32, ETH_VAR) Eth_RxBuffersOverflow[ETH_MAXCTRLS_SUPPORTED] = {0U};
/**
* @brief         Debug variable counting MII transactions finished too late
* @details       Debug variable incremented each time when MII transaction is
*                not finished successfully
*/
VAR(uint32, ETH_VAR) Eth_MiiFailed[ETH_MAXCTRLS_SUPPORTED] = {0U};
#define ETH_STOP_SEC_VAR_INIT_32
/**
 * @violates @ref Eth_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_c_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"
#endif 


/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define ETH_START_SEC_CODE
/**
 * @violates @ref Eth_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_c_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
* @brief         Initializes the Ethernet Driver
* @details       Passed configuration pointer is internally stored and
*                the driver is initialized. The Ethernet controller is not
*                touched.
* @note          Function should be called only once.
* @warning       Second call can cause undefined behavior.
*                Call the Eth_SetControllerMode() and pass ETH_MODE_DOWN to
*                the CtrlMode argument before the second Eth_Init call to avoid
*                problems.
* @api
* @param[in]     CfgPtr Points to the implementation specific structure containing
*                the Eth driver configuration
* Compiler_Warning: this warning due to behavior of compiler depend on configs. 
* @implements    Eth_Init_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(void, ETH_CODE) Eth_Init(P2CONST(Eth_ConfigType, AUTOMATIC, ETH_APPL_CONST) CfgPtr)
{
    VAR(uint8, AUTOMATIC) u8CtrlCount;
   
#if STD_ON == ETH_DEV_ERROR_DETECT   
    #if VARIANT_PRE_COMPILE != ETH_CONFIG_VARIANT
        if(NULL_PTR == CfgPtr)
        {           
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_INIT, \
                ETH_E_INV_POINTER \
                                  );
        }    
    #else 
        if(NULL_PTR != CfgPtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_INIT, \
                ETH_E_INV_POINTER \
                                  );
        }
    #endif /* VARIANT-PRE-COMPILE */
        else
        {   
#endif /* ETH_DEV_ERROR_DETECT  */
            /* Set the state to ETH_STATE_UNINIT before doing any changes to
               ensure that any preempting function (interrupt handler) will
               correctly stop its execution even if the state had been 
               ETH_STATE_ACTIVE when the Eth_Init was called. */
            for (u8CtrlCount=0U; u8CtrlCount < (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED; u8CtrlCount++)
            {
                Eth_CtrlState[u8CtrlCount] = ETH_STATE_UNINIT;
            }
            
    #if VARIANT_PRE_COMPILE != ETH_CONFIG_VARIANT
            /* Store the configuration pointer to internal global variable 
            for future usage */
            Eth_InternalCfgPtr = CfgPtr;

    #endif

            for (u8CtrlCount=0U; u8CtrlCount < (VAR(uint8, AUTOMATIC))ETH_MAX_CONTROLLER_CFG; u8CtrlCount++)
            {               
                Eth_CtrlState[u8CtrlCount] = ETH_STATE_INIT;
            }
    #if STD_ON == ETH_DEV_ERROR_DETECT
        }
    #endif /* ETH_DEV_ERROR_DETECT  */
}

/*================================================================================================*/
/**
* @brief         Initializes the given controller
* @details       The Eth Controller is reset (i.e. immediately stopped) and
*                configured according to the requested configuration. Debug
*                variables and Eth counters are cleared. Receive and transmit
*                buffers are initialized.
* @warning       Unexpected call of this function can disturb will immediately
*                stop receiver and transmitter thus disturbing any existing
*                communication.
* @api
* @param[in]     CtrlIdx Index of the controller to be initialized.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[in]     CfgIdx Index of the used configuration.
* @return        Error status
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error or inaccessible controller was
*                detected and the function failed.
* Compiler_Warning: this warning due to behavior of compiler depend on configs.
* @implements    Eth_ControllerInit_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(Std_ReturnType, ETH_CODE) Eth_ControllerInit(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(uint8, AUTOMATIC) CfgIdx)
{
    /* Variable used to track the function execution success status */
    VAR(Std_ReturnType, AUTOMATIC) u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC)) E_NOT_OK;

    /* Compiler_Warning: The parameter CfgIdx is not used any more and requirement SWS_ETH_00038 was rejected. */
    (void) CfgIdx;
#if STD_ON == ETH_DEV_ERROR_DETECT
  #if (VARIANT_PRE_COMPILE != ETH_CONFIG_VARIANT)
      /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
    if (CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
  #else
    /* Compiler_Warning: this warning due to a protection when ETH_MAXCTRLS_SUPPORTED is greater than 1. However, this lead to 
    warnings when only a controller is used. */
    /** @violates @ref Eth_c_REF_5 MISRA rule 13.7 */
    if ((CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED) || (CtrlIdx > ETH_MAX_CTRLIDX_PC) || (CtrlIdx < ETH_MIN_CTRLIDX_PC))
  #endif
    {       
            (void)Det_ReportError( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_CONTROLLERINIT, ETH_E_INV_CTRL_IDX \
                                 );
    }
    else
    {
        if(ETH_STATE_UNINIT == Eth_CtrlState[CtrlIdx])
        {           
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_CONTROLLERINIT, ETH_E_NOT_INITIALIZED \
                                  );
        }
        else
        {
            #if (VARIANT_PRE_COMPILE != ETH_CONFIG_VARIANT)
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                if (NULL_PTR == Eth_InternalCfgPtr->pController[CtrlIdx])
                {
                    (void)Det_ReportError( \
                        (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                        ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                        ETH_SID_CONTROLLERINIT, ETH_E_INV_CTRL_IDX \
                                         );
                }
                else
                {
            #endif
#endif /* ETH_DEV_ERROR_DETECT  */
                    /* Set the state to ETH_STATE_INIT before doing any changes to
                    ensure that any preempting function (interrupt handler) will
                    correctly stop its execution even if the state had been 
                    ETH_STATE_ACTIVE when the Eth_ControllerInit was called. */
                    Eth_CtrlState[CtrlIdx] = ETH_STATE_INIT;
                    /* Try to reset the controller */
                    Eth_Ipw_ResetController(CtrlIdx);
                    /*  Check whether the controller is available */
                    if(((VAR(boolean, AUTOMATIC))TRUE) == Eth_Ipw_CheckAccessToController(CtrlIdx))
                    {
                        Eth_Ipw_ConfigureController(CtrlIdx);
                        Eth_Ipw_ClearCounters(CtrlIdx);
                        Eth_Ipw_ConfigureRxBuffers(CtrlIdx); 
                        Eth_Ipw_ConfigureTxBuffers(CtrlIdx);
                        /* Only when debug variables are used */
                        #if STD_ON == DEBUG_VARIABLES
                            /* Clear debug variables */ 
                            Eth_RxBuffersOverflow[CtrlIdx] = 0U;
                            Eth_MiiFailed[CtrlIdx] = 0U;
                        #endif                     
                        /* Set controller to active state */
                        Eth_CtrlState[CtrlIdx] = ETH_STATE_ACTIVE; 
                        u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC))E_OK;
                    }
                    else
                    {
                        /* No, the controller is not available, report an error */
                      #if(STD_ON == ETH_DEM_EVENT_DETECT)
                        /**
                        * @violates @ref Eth_c_REF_5 MISRA rule 13.7
                        * @violates @ref Eth_c_REF_8 MISRA rule 17.4 */
                        /** @violates @ref Eth_c_REF_14 MISRA rule 14.1 */
                        if((VAR(uint32, AUTOMATIC))STD_ON == (VAR(uint32, AUTOMATIC))ETH_CFG_DEM_E_ACCESS_ENABLED(CtrlIdx))
                        {
                            /** @violates @ref Eth_c_REF_8 MISRA rule 17.4 */
                            Dem_ReportErrorStatus   ( \
                                (VAR(Dem_EventIdType, AUTOMATIC)) \
                                ETH_CFG_DEM_E_ACCESS(CtrlIdx), \
                                DEM_EVENT_STATUS_FAILED \
                                                    );
                        }
                      #endif
                    Eth_CtrlState[CtrlIdx] = ETH_STATE_INIT;
                    }
#if STD_ON == ETH_DEV_ERROR_DETECT
            #if (VARIANT_PRE_COMPILE != ETH_CONFIG_VARIANT)
                }
            #endif
        }
    }
#endif /* ETH_DEV_ERROR_DETECT  */
    return u8FunctionSuccess;
}
/*================================================================================================*/
/**
* @brief         Enables or disables the given controller
* @warning       Disabling the controller clears all receive and transmit
*                buffers. The application should ensure that no data is lost.
* @api
* @param[in]     CtrlIdx Index of the controller to be enabled or disabled.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[in]     CtrlMode Mode which shall be entered
*                - ETH_MODE_DOWN: disable the controller
*                - ETH_MODE_ACTIVE: enable the controller
* @return        Error status
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error was detected and the function
*                failed.
* @implements    Eth_SetControllerMode_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(Std_ReturnType, ETH_CODE) Eth_SetControllerMode(VAR(uint8, AUTOMATIC) CtrlIdx, VAR(Eth_ModeType, AUTOMATIC) CtrlMode)
{
    VAR(Std_ReturnType, AUTOMATIC) u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC))E_NOT_OK; /* Variable used to track the
                                           function execution success status */
                                           
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {        
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
            ETH_SID_SETCONTROLLERMODE, ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
        {     
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_SETCONTROLLERMODE, ETH_E_NOT_INITIALIZED \
                                  );
        }
        else
        {
    #endif /* ETH_DEV_ERROR_DETECT  */
            if(ETH_MODE_ACTIVE == CtrlMode)
            {
                Eth_Ipw_EnableController(CtrlIdx);
            }
            else
            {
                Eth_Ipw_DisableController(CtrlIdx);
            }
            u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC))E_OK;
    #if STD_ON == ETH_DEV_ERROR_DETECT
        }
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
    return u8FunctionSuccess;
}

/*================================================================================================*/
/**
* @brief         Obtains the mode of the given controller
* @api
* @param[in]     CtrlIdx Index of the controller which state shall be read.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[out]    CtrlModePtr Pointer where to store the current controller mode.
* @return        Error status
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error was detected and the function
*                failed.
* @implements    Eth_GetControllerMode_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(Std_ReturnType, ETH_CODE) Eth_GetControllerMode( \
                            VAR(uint8, AUTOMATIC) CtrlIdx, \
                            P2VAR(Eth_ModeType, AUTOMATIC, ETH_APPL_DATA) CtrlModePtr \
                                                    )
{
    VAR(Std_ReturnType, AUTOMATIC) u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC))E_NOT_OK; /* Variable used to track
                                      the function execution success status */

    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
            ETH_SID_GETCONTROLLERMODE, ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
       if(NULL_PTR == CtrlModePtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_GETCONTROLLERMODE, ETH_E_INV_POINTER \
                                  );

        }
        else
        {
           if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_GETCONTROLLERMODE, ETH_E_NOT_INITIALIZED \
                                      );
            }
            else
            {
    #endif /* ETH_DEV_ERROR_DETECT  */
                * CtrlModePtr = Eth_Ipw_CheckControllerIsActive(CtrlIdx);
                u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC))E_OK;
    #if STD_ON == ETH_DEV_ERROR_DETECT
            }
        }
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
    return u8FunctionSuccess;
}
  
/*================================================================================================*/
/**
* @brief         Obtains the physical source address used by the indexed
*                controller (the node MAC address).
* @api
* @param[in]     CtrlIdx Index of the controller which MAC address should be
*                read. The index is valid within the context of the Ethernet
*                Driver only.
* @param[out]    PhysAddrPtr Pointer where to store physical source address
*                (MAC address). The address in network byte order is stored into
*                6 bytes at the given memory address.
* @implements    Eth_GetPhysAddr_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(void, ETH_CODE) Eth_GetPhysAddr(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr)
{
    VAR(uint32, AUTOMATIC) u32AddressHolder; /* Used to hold the addres value */
    
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_GETPHYSADDR, \
            ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(NULL_PTR == PhysAddrPtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_GETPHYSADDR, ETH_E_INV_POINTER \
                                  );

        }
        else
        {
           if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_GETPHYSADDR, ETH_E_NOT_INITIALIZED \
                                      );
            }
            else
            {
    #endif /* ETH_DEV_ERROR_DETECT  */
                /* Get the first four bytes of the address */
                u32AddressHolder = Eth_Ipw_GetPhysicalAddressLow(CtrlIdx);
                /* Saved as four uint8 values instead of one uint32 value 
                   because the proper uint32 alignment is not ensured by the 
                   function prototype 
                */                
                /* Store the LSB */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                *(PhysAddrPtr + 3U) = (VAR(uint8, AUTOMATIC))(u32AddressHolder & 0xFFU);
                u32AddressHolder = u32AddressHolder >> 8U; /* Prepare the next bit */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                *(PhysAddrPtr + 2U) = (VAR(uint8, AUTOMATIC))(u32AddressHolder & 0xFFU);
                u32AddressHolder = u32AddressHolder >> 8U; /* Prepare the next bit */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                *(PhysAddrPtr + 1U) = (VAR(uint8, AUTOMATIC))(u32AddressHolder & 0xFFU);
                u32AddressHolder = u32AddressHolder >> 8U; /* Prepare the next bit */
                /* Store the MSB */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                *(PhysAddrPtr + 0U) = (VAR(uint8, AUTOMATIC))(u32AddressHolder & 0xFFU);
                /* Get the last two bytes of the address */
                u32AddressHolder = Eth_Ipw_GetPhysicalAddressHigh(CtrlIdx);
                /* Saved as four uint8 values instead of one uint32 value 
                   because the proper uint16 alignment is not ensured by the 
                   function prototype 
                */                
                /* Store the LSB */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                *(PhysAddrPtr + 5U) = (VAR(uint8, AUTOMATIC))(u32AddressHolder & 0xFFU);
                u32AddressHolder = u32AddressHolder >> 8U; /* Prepare the next bit */
                /* Store the MSB */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                *(PhysAddrPtr + 4U) = (VAR(uint8, AUTOMATIC))(u32AddressHolder & 0xFFU);
    #if STD_ON == ETH_DEV_ERROR_DETECT
            }      
        }  
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
}  

/*================================================================================================*/
/**
* @brief         Set or change physical address to the defined controller.
* @api
* @param[in]     CtrlIdx Index of the controller which PHY address should be
*                changed. The index is valid within the context of the Ethernet
*                Driver only.
* @param[in]     PhysAddrPtr Pointer to PHY address which should be set to
*                the controller. The address is stored in 6 bytes of memory
*                in network byte order.
* @caution       This function may be called only when the controller is down.
*                Call of function Eth_ControllerInit change MAC address
*                to the default value!
* @implements    Eth_SetPhysAddr_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(void, ETH_CODE) Eth_SetPhysAddr(VAR(uint8, AUTOMATIC) CtrlIdx, P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr)
{
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_SETPHYSADDR, \
            ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(NULL_PTR == PhysAddrPtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_SETPHYSADDR, ETH_E_INV_POINTER \
                                  );

        }
        else
        {
           if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_SETPHYSADDR, ETH_E_NOT_INITIALIZED \
                                      );
            }
            else
            {
    #endif /* ETH_DEV_ERROR_DETECT  */
                (void)Eth_Ipw_SetPhysAddr(CtrlIdx, PhysAddrPtr);
    #if STD_ON == ETH_DEV_ERROR_DETECT
            }
        }
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
}


#if STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER
/*================================================================================================*/
/**
* @brief         Adds or removes the specific @c PhysAddrPtr address to or from
*                a multicast address pool at controller specified by @c CtrlIdx
*                index.
* @api
* @details       Enables or disables reception for specified unicast
*                physical address.
*                Operations for special Physical addresses follow.
*                If Physical Address ff:ff:ff:ff:ff:ff is added into a filter
*                (Action=ETH_ADD_TO_FILTER) the filter is completely open
*                and any address is accepted at reception. Later on when
*                Physical Address ff:ff:ff:ff:ff:ff is removed from the filter
*                (Action=ETH_REMOVE_FROM_FILTER) the filtering is recovered
*                and the reception is allowed again only for addresses remaining
*                in the filter.
*                If Physical Address 00:00:00:00:00:00 is added into a filter,
*                no matter whether action is ETH_ADD_TO_FILTER
*                or ETH_REMOVE_FROM_FILTER,
*                the filter is completely closed and all items from table
*                are removed.
*                Note that operations of full open or close are in exclusive
*                disjunction. Operation of full open excludes full close and
*                vice versa.
* @param[in]     CtrlIdx Index of the controller. The index is valid within
*                the context of the Ethernet Driver only.
* @param[in]     PhysAddrPtr Pointer to PHY address which shall be added
*                or removed to or from multicast pool.
*                The address in network byte order stored into 6 bytes of
*                memory.
* @param[in]     Action Determine whenever the defined address will be added
*                to the pool ETH_ADD_TO_FILTER or removed from it
*                ETH_REMOVE_FROM_FILTER.
* @implements    Eth_UpdatePhysAddrFilter_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(Std_ReturnType, ETH_CODE) Eth_UpdatePhysAddrFilter ( \
                                VAR(uint8, AUTOMATIC) CtrlIdx, \
                                P2CONST(uint8, AUTOMATIC, ETH_APPL_CONST) PhysAddrPtr, \
                                VAR(Eth_FilterActionType, AUTOMATIC) Action \
                                                        )
{
    VAR(Std_ReturnType, AUTOMATIC) eReturnStatus = (VAR(Std_ReturnType, AUTOMATIC))E_NOT_OK;

    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
          (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, ETH_DRIVER_INSTANCE, \
          (VAR(uint8, AUTOMATIC)) ETH_SID_UPDATEADDRFILTER, \
          ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(NULL_PTR == PhysAddrPtr)
        {           
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_UPDATEADDRFILTER, ETH_E_INV_POINTER \
                                  );

        }
        else
        {
           if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_UPDATEADDRFILTER, ETH_E_NOT_INITIALIZED \
                                      );
            }
            else
            {
    #endif /* ETH_DEV_ERROR_DETECT  */
                Eth_Ipw_UpdatePhysAddrFilter(CtrlIdx, PhysAddrPtr, Action);
                /* Check whenever is added multicast address. I/G bit is set */
                if(1U == (*(PhysAddrPtr) & 1U))
                {
                    eReturnStatus = (VAR(Std_ReturnType, AUTOMATIC))E_OK;
                }
    #if STD_ON == ETH_DEV_ERROR_DETECT
            }
        }
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
    return eReturnStatus;
}

#endif /* STD_ON == ETH_UPDATE_PHYS_ADDR_FILTER */


#if STD_ON == ETH_CTRLENABLE_MII

/*================================================================================================*/
/**
* @brief         Writes to a transceiver (physical layer driver) register.
* @details       The management frame is assembled and the MII bus transaction
*                is issued in order to transfer the data. Function waits until
*                the bus transaction finishes.
* @warning       This function is blocking the execution until the MII bus
*                transaction is finished.
* @api
* @param[in]     CtrlIdx Index of the controller which transceiver register
*                shall be written. The index is valid within the context of
*                the Ethernet Driver only.
* @param[in]     TrcvIdx Index of the transceiver connected the MII. The value
*                shall be within the range 0..31.
* @param[in]     RegIdx Index of the transceiver register to be written. The
*                value shall be withing the range 0..31.
* @param[in]     RegVal Value to be written into the indexed register.
* @implements    Eth_WriteMii_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(Eth_ReturnType, ETH_CODE) Eth_WriteMii ( \
                                    VAR(uint8, AUTOMATIC) CtrlIdx, \
                                    VAR(uint8, AUTOMATIC) TrcvIdx, \
                                    VAR(uint8, AUTOMATIC) RegIdx, \
                                    VAR(uint16, AUTOMATIC) RegVal \
                                            )
{
    VAR(Eth_ReturnType, AUTOMATIC) eReturnStatus = ETH_E_NOT_OK;
    
    #if STD_ON == ETH_DEV_ERROR_DETECT
    /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
    /** @violates @ref Eth_c_REF_5 MISRA rule 13.7 */
    /** @violates @ref Eth_c_REF_14 MISRA rule 14.1 */
    if((CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)||((VAR(boolean, AUTOMATIC))FALSE == ETH_CFG_MDIOSUPPORT(CtrlIdx)))
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_WRITEMII, \
            ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
       if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_WRITEMII, \
                ETH_E_NOT_INITIALIZED \
                                  );
        }
        else
        {
    #endif /* ETH_DEV_ERROR_DETECT  */
            /** @violates @ref Eth_c_REF_6 MISRA rule 1.2 */
            if((VAR(boolean, AUTOMATIC))TRUE == Eth_Ipw_WriteMii(CtrlIdx, TrcvIdx, RegIdx, &RegVal))
            {
                eReturnStatus = ETH_OK;
            }
            else
            {   /* Communication timeout - controller inaccessible */
                    eReturnStatus = ETH_E_NO_ACCESS;
            }
    #if STD_ON == ETH_DEV_ERROR_DETECT
        }
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
    return eReturnStatus;
}

/*================================================================================================*/
/**
* @brief          Reads a transceiver (physical layer driver) register.
* @api
* @param[in]      CtrlIdx Index of the controller which transceiver register
*                 shall be read. The index is valid within the context of
*                 the Ethernet Driver only.
* @param[in]      TrcvIdx Index of the transceiver connected on the MII. The
*                 value shall be within the range 0..31.
* @param[in]      RegIdx Index of the transceiver register to be read. The
*                 Value shall be within the range 0..31.
* @param[out]     RegValPtr Filled with the register content of the indexed register
* @details        The management frame is assembled and the MII bus transaction
*                 is issued in order to transfer the data. Function waits until
*                 the bus transaction finishes and then returns the read data.
* @warning        This function is blocking the execution until the MII bus
*                 transaction is finished.
* @implements     Eth_ReadMii_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(Eth_ReturnType, ETH_CODE) Eth_ReadMii  ( \
                            VAR(uint8, AUTOMATIC) CtrlIdx, \
                            VAR(uint8, AUTOMATIC) TrcvIdx, \
                            VAR(uint8, AUTOMATIC) RegIdx, \
                            P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) RegValPtr \
                                            )
{
    VAR(Eth_ReturnType, AUTOMATIC) eReturnStatus = ETH_E_NOT_OK;
    
    #if STD_ON == ETH_DEV_ERROR_DETECT
    /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
    /** @violates @ref Eth_c_REF_5 MISRA rule 13.7 */
    /** @violates @ref Eth_c_REF_14 MISRA rule 14.1 */
    if((CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)||((VAR(boolean, AUTOMATIC))FALSE == ETH_CFG_MDIOSUPPORT(CtrlIdx)))
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_READMII, \
            ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(NULL_PTR == RegValPtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_READMII, \
                ETH_E_INV_POINTER \
                                  );
        }
        else
        {
           if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_READMII, ETH_E_NOT_INITIALIZED \
                                      );
            }
            else
            {
    #endif /* ETH_DEV_ERROR_DETECT  */
                if((VAR(boolean, AUTOMATIC))TRUE == Eth_Ipw_ReadMii(CtrlIdx, TrcvIdx, RegIdx, RegValPtr))
                {
                    eReturnStatus = ETH_OK;
                }
                else
                {   /* Communication timeout - controller inaccessible */
                    eReturnStatus = ETH_E_NO_ACCESS;
                }

    #if STD_ON == ETH_DEV_ERROR_DETECT
            }
        }  
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
    return eReturnStatus;
}
#endif /* ETH_CTRLENABLE_MII */
/*================================================================================================*/
/**
* @brief         Reads the value of a counter specified with its memory offset.
* @note          All counters are 32 bit counters with wrap-around. They are
*                reset to value 0 by the Eth_ControllerInit() function call.
* @api
* @param[in]     CtrlIdx Index of the controller which counter state shall be
*                read. The index is valid within the context of the Ethernet
*                Driver only.
* @param[in]     CtrOffs Memory offset of the counter which state shall be read.
*                The offset is controller specific - the offsets are provided
*                in the file Eth_ENET_Counters.h.
* @param[out]    CtrValPtr Pointer to 32 bit long memory space to be filled with
*                the content of the specified counter.
* @implements    Eth_GetCounterState_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(void, ETH_CODE) Eth_GetCounterState    ( \
                                VAR(uint8, AUTOMATIC) CtrlIdx, \
                                VAR(uint16, AUTOMATIC) CtrOffs, \
                                P2VAR(uint32, AUTOMATIC, ETH_APPL_DATA) CtrValPtr \
                                            )
{
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
            ETH_SID_GETCOUNTERSTATE, ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(NULL_PTR == CtrValPtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_GETCOUNTERSTATE, ETH_E_INV_POINTER \
                                  );
        }
        else
        {
            if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_GETCOUNTERSTATE, ETH_E_NOT_INITIALIZED \
                                      );
            }
            else
            {
    #endif /* ETH_DEV_ERROR_DETECT  */
                Eth_Ipw_GetCounterState(CtrlIdx, CtrOffs, CtrValPtr);
    #if STD_ON == ETH_DEV_ERROR_DETECT
            }
        } 
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
}

/*================================================================================================*/
/**
* @brief         Provides access to a transmit buffer of the specified
*                controller.
* @warning       The application should handle possible difference between the
*                requested and granted buffer lengths. It is not necessary to
*                use whole granted buffer i.e. some space at the end may not
*                be written.
* @api
* @param[in]     CtrlIdx Index of the controller which buffer shall be provided.
*                The index is valid within the context of the Ethernet Driver
*                only.
* @param[out]    BufIdxPtr Index to the granted transmit buffer resource.
*                It uniquely identifies the buffer in all subsequent calls of
*                functions Eth_Transmit() and Eth_TxConfirmation().
* @param[out]    BufPtr Pointer to the granted buffer. This is the space where
*                the data to be transmitted shall be stored.
* @param[in,out] LenBytePtr Buffer payload length
*                - In: desired length in bytes
*                - Out: granted length in bytes
* @return        Error and buffer status
* @retval        BUFREQ_OK: Buffer was successfully granted and no error has
*                occurred.
* @retval        BUFREQ_E_NOT_OK: A development error was detected and no buffer
*                was granted.
* @retval        BUFREQ_E_BUSY: All available buffers in use therefore no
*                buffer was granted. No error has been detected.
* @implements    Eth_ProvideTxBuffer_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(BufReq_ReturnType, ETH_CODE) Eth_ProvideTxBuffer( \
                            VAR(uint8, AUTOMATIC) CtrlIdx, \
                           P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) BufIdxPtr, \
                            P2P2VAR(Eth_DataType, AUTOMATIC, ETH_APPL_DATA) BufPtr, \
                            P2VAR(uint16, AUTOMATIC, ETH_APPL_DATA) LenBytePtr \
                                                     )
{
    /* Variable used to track function success status */
    VAR(BufReq_ReturnType, AUTOMATIC) eFunctionSuccess = BUFREQ_E_NOT_OK;
    VAR(uint16, AUTOMATIC) u16TempLenByte; /* Avoid changes of input
                                              parameters in case of an error */
    VAR(uint32, AUTOMATIC) u32MaxLenByte; /* Maximum available buffer length that
                                              drivers can provide*/
    
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
            ETH_SID_PROVIDETXBUFFER, ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(NULL_PTR == BufIdxPtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_PROVIDETXBUFFER, ETH_E_INV_POINTER \
                                  );
        }
        else
        {
            if(NULL_PTR == BufPtr)
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_PROVIDETXBUFFER, ETH_E_INV_POINTER \
                                      );
            }
            else
            {
                if(NULL_PTR == LenBytePtr)
                {
                    (void)Det_ReportError ( \
                        (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                        ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                        ETH_SID_PROVIDETXBUFFER, ETH_E_INV_POINTER \
                                          );
                }
                else
                {
                    if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
                    {
                        (void)Det_ReportError ( \
                            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                            ETH_SID_PROVIDETXBUFFER, ETH_E_NOT_INITIALIZED \
                                              );
                    }
                    else
                    {
    #endif /* ETH_DEV_ERROR_DETECT  */
                        /* Check whether the requested length is greater than
                           maximal configured one */
    #if STD_ON == ETH_USE_MULTIBUFFER_TX_FRAMES
                        /** @violates @ref Eth_c_REF_8 MISRA rule 17.4 */
                        u32MaxLenByte = ((ETH_CFG_CTRLTXBUFLENBYTE(CtrlIdx)) * (VAR(uint32, AUTOMATIC))ETH_CFG_TXBUFTOTAL(CtrlIdx)) - (VAR(uint32, AUTOMATIC))14U;
    #else
                        /** @violates @ref Eth_c_REF_8 MISRA rule 17.4 */
                        u32MaxLenByte = ETH_CFG_CTRLTXBUFLENBYTE(CtrlIdx) - (VAR(uint32, AUTOMATIC))14U;
    #endif

                        if(*LenBytePtr > u32MaxLenByte)
                        {   /* Requested size is too long, do not lock buffer */
                            /* Set length to maximal available payload length */
                           *LenBytePtr = (VAR(uint16,AUTOMATIC))u32MaxLenByte;
                            eFunctionSuccess = BUFREQ_E_OVFL;
                        }
                        else
                        {   /* Good, the requested size fits into buffer size */
                            /* Get some space to put data in, check success */
                            u16TempLenByte = *LenBytePtr;
                            /** @violates @ref Eth_c_REF_6 MISRA rule 1.2 */
                            if(((VAR(boolean, AUTOMATIC))TRUE) == Eth_Ipw_ProvideBufferDataArea(CtrlIdx, BufIdxPtr, BufPtr, &u16TempLenByte))
                            { /* Data space is available */
                                *LenBytePtr = u16TempLenByte;
                                eFunctionSuccess = BUFREQ_OK;
                            }
                            else
                            { /* Data space is not available */
                                eFunctionSuccess = BUFREQ_E_BUSY;
                            }
                        }
    #if STD_ON == ETH_DEV_ERROR_DETECT
                    }
                }
            }
        }
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
    return eFunctionSuccess;
}

/*================================================================================================*/
/**
* @brief         Triggers transmission of a previously granted and then filled
*                transmit buffer.
* @api
* @param[in]     CtrlIdx Index of the controller which buffer shall be
*                transmitted. The index is valid within the context of
*                the Ethernet Driver only.
* @param[in]     BufIdx Index of the buffer resource to be transmitted.
* @param[in]     FrameType Desired value of the Ethernet frame type in the
*                frame header.
* @param[in]     TxConfirmation Activates transmission confirmation.
* @param[in]     LenByte Buffer data length in bytes (payload length).
* @param[in]     PhysAddrPtr Physical target address (MAC address) in network
*                byte order.
* @return        Error status
* @retval        E_OK No error was detected during the function execution.
* @retval        E_NOT_OK Development error was detected and the function
*                failed.
* @implements    Eth_Transmit_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(Std_ReturnType, ETH_CODE) Eth_Transmit     (
                            VAR(uint8, AUTOMATIC) CtrlIdx,
                            VAR(uint8, AUTOMATIC) BufIdx,
                            Eth_FrameType FrameType,
                            VAR(boolean, AUTOMATIC) TxConfirmation,
                            VAR(uint16, AUTOMATIC) LenByte,
                            P2VAR(uint8, AUTOMATIC, ETH_APPL_DATA) PhysAddrPtr
#if STD_ON == ETH_BRIDGE_SUPPORT
                          , P2CONST(uint8, AUTOMATIC, ETH_APPL_DATA) PhysSourceAddrPtr
#endif /* ETH_BRIDGE_SUPPORT  */
                                                )
{
    VAR(Std_ReturnType, AUTOMATIC) u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC))E_NOT_OK; /* Used to track
                                                     function success */
    
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_TRANSMIT, \
            ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(NULL_PTR == PhysAddrPtr)
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_TRANSMIT, \
                ETH_E_INV_POINTER \
                                  );
        }
        else
        {
            if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_TRANSMIT, ETH_E_NOT_INITIALIZED \
                                      );
            }
            else
            {
                if(ETH_MODE_ACTIVE != Eth_Ipw_CheckControllerIsActive(CtrlIdx))
                {
                    (void)Det_ReportError ( \
                        (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                        ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                        ETH_SID_TRANSMIT, ETH_E_INV_MODE \
                                          );
                }
                else
                {
                    /** @violates @ref Eth_c_REF_8 MISRA rule 17.4 */
                    if(BufIdx >= ETH_CFG_TXBUFTOTAL(CtrlIdx))
                    {
                        (void)Det_ReportError ( \
                            (VAR(uint8, AUTOMATIC)) \
                            ETH_MODULE_ID,  ETH_DRIVER_INSTANCE, \
                            (VAR(uint8, AUTOMATIC)) ETH_SID_TRANSMIT, \
                            ETH_E_INV_PARAM \
                                              );
                    }
                    else
                    {
    #endif /* ETH_DEV_ERROR_DETECT  */
                        /* Check whether the buffer was previously locked
                           and has not been transmitted yet */
                        /** @violates @ref Eth_c_REF_8 MISRA rule 17.4 */
                        /** @violates @ref Eth_c_REF_11 MISRA rule 11.1 */
                        if((VAR(boolean, AUTOMATIC))TRUE == Eth_Ipw_IsTxBufLockedBT(CtrlIdx, (VAR(uint8, AUTOMATIC))BufIdx))
                        { /* Yes, transmit the buffer */
                            Eth_Ipw_Transmit(CtrlIdx, BufIdx, FrameType, LenByte, TxConfirmation, PhysAddrPtr
#if STD_ON == ETH_BRIDGE_SUPPORT
                                                , PhysSourceAddrPtr
#endif /* ETH_BRIDGE_SUPPORT  */
                                            );
                            u8FunctionSuccess = (VAR(Std_ReturnType, AUTOMATIC))E_OK;
                        }
                        else
                        { /* No, report an error, do not transmit buffer */
    #if STD_ON == ETH_DEV_ERROR_DETECT
                            (void)Det_ReportError ( \
                                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                                ETH_SID_TRANSMIT, ETH_E_INV_PARAM \
                                                  );
    #endif /* ETH_DEV_ERROR_DETECT  */
                        }
    #if STD_ON == ETH_DEV_ERROR_DETECT
                    }
                }
            }
        }
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
    return u8FunctionSuccess; 
}

/*================================================================================================*/
/**
* @brief         Triggers frames reception notifications.
* @details       All receive buffers are checked and the first received frame is
*                passed to the EthIf module. The caller is notified whether any
*                frame was received and whether more frames are available in the
*                receive queue.
* @api
* @param[in]     CtrlIdx Index of the controller which shall be checked whether
*                any new frames were received. The index is valid within
*                the context of the Ethernet Driver only.
* @param[out]    RxStatusPtr Informs the caller whether a frame was received 
*                (@c ETH_RECEIVED or @c ETH_NOT_RECEIVED) and whether more frames
*                are available in the queue (@c ETH_RECEIVED or 
*                @c ETH_RECEIVED_MORE_DATA_AVAILABLE).
* @implements    Eth_Receive_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(void, ETH_CODE) Eth_Receive(VAR(uint8, AUTOMATIC) CtrlIdx, P2VAR(Eth_RxStatusType, AUTOMATIC, ETH_APPL_DATA) RxStatusPtr)
{
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_RECEIVE, \
            ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) ETH_SID_RECEIVE, \
                ETH_E_NOT_INITIALIZED \
                                  );
        }
        else
        {
            if(ETH_MODE_ACTIVE != Eth_Ipw_CheckControllerIsActive(CtrlIdx))
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_RECEIVE, ETH_E_INV_MODE \
                                      );
            }
            else
            {
    #endif /* ETH_DEV_ERROR_DETECT  */
                /** @violates @ref Eth_c_REF_5 MISRA rule 13.7 */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                /** @violates @ref Eth_c_REF_14 MISRA rule 14.1 */
                if((VAR(boolean, AUTOMATIC))FALSE == ETH_CFG_ENABLERXINTERRUPT(CtrlIdx))
                {
                    /* Check all buffers and report them - returned error
                    status is ignored because there is no mean to report errors
                    in the AUTOSAR specification */
                    *RxStatusPtr = Eth_Ipw_ReportReception(CtrlIdx, (VAR(boolean, AUTOMATIC))FALSE);
                }/*ETH_CFG_ENABLERXINTERRUPT*/
    #if STD_ON == ETH_DEV_ERROR_DETECT
                /* Check whether any too long frame has been discarded/lost 
                   Note: this check is done after the reporting the reception
                   to avoid all buffers being filled without reporting them
                   to the upper layer just because of lost frames. */
                if((VAR(boolean, AUTOMATIC))TRUE == Eth_Ipw_TooLongFrameReceived(CtrlIdx))
                {
                    (void)Det_ReportError ( \
                        (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                        ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                        ETH_SID_RECEIVE, ETH_E_FRAMES_LOST \
                                          );
                }
            }
        } 
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
}

/*================================================================================================*/
/**
* @brief         Triggers frame transmission confirmations.
* @api
* @param[in]     CtrlIdx Index of the controller which shall be checked whether
*                any frame transmission has finished. The index is valid within
*                the context of the Ethernet Driver only.
* @details       All transmit buffers are checked and upper layers are informed
*                about successfully transmitted frames. Buffers containing
*                transmitted frames are unlocked after the confirmation.
* @implements    Eth_TxConfirmation_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(void, ETH_CODE) Eth_TxConfirmation(VAR(uint8, AUTOMATIC) CtrlIdx)
{
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(CtrlIdx >= (VAR(uint8, AUTOMATIC))ETH_MAXCTRLS_SUPPORTED)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
            ETH_SID_TXCONFIRMATION, ETH_E_INV_CTRL_IDX \
                              );
    }
    else
    {
        if(ETH_STATE_ACTIVE != Eth_CtrlState[CtrlIdx])
        {
            (void)Det_ReportError ( \
                (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                ETH_SID_TXCONFIRMATION, ETH_E_NOT_INITIALIZED \
                                  );
        }
        else
        {
            if(ETH_MODE_ACTIVE != Eth_Ipw_CheckControllerIsActive(CtrlIdx))
            {
                (void)Det_ReportError ( \
                    (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
                    ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
                    ETH_SID_TXCONFIRMATION, ETH_E_INV_MODE \
                                      );
            }
            else
            {

    #endif /* ETH_DEV_ERROR_DETECT  */
                /** @violates @ref Eth_c_REF_5 MISRA rule 13.7 */
                /** @violates @ref Eth_c_REF_4 MISRA rule 17.4 */
                /** @violates @ref Eth_c_REF_14 MISRA rule 14.1 */
                if((VAR(boolean, AUTOMATIC))FALSE == ETH_CFG_ENABLETXINTERRUPT(CtrlIdx))
                {
                    /* Check all buffers and report them - returned error 
                    status is ignored because there is no mean to report errors
                    in the AUTOSAR specification */
                    (void)Eth_Ipw_ReportTransmission(CtrlIdx);
                }/*ETH_CFG_ENABLETXINTERRUPT*/
    #if STD_ON == ETH_DEV_ERROR_DETECT
            }
        } 
    }
    #endif /* ETH_DEV_ERROR_DETECT  */
}

#if STD_ON == ETH_VERSION_INFO_API
#if STD_OFF == ETH_VERSION_INFO_API_MACRO
/*================================================================================================*/
/**
* @brief         Returns the version information of this module.
* @api
* @param[out]    VersionInfoPtr Pointer where to store the version information
*                of this particular module instance.
* @implements    Eth_GetVersionInfo_Activity
*/

/** @violates @ref Eth_c_REF_7 MISRA rule 8.10 */
FUNC(void, ETH_CODE) Eth_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ETH_APPL_DATA) VersionInfoPtr) 
{
    #if STD_ON == ETH_DEV_ERROR_DETECT
    if(NULL_PTR == VersionInfoPtr)
    {
        (void)Det_ReportError ( \
            (VAR(uint8, AUTOMATIC)) ETH_MODULE_ID, \
            ETH_DRIVER_INSTANCE, (VAR(uint8, AUTOMATIC)) \
            ETH_SID_GETVERSIONINFO, ETH_E_INV_POINTER \
                              );
    }
    else
    {
    #endif /* ETH_DEV_ERROR_DETECT */
        VersionInfoPtr->moduleID = (VAR(uint16, AUTOMATIC))ETH_MODULE_ID;
        VersionInfoPtr->vendorID = (VAR(uint16, AUTOMATIC))ETH_VENDOR_ID;
        VersionInfoPtr->sw_major_version = (VAR(uint8, AUTOMATIC))ETH_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (VAR(uint8, AUTOMATIC))ETH_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (VAR(uint8, AUTOMATIC))ETH_SW_PATCH_VERSION;

    #if STD_ON == ETH_DEV_ERROR_DETECT
    }
    #endif /* ETH_DEV_ERROR_DETECT */
}
#endif /* STD_OFF == ETH_VERSION_INFO_API_MACRO */
#endif /* ETH_VERSION_INFO_API */

#define ETH_STOP_SEC_CODE
/**
 * @violates @ref Eth_c_REF_1 MISRA rule 19.1
 * @violates @ref Eth_c_REF_2 MISRA rule 19.15
 */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
