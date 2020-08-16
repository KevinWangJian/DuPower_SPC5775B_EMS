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



/* MemMap.h for AUTOSAR Memory Mapping */

/* MR12 RULE 1.2 VIOLATION: MemMap header concept - no protection against multiple inclusion intended*/
#ifndef RBA_ETHTCP_MEMMAP_H
#define RBA_ETHTCP_MEMMAP_H

#define MEMMAP_ERROR

/* ---- Section mapping for rba_EthTcp  --------------------------------- */
#if defined RBA_ETHTCP_START_SEC_CONST_8
    #define BSW_START_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_CONST_8
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_CONST_8
    #define BSW_STOP_SEC_DEFAULT_CONST_8
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_CONST_8
    #undef MEMMAP_ERROR

#elif defined RBA_ETHTCP_START_SEC_CONST_16
    #define BSW_START_SEC_DEFAULT_CONST_16
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_CONST_16
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_CONST_16
    #define BSW_STOP_SEC_DEFAULT_CONST_16
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_CONST_16
    #undef MEMMAP_ERROR

#elif defined RBA_ETHTCP_START_SEC_CONST_32
    #define BSW_START_SEC_DEFAULT_CONST_32
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_CONST_32
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_CONST_32
    #define BSW_STOP_SEC_DEFAULT_CONST_32
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_CONST_32
    #undef MEMMAP_ERROR

#elif defined RBA_ETHTCP_START_SEC_CONST_UNSPECIFIED
    /* Unspecified size */
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

/*----------------------------------------------------------------------------*/
/* Used for global or static variables that are
    cleared to zero after every reset */
/*----------------------------------------------------------------------------*/

#elif defined RBA_ETHTCP_START_SEC_VAR_CLEARED_8
    /*  8 bit */
    #define BSW_START_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_CLEARED_8
    #define BSW_STOP_SEC_VAR_CLEARED_8
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_CLEARED_8
    #undef MEMMAP_ERROR

#elif defined RBA_ETHTCP_START_SEC_VAR_CLEARED_16
    /* 16 bit */
    #define BSW_START_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_CLEARED_16
    #define BSW_STOP_SEC_VAR_CLEARED_16
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_CLEARED_16
    #undef MEMMAP_ERROR

#elif defined RBA_ETHTCP_START_SEC_VAR_CLEARED_32
    /* 32 bit */
    #define BSW_START_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_VAR_CLEARED_32
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_CLEARED_32
    #undef MEMMAP_ERROR

#elif defined RBA_ETHTCP_START_SEC_VAR_CLEARED_UNSPECIFIED
    /* UNSPECIFIED */
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef MEMMAP_ERROR

/*----------------------------------------------------------------------------*/
/* Used for global or static variables that are
    initialized to values after every reset */
/*----------------------------------------------------------------------------*/

 /*  8 bit */
#elif defined RBA_ETHTCP_START_SEC_VAR_INIT_8
    #define BSW_START_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_INIT_8
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_INIT_8
    #define BSW_STOP_SEC_VAR_INIT_8
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_INIT_8
    #undef MEMMAP_ERROR

 /*  16 bit */
#elif defined RBA_ETHTCP_START_SEC_VAR_INIT_16
    #define BSW_START_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_INIT_16
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_INIT_16
    #define BSW_STOP_SEC_VAR_INIT_16
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_INIT_16
    #undef MEMMAP_ERROR

 /*  32 bit */
#elif defined RBA_ETHTCP_START_SEC_VAR_INIT_32
    #define BSW_START_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_INIT_32
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_INIT_32
    #define BSW_STOP_SEC_VAR_INIT_32
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_INIT_32
    #undef MEMMAP_ERROR

	/* UNSPECIFIED */
#elif defined RBA_ETHTCP_START_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_VAR_INIT_UNSPECIFIED
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#elif defined RBA_ETHTCP_START_SEC_CODE
    #define  BSW_START_SEC_DEFAULT_CODE
	#include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_CODE
    #define  BSW_STOP_SEC_DEFAULT_CODE
	#include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_CODE
    #undef MEMMAP_ERROR

/* Code that shall go into fast code memory segments - Scratchpad Memory (SPRAM) */
#elif defined RBA_ETHTCP_START_SEC_CODE_FAST
    #define  BSW_START_SEC_SPRAM_CODE
	#include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_START_SEC_CODE_FAST
    #undef MEMMAP_ERROR
#elif defined RBA_ETHTCP_STOP_SEC_CODE_FAST
    #define  BSW_STOP_SEC_SPRAM_CODE
	#include "Bsw_MemMap.h"
    #undef RBA_ETHTCP_STOP_SEC_CODE_FAST
    #undef MEMMAP_ERROR

#elif defined MEMMAP_ERROR
    #error "rba_EthTcp_MemMap.h, wrong #pragma command"
#endif

#undef RBA_ETHTCP_MEMMAP_H
#endif
/* -------- END OF FILE ------------------------------------------------------- */

