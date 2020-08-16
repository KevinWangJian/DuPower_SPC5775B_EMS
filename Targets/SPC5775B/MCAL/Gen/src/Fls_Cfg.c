/**
*   @file    Fls_Cfg.c
*   @implements Fls_Cfg.c_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver.
*   @details Definitions of all Pre-compile configuration structures.
*
*   @addtogroup FLS
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : Flash_Memory
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
* @section fls_cfg_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, Only preprocessor statements and comments before 
* '#include'
* Because of Autosar requirement MEMMAP003 of memory mapping.
*
* @section fls_cfg_c_REF_2
* Violates MISRA 2004 Required Rule 11.1, Conversions involing function pointers must be to/from integral types.
* This violation is due to FLS213.
* 
* @section fls_cfg_c_REF_3
* Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between a pointer type and
* an integral type.
* This violation is due to FLS213.
* 
* @section fls_cfg_c_REF_4
* Violates MISRA 2004 Required Rule 8.8, Object/function previously declared.
* The rule 8.8 requires that 'An external object or function shall be declared in one and only one file'.
* This requirement is fulfilled since the function is declared as external in and only in one configuration 
* C file (Fls_Cfg.c or Fls_PBcfg.c). There is no need to put the declaration into Fls_Cfg.h and made it 
* accessible for all modules which includes Fls.h/Fls_Cfg.h.
* 
* @section fls_cfg_c_REF_5
* Violates MISRA 2004 Required Rule 20.2, Re-use of C90 identifier pattern.
* This is just a matter of a symbol specified in the configuration.
*  
* @section fls_cfg_c_REF_6
* Violates MISRA 2004 Advisory Rule 11.4, Cast from pointer to pointer.
* This violation is due to FLS213.    
* 
* @section [global]
* Violates MISRA 2004 Required Rule 5.1,
* Identifiers (internal and external) shall not rely on the significance of more than 31 characters. 
* The used compilers use more than 31 chars for identifiers.
* 
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that
* 31 character significance and case sensitivity are supported for external identifiers
* This violation is due to the requirement that requests to have a file version check.
* 
* @section [global]
* Violates MISRA 2004 Required Rule 19.15, Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
* 
* 
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fls.h"
#ifdef FLS_PRECOMPILE_SUPPORT

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_VENDOR_ID_PCFG_C                      43
#define FLS_AR_RELEASE_MAJOR_VERSION_PCFG_C       4
#define FLS_AR_RELEASE_MINOR_VERSION_PCFG_C       0
#define FLS_AR_RELEASE_REVISION_VERSION_PCFG_C    3
#define FLS_SW_MAJOR_VERSION_PCFG_C               1
#define FLS_SW_MINOR_VERSION_PCFG_C               0
#define FLS_SW_PATCH_VERSION_PCFG_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Fls header file are of the same vendor */
#if (FLS_VENDOR_ID_PCFG_C != FLS_VENDOR_ID)
    #error "Fls_Cfg.c and Fls.h have different vendor ids"
#endif
/* Check if current file and Fls header file are of the same Autosar version */
#if ((FLS_AR_RELEASE_MAJOR_VERSION_PCFG_C    != FLS_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_AR_RELEASE_MINOR_VERSION_PCFG_C    != FLS_AR_RELEASE_MINOR_VERSION) || \
     (FLS_AR_RELEASE_REVISION_VERSION_PCFG_C != FLS_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Fls_Cfg.c and Fls.h are different"
#endif
/* Check if current file and Fls header file are of the same Software version */
#if ((FLS_SW_MAJOR_VERSION_PCFG_C != FLS_SW_MAJOR_VERSION) || \
     (FLS_SW_MINOR_VERSION_PCFG_C != FLS_SW_MINOR_VERSION) || \
     (FLS_SW_PATCH_VERSION_PCFG_C != FLS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Fls_Cfg.c and Fls.h are different"
#endif



/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/

        
        
#define FLS_START_SEC_CODE
/* 
* @violates @ref fls_cfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "MemMap.h"


/* Declaration of Fls Access Code Pointer (Fls_Flash_AccessCode)*/
/* @violates @ref fls_cfg_c_REF_5 Re-use of C90 identifier pattern */
extern uint8 Fls_Flash_AccessCode;


#define FLS_STOP_SEC_CODE
/* 
* @violates @ref fls_cfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "MemMap.h"
    



                                        
                        



#define FLS_START_SEC_CONFIG_DATA_8
/* 
* @violates @ref fls_cfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "MemMap.h"

/* aFlsSectorFlags[] (FlsConfigSet_0) */
static CONST(uint8, FLS_CONST) FlsConfigSet_0_aFlsSectorFlags[2] =
{
    0U, /* (FlsSector_0) */
    0U /* (FlsSector_1) */
};
/* aFlsSectorUnlock[] (FlsConfigSet_0) */
static CONST(uint8, FLS_CONST) FlsConfigSet_0_aFlsSectorUnlock[2] =
{
    1U, /* (FlsSector_0) */
    1U /* (FlsSector_1) */
};
#define FLS_STOP_SEC_CONFIG_DATA_8
/* 
* @violates @ref fls_cfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "MemMap.h"

#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
/* 
* @violates @ref fls_cfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "MemMap.h"

/* aFlsSectorEndAddr[] (FlsConfigSet_0) */
static CONST(Fls_AddressType, FLS_CONST) FlsConfigSet_0_aFlsSectorEndAddr[2] =
{
    65535U, /* FlsSectorEndAddr (FlsSector_0)*/
    131071U /* FlsSectorEndAddr (FlsSector_1)*/
};
/* aFlsProgrammingSize[] (FlsConfigSet_0) */
static CONST(Fls_LengthType, FLS_CONST) FlsConfigSet_0_aFlsProgSize[2] =
{
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD, /* FlsProgrammingSize (FlsSector_0) */
    (Fls_LengthType)FLS_WRITE_DOUBLE_WORD /* FlsProgrammingSize (FlsSector_1) */
};
/* aFlsPhysicalSector[] (FlsConfigSet_0) */
static CONST(Fls_Flash_PhysicalSectorType, FLS_CONST) FlsConfigSet_0_aFlsPhysicalSector[2] =
{
    FLS_DATA_ARRAY_0_PART_0_L00, /* FlsPhysicalSector (FlsSector_0) */
    FLS_DATA_ARRAY_0_PART_1_L01 /* FlsPhysicalSector (FlsSector_1) */
};
/**
* @brief        Structure used to set function pointers notification, working mode
*/
/* Fls module initialization data */ 
CONST(Fls_ConfigType, FLS_CONST) Fls_ConfigSetPC =
{
    /* @violates @ref fls_cfg_c_REF_2 Conversions involing function pointers must be to/from integral types */
    /* @violates @ref fls_cfg_c_REF_3 Cast from pointer to pointer */
    /* @violates @ref fls_cfg_c_REF_6 Cast from pointer to pointer */
    (Fls_Flash_AcErasePtrType)&Fls_Flash_AccessCode, /* FlsAcErase */
    /* @violates @ref fls_cfg_c_REF_2 Conversions involing function pointers must be to/from integral types */
    /* @violates @ref fls_cfg_c_REF_3 Cast from pointer to pointer */
    /* @violates @ref fls_cfg_c_REF_6 Cast from pointer to pointer */
    (Fls_Flash_AcWritePtrType)&Fls_Flash_AccessCode, /* FlsAcWrite */
    NULL_PTR, /* FlsACCallback */
    NULL_PTR, /* FlsJobEndNotification */
    NULL_PTR, /* FlsJobErrorNotification */
    NULL_PTR, /* FlsStartFlashAccessNotif */
    NULL_PTR, /* FlsFinishedFlashAccessNotif */
    MEMIF_MODE_SLOW, /* FlsDefaultMode */
    1048576U, /* FlsMaxReadFastMode */
    1024U, /* FlsMaxReadNormalMode */
    256U, /* FlsMaxWriteFastMode */
    8U, /* FlsMaxWriteNormalMode */
    2U, /* FlsSectorCount */
    &FlsConfigSet_0_aFlsSectorEndAddr, /* aFlsSectorEndAddr[]  */
    &FlsConfigSet_0_aFlsPhysicalSector, /* aFlsPhysicalSector[] */
    &FlsConfigSet_0_aFlsSectorFlags, /* aFlsSectorFlags[] */
    &FlsConfigSet_0_aFlsProgSize, /* aFlsProgSize[] */
    &FlsConfigSet_0_aFlsSectorUnlock, /* aFlsSectorUnlock[] */
            39670U /* configCrc */
};

#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* 
* @violates @ref fls_cfg_c_REF_1 Only preprocessor statements
* and comments before '#include'
*/
#include "MemMap.h"



#endif /* FLS_PRECOMPILE_SUPPORT */
#ifdef __cplusplus
}
#endif

/** @}*/
