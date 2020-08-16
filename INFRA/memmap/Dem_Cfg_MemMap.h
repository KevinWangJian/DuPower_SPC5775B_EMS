/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




/* MemMap.h for AUTOSAR Dem R4.0 Rev 2 */

/**
 * \file
 * \ingroup DEM_PRJ_TPL
 * \brief Dem-specific memory mapping definitions
 *
 * Map the Dem memory sections to ECU-specific memory sections. For RTE-generated code, this file is included
 * indirectly via \ref Dem_MemMap.h_tpl "Dem_MemMap.h"
 */


/* MR12 DIR 4.10 VIOLATION: Multiple inclusion is needed and necessary for memmapping as per AUTOSAR */
#define DEM_MEMMAP_ERROR

/* ============================   BSW   ============================ */
#if defined DEM_START_SEC_RAM_CLEARED
    #if defined DEM_WAS_STARTED_SEC_RAM_CLEARED
        #error DEM_WAS_STARTED_SEC_RAM_CLEARED already defined
    #endif
    #define BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_RAM_CLEARED
    #define DEM_WAS_STARTED_SEC_RAM_CLEARED

#elif defined DEM_STOP_SEC_RAM_CLEARED
    #if ! defined DEM_WAS_STARTED_SEC_RAM_CLEARED
        #error DEM_STOP_SEC_RAM_CLEARED without START_SEC
    #else
        #undef DEM_WAS_STARTED_SEC_RAM_CLEARED
    #endif
    #define BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_RAM_CLEARED

#elif defined DEM_START_SEC_RAM_INIT
    #if defined DEM_WAS_STARTED_SEC_RAM_INIT
        #error DEM_WAS_STARTED_SEC_RAM_INIT already defined
    #endif
    #define BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_VAR_INIT_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_RAM_INIT
    #define DEM_WAS_STARTED_SEC_RAM_INIT

#elif defined DEM_STOP_SEC_RAM_INIT
    #if ! defined DEM_WAS_STARTED_SEC_RAM_INIT
        #error DEM_STOP_SEC_RAM_INIT without START_SEC
    #else
        #undef DEM_WAS_STARTED_SEC_RAM_INIT
    #endif
    #define BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_VAR_INIT_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_RAM_INIT

#elif defined DEM_START_SEC_ROM_CONST
    #if defined DEM_WAS_STARTED_SEC_ROM_CONST
        #error DEM_WAS_STARTED_SEC_ROM_CONST already defined
    #endif
    #define BSW_START_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_CONST_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_ROM_CONST
    #define DEM_WAS_STARTED_SEC_ROM_CONST

#elif defined DEM_STOP_SEC_ROM_CONST
    #if ! defined DEM_WAS_STARTED_SEC_ROM_CONST
        #error DEM_STOP_SEC_ROM_CONST without START_SEC
    #else
        #undef DEM_WAS_STARTED_SEC_ROM_CONST
    #endif
    #define BSW_STOP_SEC_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_CONST_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_ROM_CONST

#elif defined DEM_START_SEC_ROM_CODE
    #if defined DEM_WAS_STARTED_SEC_ROM_CODE
        #error DEM_WAS_STARTED_SEC_ROM_CODE already defined
    #endif
    #define BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_ROM_CODE
    #define DEM_WAS_STARTED_SEC_ROM_CODE

#elif defined DEM_STOP_SEC_ROM_CODE
    #if ! defined DEM_WAS_STARTED_SEC_ROM_CODE
        #error DEM_STOP_SEC_ROM_CODE without START_SEC
    #else
        #undef DEM_WAS_STARTED_SEC_ROM_CODE
    #endif
    #define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_ROM_CODE

#elif defined DEM_START_SEC_CODE
    #if defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE already defined
    #endif
    #define BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_CODE
    #define Dem_WAS_STARTED_SEC_CODE

#elif defined DEM_STOP_SEC_CODE
    #if ! defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE without START_SEC
    #else
        #undef Dem_WAS_STARTED_SEC_CODE
    #endif
    #define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_CODE


#elif defined Dem_START_SEC_CODE
    #if defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE already defined
    #endif
    #define BSW_START_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef Dem_START_SEC_CODE
    #define Dem_WAS_STARTED_SEC_CODE

#elif defined Dem_STOP_SEC_CODE
    #if ! defined Dem_WAS_STARTED_SEC_CODE
        #error Dem_WAS_STARTED_SEC_CODE without START_SEC
    #else
        #undef Dem_WAS_STARTED_SEC_CODE
    #endif
    #define BSW_STOP_SEC_CODE
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_CODE
    #undef DEM_MEMMAP_ERROR
    #undef Dem_STOP_SEC_CODE

#elif defined DEM_START_SEC_SAVED_ZONE
    #if defined DEM_WAS_STARTED_SEC_SAVED_ZONE
        #error DEM_WAS_STARTED_SEC_SAVED_ZONE already defined
    #endif
    #define BSW_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_START_SEC_SAVED_ZONE
    #define DEM_WAS_STARTED_SEC_SAVED_ZONE

#elif defined DEM_STOP_SEC_SAVED_ZONE
    #if ! defined DEM_WAS_STARTED_SEC_SAVED_ZONE
        #error DEM_WAS_STARTED_SEC_SAVED_ZONE without START_SEC
    #else
        #undef DEM_WAS_STARTED_SEC_SAVED_ZONE
    #endif
    #define BSW_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #include "Bsw_MemMap.h"
    #undef BSW_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
    #undef DEM_MEMMAP_ERROR
    #undef DEM_STOP_SEC_SAVED_ZONE

#elif defined DEM_MEMMAP_ERROR
    #error "Dem_MemMap.h, wrong #pragma command"
#endif

