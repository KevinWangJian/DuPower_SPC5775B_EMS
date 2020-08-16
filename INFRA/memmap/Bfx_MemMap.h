/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */

/* MISRA RULE 19.15 VIOLATION: The MemMap header shall have no include protection because of the concept of MemMap.
   The MemMep header could be included multiple times in a c file. */
   

#define EFX_MEMMAP_ERROR

/**********************************************************************************************************************
 **                                        Definitions for module Bfx                                                **
 *********************************************************************************************************************/

/* MISRA RULE 3.4 VIOLATION: The below pragma is set to map Normal configuration to Standard flash */
#if   defined (BFX_START_SEC_CODE)
    #define BSW_START_SEC_CODE
       #include "Bsw_MemMap.h"
       #undef BFX_START_SEC_CODE
       #undef BFX_MEMMAP_ERROR
#elif defined (BFX_STOP_SEC_CODE)
    #define BSW_STOP_SEC_CODE
       #include "Bsw_MemMap.h"
       #undef BFX_STOP_SEC_CODE
    #undef BFX_MEMMAP_ERROR

/* MISRA RULE 3.4 VIOLATION: The below pragma is set to map Slow configuration to Standard flash */
#elif defined (BFX_START_SEC_CODE_SLOW)
    #define BSW_START_SEC_CODE
       #include "Bsw_MemMap.h"
    # undef BFX_START_SEC_CODE_SLOW
    # undef BFX_MEMMAP_ERROR
#elif defined (BFX_STOP_SEC_CODE_SLOW)
    #define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    # undef BFX_STOP_SEC_CODE_SLOW
    # undef BFX_MEMMAP_ERROR

/* MISRA RULE 3.4 VIOLATION: The below pragma is to map Fast configuration to SPRAM */
#elif defined (BFX_START_SEC_CODE_FAST)
    #define BSW_START_SEC_CODE_FAST
      #include "Bsw_MemMap.h"
    # undef BFX_START_SEC_CODE_FAST
    # undef BFX_MEMMAP_ERROR
#elif defined (BFX_STOP_SEC_CODE_FAST)
    #define BSW_STOP_SEC_CODE_FAST
    #include "Bsw_MemMap.h"
    # undef BFX_STOP_SEC_CODE_FAST
    # undef BFX_MEMMAP_ERROR

#elif defined BFX_MEMMAP_ERROR
# error "Bfx_MemMap.h, wrong #pragma command"
#endif
