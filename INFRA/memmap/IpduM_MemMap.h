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

/* MR12 RULE 1.2 VIOLATION: MemMap header concept - no protection against multiple inclusion intended */
#ifndef IPDUM_MEMMAP_H
#define IPDUM_MEMMAP_H

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


#if defined IPDUM_START_SEC_CONST_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef IPDUM_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined IPDUM_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef IPDUM_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined IPDUM_START_SEC_VAR_CLEARED_8
  #define BSW_START_SEC_VAR_CLEARED_8
  #include "Bsw_MemMap.h"
  #undef  IPDUM_START_SEC_VAR_CLEARED_8
  #undef MEMMAP_ERROR
#elif defined IPDUM_STOP_SEC_VAR_CLEARED_8
  #define BSW_STOP_SEC_VAR_CLEARED_8
  #include "Bsw_MemMap.h"
  #undef  IPDUM_STOP_SEC_VAR_CLEARED_8
  #undef MEMMAP_ERROR

#elif defined IPDUM_START_SEC_VAR_INIT_8
  #define BSW_START_SEC_VAR_INIT_8
  #include "Bsw_MemMap.h"
  #undef  IPDUM_START_SEC_VAR_INIT_8
  #undef MEMMAP_ERROR
#elif defined IPDUM_STOP_SEC_VAR_INIT_8
  #define BSW_STOP_SEC_VAR_INIT_8
  #include "Bsw_MemMap.h"
  #undef  IPDUM_STOP_SEC_VAR_INIT_8
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

#elif defined IPDUM_START_SEC_VAR_CLEARED_UNSPECIFIED
    /* UNSPECIFIED */
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef IPDUM_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined IPDUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef IPDUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
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
/* DEFAULT                normal or slow access        cyclic variable >= 10ms  */
/*----------------------------------------------------------------------------*/
#elif defined IPDUM_START_SEC_CODE
    #define  BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef IPDUM_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined IPDUM_STOP_SEC_CODE
    #define  BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef IPDUM_STOP_SEC_CODE
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "IpduM_MemMap.h, wrong #pragma command"
#endif

#undef IPDUM_MEMMAP_H
#endif /* #ifndef IPDUM_MEMMAP_H */
