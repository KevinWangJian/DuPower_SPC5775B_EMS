/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




/* MISRA RULE 19.15 VIOLATION: MemMap header concept - no protection against multiple inclusion intended */
#define MEMMAP_ERROR

/* note: this area is protected against multiple includes */

/* ============================   BSW   ============================ */

/* Used for global or static variables that are
    cleared to zero after every reset */
#if defined BSWM_START_SEC_VAR_CLEARED_8
    /*  8 bit */
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_VAR_CLEARED_32
    /* 32 bit */
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_VAR_CLEARED_BOOLEAN
    /* BOOLEAN size */
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR

/* Used for global or static variables that are
    initialized with values after every reset */

#elif defined BSWM_START_SEC_VAR_INIT_8
    /*  8 bit */
    #define BSW_START_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_VAR_INIT_8
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_VAR_INIT_8
    #define BSW_STOP_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_VAR_INIT_8
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_VAR_INIT_16
    /*  16 bit */
    #define BSW_START_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_VAR_INIT_16
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_VAR_INIT_16
    #define BSW_STOP_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_VAR_INIT_16
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_VAR_INIT_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_VAR_INIT_BOOLEAN
    /* BOOLEAN size */
    #define BSW_START_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_VAR_INIT_BOOLEAN
    #define BSW_STOP_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_VAR_INIT_BOOLEAN
    #undef MEMMAP_ERROR

/* Global or static constants */
#elif defined BSWM_START_SEC_CONST_8
    /*  8 bit */
    #define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_CONST_16
    /* 16 bit */
    #define BSW_START_SEC_CONST_16
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_CONST_16
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_CONST_16
    #define BSW_STOP_SEC_CONST_16
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_CONST_16
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_CONST_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

/* Memory section for PostBuild data */
#elif defined BSWM_START_SEC_CONFIG_DATA_POSTBUILD_32
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_CONFIG_DATA_POSTBUILD_32
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
    #undef MEMMAP_ERROR

#elif defined BSWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined BSWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

/*For all the sections defined in RTE have included via BswM_MemMap.h file and redeclarations have been removed with the following mapping*/
#elif defined BSWM_START_SEC_CODE
    #define  BSW_START_SEC_CODE
	#include "BswM_MemMap.h"
    #undef BSWM_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined BSWM_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
	#include "BswM_MemMap.h"
    #undef BSWM_STOP_SEC_CODE
    #undef MEMMAP_ERROR
#endif

#ifdef MEMMAP_ERROR
  #error "BswM_Cfg_MemMap.h, wrong #pragma command"
#endif

/*
 **********************************************************************************************************************
*/
