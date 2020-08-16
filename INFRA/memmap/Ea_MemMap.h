/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



/* <component>_MemMap.h for AUTOSAR Memory Mapping R4.0 Rev 3 */
/* MISRA RULE 19.15 VIOLATION: MemMap header concept - no protection against repeated inclusion intended */
#define MEMMAP_ERROR

/* Ea Cleared RAM: boolean mapped to 8 bit */
#if defined EA_START_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_VAR_CLEARED_BOOLEAN
    #undef MEMMAP_ERROR

/* Ea Cleared RAM: 8 bit values */
#elif defined EA_START_SEC_VAR_CLEARED_8
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR

/* Ea Cleared RAM: 16 bit values */
#elif defined EA_START_SEC_VAR_CLEARED_16
    #define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_VAR_CLEARED_16
    #define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR

/* Ea Cleared RAM: 32 bit values */
#elif defined EA_START_SEC_VAR_CLEARED_32
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR

/* Ea Cleared RAM: unspecified size */
#elif defined EA_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

/* Ea Initialized RAM: 32 bit values */
#elif defined EA_START_SEC_VAR_INIT_32
    #define BSW_START_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_VAR_INIT_32
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_VAR_INIT_32
    #define BSW_STOP_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_VAR_INIT_32
    #undef MEMMAP_ERROR

/* Ea Initialized RAM: unspecified size */
#elif defined EA_START_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

/* Ea Const (ROM): unspecified size */
#elif defined EA_START_SEC_CONST_UNSPECIFIED
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

/* Ea Code */
#elif defined EA_START_SEC_CODE
    #define BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef EA_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined EA_STOP_SEC_CODE
    #define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef EA_STOP_SEC_CODE
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "Ea_MemMap.h, wrong #pragma command"
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
 **********************************************************************************************************************
 * End of header file: $Name______:Ea_MemMap$
 **********************************************************************************************************************
</BASDKey>*/
