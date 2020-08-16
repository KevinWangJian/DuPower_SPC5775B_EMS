/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



/*
 *********************************************************************************************************
 * Defines/Macros
 *********************************************************************************************************
*/

/* MR12 RULE 1.2, DIR 4.10 VIOLATION: MemMap header concept - no protection against multiple inclusion intended */
#define MEMMAP_ERROR

#if defined WDGM_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_FAST_CLEARED_BOOLEAN
    /*  BOOLEAN */
    #define BSW_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_FAST_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_FAST_CLEARED_8
    /*  8 bit */
    #define BSW_START_SEC_VAR_FAST_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_FAST_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_FAST_CLEARED_8
    #define BSW_STOP_SEC_VAR_FAST_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_FAST_CLEARED_8
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_FAST_CLEARED_16
    /*  16 bit */
    #define BSW_START_SEC_VAR_FAST_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_FAST_CLEARED_16
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_FAST_CLEARED_16
    #define BSW_STOP_SEC_VAR_FAST_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_FAST_CLEARED_16
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_CLEARED_16
    /*  16 bit */
    #define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_CLEARED_16
    #define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_CLEARED_32
    /*  32 bit */
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_SLOW_INIT_BOOLEAN
    /* BOOLEAN */
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_SLOW_INIT_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_FAST_INIT_8
    #define  BSW_START_SEC_VAR_FAST_INIT_8
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_VAR_FAST_INIT_8
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_FAST_INIT_8
    #define  BSW_STOP_SEC_VAR_FAST_INIT_8
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_VAR_FAST_INIT_8
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    /* Unspecified size */
    #undef WDGM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    #undef WDGM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
    /* Unspecified size */
    #undef WDGM_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
    #undef WDGM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
    /*  8 bit */
    #undef WDGM_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
    #undef WDGM_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    #undef MEMMAP_ERROR

/*For all the sections defined in RTE have included via WdgM_MemMap.h file */
#elif defined WDGM_START_SEC_CODE
    #define  WdgM_START_SEC_CODE
    #include "WdgM_MemMap.h"
    #undef WDGM_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_CODE
    #define  WdgM_STOP_SEC_CODE
    #include "WdgM_MemMap.h"
    #undef WDGM_STOP_SEC_CODE
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_CODE_FAST
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_CODE_FAST
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_CODE_FAST
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_CODE_FAST
    #undef MEMMAP_ERROR

#elif defined WDGM_START_SEC_CODE_SLOW
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGM_START_SEC_CODE_SLOW
    #undef MEMMAP_ERROR
#elif defined WDGM_STOP_SEC_CODE_SLOW
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGM_STOP_SEC_CODE_SLOW
    #undef MEMMAP_ERROR


#elif defined MEMMAP_ERROR
    #error "WdgM_Cfg_MemMap.h, wrong #pragma command"
#endif
