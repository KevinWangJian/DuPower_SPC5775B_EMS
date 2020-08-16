/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



/* Copy write information as per the latest templates */

/* MemMap.h for AUTOSAR Memory Mapping R4.0 Rev 3 */
/* MR12 DIR 4.10 VIOLATION: MemMap header concept - no protection against repeated inclusion intended. */
#define MEMMAP_ERROR
#if(COMM_CONFIGURATION_VARIANT == COMM_VARIANT_PRECOMPILE)
// If Module is pre-compile , then map post-build memmap to pre-compile memmap
#ifdef COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define COMM_START_SEC_CONST_UNSPECIFIED
#endif

#ifdef COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define COMM_STOP_SEC_CONST_UNSPECIFIED
#endif

#endif /* #if(COMM_CONFIGURATION_VARIANT == COMM_VARIANT_PRECOMPILE)  */

/*----------------------------------------------------------------------------*/
/* To be used for global or static constants */
/* All generated constant variables */
/*----------------------------------------------------------------------------*/

#if defined COMM_START_SEC_CONST_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined COMM_START_SEC_CONST_8
    #define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR
/*----------------------------------------------------------------------------*/

/* Used for global or static variables that are
    cleared to zero after every reset */
#elif defined COMM_START_SEC_VAR_CLEARED_BOOLEAN
    /*  BOOLEAN */
    #define BSW_START_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_CLEARED_BOOLEAN
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR


#elif defined COMM_START_SEC_VAR_CLEARED_8
    /*  8 bit */
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR




#elif defined COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
    /* UNSPECIFIED */
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

/*----------------------------------------------------------------------------*/
/* used for variables that are initialized with values after every reset */
/*----------------------------------------------------------------------------*/

 #elif defined COMM_START_SEC_VAR_INIT_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR



/*----------------------------------------------------------------------------*/
/* DEFAULT                normal or slow access        cyclic variable >= 10ms  */
/*----------------------------------------------------------------------------*/
#elif defined COMM_START_SEC_CODE
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CODE
    #undef MEMMAP_ERROR

// Memmap for Post build data
#elif defined COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "ComM_Cfg_MemMap.h, wrong #pragma command"
#endif



