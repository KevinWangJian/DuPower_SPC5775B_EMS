/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




/* MR12 RULE 1.2 VIOLATION: MemMap header concept - no protection against multiple inclusion intended */
#ifndef COM_MEMMAP_H
#define COM_MEMMAP_H

/* Below inclusion is required to make the module variant info macro's available here. */
#include "Com_Cfg_SymbolicNames.h"

#define MEMMAP_ERROR

#if ( COM_CONFIGURATION_VARIANT == COM_VARIANT_PRE_COMPILE )

/* If Module is Pre-Compile, then map Post-Build MemMap to Pre-Compile MemMap */
# if defined COM_START_SEC_CONFIG_DATA_POSTBUILD_32
#  undef COM_START_SEC_CONFIG_DATA_POSTBUILD_32
#  define COM_START_SEC_CONST_32
# elif defined COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#  undef  COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#  define COM_STOP_SEC_CONST_32

# elif defined COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#  undef COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#  define COM_START_SEC_CONST_UNSPECIFIED
# elif defined COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#  undef  COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#  define COM_STOP_SEC_CONST_UNSPECIFIED

# elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#  undef COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#  define COM_START_SEC_VAR_CLEARED_8
# elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#  undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#  define COM_STOP_SEC_VAR_CLEARED_8

# elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#  undef COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#  define COM_START_SEC_VAR_CLEARED_16
# elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#  undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#  define COM_STOP_SEC_VAR_CLEARED_16

# elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#  undef COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#  define COM_START_SEC_VAR_CLEARED_32
# elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#  undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#  define COM_STOP_SEC_VAR_CLEARED_32

# elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#  undef COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#  define COM_START_SEC_VAR_CLEARED_64
# elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
#  undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
#  define COM_STOP_SEC_VAR_CLEARED_64

# elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#  undef COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#  define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
# elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#  undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#  define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED

# endif

#endif /* #if ( COM_CONFIGURATION_VARIANT == COM_VARIANT_PRE_COMPILE ) */

#if defined COM_START_SEC_CONST_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_CONST_32
    /* 32-bit size */
    #define BSW_START_SEC_CONST_32
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_CONST_32
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_CONST_32
    #define BSW_STOP_SEC_CONST_32
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_CONST_32
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_CONST_8
    /* 8-bit size */
    #define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_CODE
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_CODE
    #undef MEMMAP_ERROR

/*----------------------------------------------------------------------------*/
/* used for variables that are initialized with values after every reset      */
/*----------------------------------------------------------------------------*/

 #elif defined COM_START_SEC_VAR_INIT_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
/*----------------------------------------------------------------------------*/

#elif defined COM_START_SEC_VAR_CLEARED_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_64
    /* 64-bit Size */
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_64
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_64
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_64
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_32
    /* 32-bit Size */
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_16
    /* 16-bit Size */
    #define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_16
    #define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_8
    /*  8-bit Size */
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR

/* Code that shall go into fast code memory segments - Scratchpad Memory (SPRAM) */
#elif defined COM_START_SEC_CODE_FAST
    #define  BSW_START_SEC_CODE_FAST
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_CODE_FAST
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_CODE_FAST
    #define  BSW_STOP_SEC_CODE_FAST
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_CODE_FAST
    #undef MEMMAP_ERROR

/* ======================================================== */
/* == PBL Constants                                      == */
/* ======================================================== */

#elif defined COM_START_SEC_CONFIG_DATA_POSTBUILD_32
    /* 32-bit size */
    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_32
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_CONFIG_DATA_POSTBUILD_32
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_8
    /*  8-bit size */
    #define BSW_START_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_8
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_16
    /* 16-bit size */
    #define BSW_START_SEC_VAR_CLEARED_POSTBUILD_16
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_16
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
    #define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_16
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_32
    /* 32-bit size */
    #define BSW_START_SEC_VAR_CLEARED_POSTBUILD_32
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_32
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
    #define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_32
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_64
    /* 64-bit size */
    #define BSW_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_64
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
    #define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
    #undef MEMMAP_ERROR

#elif defined COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif

#if defined MEMMAP_ERROR
   #error "Com_MemMap.h, wrong #pragma command"
#endif

#undef COM_MEMMAP_H
#endif /* #ifndef COM_MEMMAP_H */


