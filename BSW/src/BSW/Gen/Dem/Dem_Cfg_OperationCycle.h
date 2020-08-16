/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_OPERATIONCYCLE_H
#define DEM_CFG_OPERATIONCYCLE_H

#include "rba_DiagLib_Bits8.h"
#include "rba_DiagLib_Bits16.h"
#include "rba_DiagLib_Bits32.h"

#define DEM_CFG_OPERATIONCYCLESTATUSSTORAGE_OFF  STD_OFF
#define DEM_CFG_OPERATIONCYCLESTATUSSTORAGE_ON   STD_ON

#define DEM_CFG_OPERATIONCYCLESTATUSSTORAGE      DEM_CFG_OPERATIONCYCLESTATUSSTORAGE_ON

#define DemConf_DemOperationCycle_DemOperationCycle_Power  0u

#define DEM_OPERATIONCYCLE_COUNT      1
#define DEM_OPERATIONCYCLE_BITSIZE    1
#define DEM_AGINGCYCLE_BITSIZE        DEM_OPERATIONCYCLE_BITSIZE
#define DEM_FAILURECYCLE_BITSIZE      DEM_OPERATIONCYCLE_BITSIZE

#if (DEM_OPERATIONCYCLE_COUNT <= 8)
typedef uint8 Dem_OperationCycleList;
#define DEM_OPERATIONCYCLE_SETBIT        rba_DiagLib_Bit8SetBit
#define DEM_OPERATIONCYCLE_CLEARBIT      rba_DiagLib_Bit8ClearBit
#define DEM_OPERATIONCYCLE_ISBITSET      rba_DiagLib_Bit8IsBitSet
#define DEM_OPERATIONCYCLE_BITMASK       rba_DiagLib_Bit8Mask
#define DEM_OPERATIONCYCLE_SETBITMASK    rba_DiagLib_Bit8SetBitMask
#define DEM_OPERATIONCYCLE_CLEARBITMASK  rba_DiagLib_Bit8ClearBitMask

#elif (DEM_OPERATIONCYCLE_COUNT <= 16)
typedef uint16 Dem_OperationCycleList;
#define DEM_OPERATIONCYCLE_SETBIT        rba_DiagLib_Bit16SetBit
#define DEM_OPERATIONCYCLE_CLEARBIT      rba_DiagLib_Bit16ClearBit
#define DEM_OPERATIONCYCLE_ISBITSET      rba_DiagLib_Bit16IsBitSet
#define DEM_OPERATIONCYCLE_BITMASK       rba_DiagLib_Bit16Mask
#define DEM_OPERATIONCYCLE_SETBITMASK    rba_DiagLib_Bit16SetBitMask
#define DEM_OPERATIONCYCLE_CLEARBITMASK  rba_DiagLib_Bit16ClearBitMask

#elif (DEM_OPERATIONCYCLE_COUNT <= 32)
typedef uint32 Dem_OperationCycleList;
#define DEM_OPERATIONCYCLE_SETBIT        rba_DiagLib_Bit32SetBit
#define DEM_OPERATIONCYCLE_CLEARBIT      rba_DiagLib_Bit32ClearBit
#define DEM_OPERATIONCYCLE_ISBITSET      rba_DiagLib_Bit32IsBitSet
#define DEM_OPERATIONCYCLE_BITMASK       rba_DiagLib_Bit32Mask
#define DEM_OPERATIONCYCLE_SETBITMASK    rba_DiagLib_Bit32SetBitMask
#define DEM_OPERATIONCYCLE_CLEARBITMASK  rba_DiagLib_Bit32ClearBitMask

#endif

#endif

