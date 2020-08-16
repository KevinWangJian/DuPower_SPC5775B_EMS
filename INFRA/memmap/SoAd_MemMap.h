/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
//#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif /* NOT_READY_FOR_TESTING_OR_DEPLOYMENT */



/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      CODE SECION		                                     **
*******************************************************************************/
/* MR12 RULE 1.2 VIOLATION: MemMap header concept - no protection against multiple inclusion intended*/
#ifndef SOAD_MEMMAP_H
#define SOAD_MEMMAP_H

#if defined SOAD_START_SEC_CODE
/* Include file code is not protected against repeated inclusion MISRA-C:2004 Rule 19.15  */
/* MISRA RULE 19.15 VIOLATION: Precautions shall be taken in order to prevent the contents of a header file being included twice. */
    #define BSW_START_SEC_DEFAULT_CODE

    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_CODE
#elif defined SOAD_STOP_SEC_CODE
    #define BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_CODE

#elif defined SOAD_START_SEC_CODE_SLOW
    #define BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_CODE_SLOW
#elif defined SOAD_STOP_SEC_CODE_SLOW
    #define BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_CODE_SLOW

/*******************************************************************************
**                      DATA SECION for CONST                                 **
*******************************************************************************/
#elif defined SOAD_START_SEC_CONST_8
    #define BSW_START_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_CONST_8
#elif defined SOAD_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_CONST_8

#elif defined SOAD_START_SEC_CONST_16
    #define BSW_START_SEC_DEFAULT_CONST_16
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_CONST_16
#elif defined SOAD_STOP_SEC_CONST_16
    #define BSW_STOP_SEC_DEFAULT_CONST_16
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_CONST_16

#elif defined SOAD_START_SEC_CONST_32
    #define BSW_START_SEC_DEFAULT_CONST_32
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_CONST_32
#elif defined SOAD_STOP_SEC_CONST_32
    #define BSW_STOP_SEC_DEFAULT_CONST_32
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_CONST_32

#elif defined SOAD_START_SEC_CONST_UNSPECIFIED
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_CONST_UNSPECIFIED
#elif defined SOAD_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_CONST_UNSPECIFIED

/*******************************************************************************
**                      DATA SECION for STATIC AND GLOBAL                     **
*******************************************************************************/

#elif defined SOAD_START_SEC_VAR_INIT_8
    #define BSW_START_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_INIT_8
#elif defined SOAD_STOP_SEC_VAR_INIT_8
    #define BSW_STOP_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_INIT_8

#elif defined SOAD_START_SEC_VAR_INIT_16
    #define BSW_START_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_INIT_16
#elif defined SOAD_STOP_SEC_VAR_INIT_16
    #define BSW_STOP_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_INIT_16

#elif defined SOAD_START_SEC_VAR_INIT_32
    #define BSW_START_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_INIT_32
#elif defined SOAD_STOP_SEC_VAR_INIT_32
    #define BSW_STOP_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_INIT_32

#elif defined SOAD_START_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_INIT_UNSPECIFIED
#elif defined SOAD_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_INIT_UNSPECIFIED



#elif defined SOAD_START_SEC_VAR_CLEARED_8
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_CLEARED_8
#elif defined SOAD_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_CLEARED_8

#elif defined SOAD_START_SEC_VAR_CLEARED_16
    #define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_CLEARED_16
#elif defined SOAD_STOP_SEC_VAR_CLEARED_16
    #define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_CLEARED_16

#elif defined SOAD_START_SEC_VAR_CLEARED_32
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_CLEARED_32
#elif defined SOAD_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_CLEARED_32

#elif defined SOAD_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef SOAD_START_SEC_VAR_CLEARED_UNSPECIFIED
#elif defined SOAD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef SOAD_STOP_SEC_VAR_CLEARED_UNSPECIFIED

#else
 	#error "Memory mapping is not proper, Please check it in SoAd_MemMap.h file"
#endif

#undef SOAD_MEMMAP_H
#endif
