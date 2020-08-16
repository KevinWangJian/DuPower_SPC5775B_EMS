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



/* MemMap.h for AUTOSAR Memory Mapping R4.0 Rev 3 */
/* MISRA RULE 19.15 VIOLATION: This file is required for Memory mapping       */
#define MEMMAP_ERROR

/* ============================   BSW   ============================ */

/*----------------------------------------------------------------------------*/
/* Constants with attributes that show that they reside in one segment for module configuration. */
/* Mostly for the Post Build modules and for the Configuration Data */
/* But right now it is unused as we support only selectable not loadable in Post Build */


/*----------------------------------------------------------------------------*/
/* To be used for calibration */
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/* To be used for global or static constants */
/* All generated constant variables */
/*----------------------------------------------------------------------------*/

#if defined ETHTRCV_START_SEC_CONST_BOOLEAN
    #define BSW_START_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CONST_BOOLEAN
    #define BSW_STOP_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR


#elif defined ETHTRCV_START_SEC_CONST_8
    #define BSW_START_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR


#elif defined ETHTRCV_START_SEC_CONST_UNSPECIFIED
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR


#elif defined ETHTRCV_START_SEC_CONFIG_DATA_UNSPECIFIED
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CONFIG_DATA_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined ETHTRCV_START_SEC_CONFIG_DATA_8
    #define BSW_START_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CONFIG_DATA_8
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CONFIG_DATA_8
    #define BSW_STOP_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CONFIG_DATA_8
    #undef MEMMAP_ERROR


#elif defined ETHTRCV_START_SEC_CONFIG_DATA_16
    #define BSW_START_SEC_DEFAULT_CONST_16
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CONFIG_DATA_16
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CONFIG_DATA_16
    #define BSW_STOP_SEC_DEFAULT_CONST_16
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CONFIG_DATA_16
    #undef MEMMAP_ERROR


/*----------------------------------------------------------------------------*/
/* To be used for RAM buffers of variables saved in non volatile memory. */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* To be used for all global or static variables that are never initialized. */
/* NOT USED */
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/* used for variables that are never cleared and never initialized */
/* NOT USED */
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/

/* Used for global or static variables that are
    cleared to zero after every reset */
#elif defined ETHTRCV_START_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined ETHTRCV_START_SEC_VAR_CLEARED_8
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR

#elif defined ETHTRCV_START_SEC_VAR_NO_INIT_16
    #define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_VAR_NO_INIT_16
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_VAR_NO_INIT_16
    #define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_VAR_NO_INIT_16
    #undef MEMMAP_ERROR


#elif defined ETHTRCV_START_SEC_VAR_CLEARED_32
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR

#elif defined ETHTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined ETHTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined ETHTRCV_START_SEC_CONFIG_DATA_POSTBUILD_HEADER
    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_HEADER
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CONFIG_DATA_POSTBUILD_HEADER
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_HEADER
    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_HEADER
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_HEADER
    #undef MEMMAP_ERROR



/*----------------------------------------------------------------------------*/
/* used for variables that are cleared to zero only after power on reset */
/* NOT USED */
/*-----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/* used for variables that are initialized with values after every reset */
/* NOT USED */
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/* used for variables that are initialized with values only after power on reset */
/* NOT USED */
/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/* VAR_FAST                for variables which are accessed frequently  */
/*----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
/* DEFAULT                normal or slow access        cyclic variable >= 10ms  */
/*----------------------------------------------------------------------------*/
#elif defined ETHTRCV_START_SEC_CODE
    #define  BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined ETHTRCV_STOP_SEC_CODE
    #define  BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    #undef ETHTRCV_STOP_SEC_CODE
    #undef MEMMAP_ERROR

/* Code that shall go into fast code memory segments - Scratchpad Memory (SPRAM) */




#elif defined MEMMAP_ERROR
  //  #error "ETHTRCV_MemMap.h, wrong #pragma command"
#endif


/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
