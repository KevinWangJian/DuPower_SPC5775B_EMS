
#ifndef DEM_EVMEMGENTYPES_H
#define DEM_EVMEMGENTYPES_H

#include "Dem_Types.h"
#include "Dem_Cfg_EvMem.h"

/* ----------------------------------------------------------------------------
   config
   ----------------------------------------------------------------------------
 */
#define DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE     5u
#define DEM_EVMEMGEN_OVERFLOW_ARRAYSIZE                      5u

/* ----------------------------------------------------------------------------
   sanity checks of ARRAY-Length
   ----------------------------------------------------------------------------
 */

#if  DEM_DTC_ORIGIN_PRIMARY_MEMORY >= DEM_EVMEMGEN_OVERFLOW_ARRAYSIZE
#error "Declarations of DTC-Origins does not match the array size of the Overflow Flag Array"
#endif
#if  DEM_DTC_ORIGIN_MIRROR_MEMORY >= DEM_EVMEMGEN_OVERFLOW_ARRAYSIZE
#error "Declarations of DTC-Origins does not match the array size of the Overflow Flag Array"
#endif
#if  DEM_DTC_ORIGIN_PERMANENT_MEMORY >= DEM_EVMEMGEN_OVERFLOW_ARRAYSIZE
#error "Declarations of DTC-Origins does not match the array size of the Overflow Flag Array"
#endif
#if  DEM_DTC_ORIGIN_SECONDARY_MEMORY >= DEM_EVMEMGEN_OVERFLOW_ARRAYSIZE
#error "Declarations of DTC-Origins does not match the array size of the Overflow Flag Array"
#endif

#if  DEM_FIRST_FAILED_DTC >= DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE
#error "Declarations of DTC-Requests does not match the array size of the DTC Occurrence Array"
#endif
#if  DEM_MOST_RECENT_FAILED_DTC >= DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE
#error "Declarations of DTC-Requests does not match the array size of the DTC Occurrence Array"
#endif
#if  DEM_FIRST_DET_CONFIRMED_DTC >= DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE
#error "Declarations of DTC-Requests does not match the array size of the DTC Occurrence Array"
#endif
#if  DEM_MOST_REC_DET_CONFIRMED_DTC >= DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE
#error "Declarations of DTC-Requests does not match the array size of the DTC Occurrence Array"
#endif

#endif

