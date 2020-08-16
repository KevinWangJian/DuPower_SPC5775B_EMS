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
 ***********************************************************************************************************************
 * MemMap Sections
 ***********************************************************************************************************************
 */

/* MISRA RULE 19.15 VIOLATION: MemMap header file should not have header file protection */
#define MEMMAP_ERROR

#if defined CANTP_START_SEC_VAR_CLEARED_8
#define BSW_START_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_VAR_CLEARED_8
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_VAR_CLEARED_8
#define BSW_STOP_SEC_VAR_CLEARED_8
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_VAR_CLEARED_8
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONST_UNSPECIFIED
#define BSW_START_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONST_UNSPECIFIED
#define BSW_STOP_SEC_CONST_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_CONST_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONST_8
#define BSW_START_SEC_CONST_8
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_CONST_8
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONST_8
#define BSW_STOP_SEC_CONST_8
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_CONST_8
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CODE
#define BSW_START_SEC_CODE
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_CODE
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CODE
#define BSW_STOP_SEC_CODE
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_CODE
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_FDCALLOUT_CODE
#define BSW_START_SEC_CODE
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_FDCALLOUT_CODE
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_FDCALLOUT_CODE
#define BSW_STOP_SEC_CODE
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_FDCALLOUT_CODE
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#define BSW_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_CONFIG_DATA_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#define BSW_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_CODE
#define BSW_START_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_CONFIG_CODE
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_CODE
#define BSW_STOP_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_CONFIG_CODE
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_CODE_POSTBUILD
#define BSW_START_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_CONFIG_CODE_POSTBUILD
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_CODE_POSTBUILD
#define BSW_STOP_SEC_DEFAULT_CODE
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_CONFIG_CODE_POSTBUILD
#undef MEMMAP_ERROR

#elif defined CANTP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#undef MEMMAP_ERROR
#elif defined CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#define BSW_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Bsw_MemMap.h"
#undef CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#undef MEMMAP_ERROR


#elif defined MEMMAP_ERROR
#error "CanTp_MemMap.h, wrong #pragma command"
#endif

/*
************************************************************************************************************************
* End of the file
************************************************************************************************************************
*/
