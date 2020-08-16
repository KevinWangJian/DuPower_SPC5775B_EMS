/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




/* MR12 DIR 4.10 VIOLATION: MemMap header concept - no protection against multiple inclusion intended */
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
#define MEMMAP_ERROR

#if defined WDGIF_START_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGIF_START_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined WDGIF_STOP_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef WDGIF_STOP_SEC_CONFIG_DATA_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined WDGIF_START_SEC_CODE
    #define  BSW_START_SEC_CODE
	#include "Bsw_MemMap.h"
    #undef WDGIF_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined WDGIF_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
	#include "Bsw_MemMap.h"
    #undef WDGIF_STOP_SEC_CODE
    #undef MEMMAP_ERROR

#elif defined WDGIF_START_SEC_CODE_FAST
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGIF_START_SEC_CODE_FAST
    #undef MEMMAP_ERROR
#elif defined WDGIF_STOP_SEC_CODE_FAST
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGIF_STOP_SEC_CODE_FAST
    #undef MEMMAP_ERROR

#elif defined WDGIF_START_SEC_CODE_SLOW
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGIF_START_SEC_CODE_SLOW
    #undef MEMMAP_ERROR
#elif defined WDGIF_STOP_SEC_CODE_SLOW
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef WDGIF_STOP_SEC_CODE_SLOW
    #undef MEMMAP_ERROR


#elif defined MEMMAP_ERROR
    #error "WdgIf_MemMap.h, wrong #pragma command"
#endif


