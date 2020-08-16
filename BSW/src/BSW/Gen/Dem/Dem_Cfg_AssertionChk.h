/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_ASSERTIONCHK_H
#define DEM_CFG_ASSERTIONCHK_H

#include "Dem_Lib.h"
#include "Dem_EventStatus.h"
#include "Dem_GenericNvData.h"
#include "Dem_DisturbanceMemory.h"
#include "Dem_Obd.h"

/* -------------------------------------------------- */
/* DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH       */
/* -------------------------------------------------- */
#define DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH_ON   STD_ON
#define DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH_OFF  STD_OFF
#define DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH  DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH_ON

#if(DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH == DEM_CFG_STATIC_ASSERTION_FOR_NVM_BLOCKLENGTH_ON)
/* Macros which defines the block size of each configured NvM Block */
#define  DEM_NVM_ID_DEM_GENERIC_NV_DATA_SIZE                16
#define  DEM_NVM_ID_EVMEM_LOC_0_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_1_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_2_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_3_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_4_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_5_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_6_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_7_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_8_SIZE                        164
#define  DEM_NVM_ID_EVMEM_LOC_9_SIZE                        164
#define  DEM_NVM_ID_EVT_STATUSBYTE_SIZE                     208

DEM_STATIC_ASSERT((DEM_SIZEOF_VAR(Dem_GenericNvData)==DEM_NVM_ID_DEM_GENERIC_NV_DATA_SIZE),DEM_NVM_ID_DEM_GENERIC_NV_DATA_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_0_SIZE),DEM_NVM_ID_EVMEM_LOC_0_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_1_SIZE),DEM_NVM_ID_EVMEM_LOC_1_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_2_SIZE),DEM_NVM_ID_EVMEM_LOC_2_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_3_SIZE),DEM_NVM_ID_EVMEM_LOC_3_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_4_SIZE),DEM_NVM_ID_EVMEM_LOC_4_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_5_SIZE),DEM_NVM_ID_EVMEM_LOC_5_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_6_SIZE),DEM_NVM_ID_EVMEM_LOC_6_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_7_SIZE),DEM_NVM_ID_EVMEM_LOC_7_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_8_SIZE),DEM_NVM_ID_EVMEM_LOC_8_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_TYPE(Dem_EvMemEventMemoryType)==DEM_NVM_ID_EVMEM_LOC_9_SIZE),DEM_NVM_ID_EVMEM_LOC_9_BlockLengthIsInvalid);
DEM_STATIC_ASSERT((DEM_SIZEOF_VAR(Dem_AllEventsStatusByte)==DEM_NVM_ID_EVT_STATUSBYTE_SIZE),DEM_NVM_ID_EVT_STATUSBYTE_BlockLengthIsInvalid);

#endif

#endif

