/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




/* MemIf_MemMap.h for AUTOSAR Memory Mapping R4.0 Rev 3 */
/* MR12 DIR 4.10 VIOLATION: MemMap header concept - no protection against repeated inclusion intended */
/* MR12 RULE 20.14 VIOLATION: All #if are balanced, no failure expected */

/*
 **********************************************************************************************************************
 * Necessary for service components: RTE uses unchanged SWCD short name for runnables on ASW side
 **********************************************************************************************************************
*/

#if defined MemIf_START_SEC_CODE
    #undef  MemIf_START_SEC_CODE
    #define MEMIF_START_SEC_CODE
#elif defined MemIf_STOP_SEC_CODE
    #undef  MemIf_STOP_SEC_CODE
    #define MEMIF_STOP_SEC_CODE
#endif

/*
 **********************************************************************************************************************
 * Variables mapping
 **********************************************************************************************************************
*/

/* Variables that are cleared to zero after every reset */

/* Cleared RAM: boolean mapped to 8 bit */
#if defined MEMIF_START_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_CLEARED_BOOLEAN
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"

/* Cleared RAM: 8 bit values */
#elif defined MEMIF_START_SEC_VAR_CLEARED_8
    #undef MEMIF_START_SEC_VAR_CLEARED_8
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_CLEARED_8
    #undef MEMIF_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"

/* Cleared RAM: 16 bit values */
#elif defined MEMIF_START_SEC_VAR_CLEARED_16
    #undef MEMIF_START_SEC_VAR_CLEARED_16
    #define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_CLEARED_16
    #undef MEMIF_STOP_SEC_VAR_CLEARED_16
    #define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"

/* Cleared RAM: 32 bit values */
#elif defined MEMIF_START_SEC_VAR_CLEARED_32
    #undef MEMIF_START_SEC_VAR_CLEARED_32
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_CLEARED_32
    #undef MEMIF_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"

/* Cleared RAM: unspecified size */
#elif defined MEMIF_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMIF_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"

/* Variables that are reset to initial value after every reset */

/* Initialized RAM: boolean mapped to 8 bit */
#elif defined MEMIF_START_SEC_VAR_INIT_BOOLEAN
    #undef MEMIF_START_SEC_VAR_INIT_BOOLEAN
    #define BSW_START_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_INIT_BOOLEAN
    #undef MEMIF_STOP_SEC_VAR_INIT_BOOLEAN
    #define BSW_STOP_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"

/* Initialized RAM: 8 bit values */
#elif defined MEMIF_START_SEC_VAR_INIT_8
    #undef MEMIF_START_SEC_VAR_INIT_8
    #define BSW_START_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_INIT_8
    #undef MEMIF_STOP_SEC_VAR_INIT_8
    #define BSW_STOP_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"

/* Initialized RAM: 16 bit values */
#elif defined MEMIF_START_SEC_VAR_INIT_16
    #undef MEMIF_START_SEC_VAR_INIT_16
    #define BSW_START_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_INIT_16
    #undef MEMIF_STOP_SEC_VAR_INIT_16
    #define BSW_STOP_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"

/* Initialized RAM: 32 bit values */
#elif defined MEMIF_START_SEC_VAR_INIT_32
    #undef MEMIF_START_SEC_VAR_INIT_32
    #define BSW_START_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_INIT_32
    #undef MEMIF_STOP_SEC_VAR_INIT_32
    #define BSW_STOP_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"

/* Initialized RAM: unspecified size */
#elif defined MEMIF_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMIF_START_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMIF_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"

/* Variables located in saved zone */

/* Saved zone: 8 bit values */
#elif defined MEMIF_START_SEC_VAR_SAVED_ZONE_8
    #undef MEMIF_START_SEC_VAR_SAVED_ZONE_8
    #define BSW_START_SEC_SAVED_ZONE_8
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_SAVED_ZONE_8
    #undef MEMIF_STOP_SEC_VAR_SAVED_ZONE_8
    #define BSW_STOP_SEC_SAVED_ZONE_8
    #include "Bsw_MemMap.h"

/* Saved zone: 16 bit values */
#elif defined MEMIF_START_SEC_VAR_SAVED_ZONE_16
    #undef MEMIF_START_SEC_VAR_SAVED_ZONE_16
    #define BSW_START_SEC_SAVED_ZONE_16
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_SAVED_ZONE_16
    #undef MEMIF_STOP_SEC_VAR_SAVED_ZONE_16
    #define BSW_STOP_SEC_SAVED_ZONE_16
    #include "Bsw_MemMap.h"

/* Saved zone: 32 bit values */
#elif defined MEMIF_START_SEC_VAR_SAVED_ZONE_32
    #undef MEMIF_START_SEC_VAR_SAVED_ZONE_32
    #define BSW_START_SEC_SAVED_ZONE_32
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_SAVED_ZONE_32
    #undef MEMIF_STOP_SEC_VAR_SAVED_ZONE_32
    #define BSW_STOP_SEC_SAVED_ZONE_32
    #include "Bsw_MemMap.h"

/* Saved zone: unspecified size */
#elif defined MEMIF_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #undef MEMIF_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #define BSW_START_SEC_SAVED_ZONE_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #undef MEMIF_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #define BSW_STOP_SEC_SAVED_ZONE_UNSPECIFIED
    #include "Bsw_MemMap.h"

/*
 **********************************************************************************************************************
 * Constants mapping
 **********************************************************************************************************************
*/

/* Global or static Constants */

/* Const (ROM): 8 bit values */
#elif defined MEMIF_START_SEC_CONST_8
    #undef MEMIF_START_SEC_CONST_8
    #define BSW_START_SEC_CONST_8
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_CONST_8
    #undef MEMIF_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_CONST_8
    #include "Bsw_MemMap.h"

/* Const (ROM): 16 bit values */
#elif defined MEMIF_START_SEC_CONST_16
    #undef MEMIF_START_SEC_CONST_16
    #define BSW_START_SEC_CONST_16
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_CONST_16
    #undef MEMIF_STOP_SEC_CONST_16
    #define BSW_STOP_SEC_CONST_16
    #include "Bsw_MemMap.h"

/* Const (ROM): 32 bit values */
#elif defined MEMIF_START_SEC_CONST_32
    #undef MEMIF_START_SEC_CONST_32
    #define BSW_START_SEC_CONST_32
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_CONST_32
    #undef MEMIF_STOP_SEC_CONST_32
    #define BSW_STOP_SEC_CONST_32
    #include "Bsw_MemMap.h"

/* Const (ROM): unspecified size */
#elif defined MEMIF_START_SEC_CONST_UNSPECIFIED
    #undef MEMIF_START_SEC_CONST_UNSPECIFIED
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMIF_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"

/*
 **********************************************************************************************************************
 * Code mapping
 **********************************************************************************************************************
*/

/* Code located in normal code section  (not defined by Autosar!)*/

#elif defined MEMIF_START_SEC_CODE
    #undef MEMIF_START_SEC_CODE
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
#elif defined MEMIF_STOP_SEC_CODE
    #undef MEMIF_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"

/*********************************************************************************************************************/
#else
    #error "MemIf_MemMap.h: unknown MemMap define "
#endif
