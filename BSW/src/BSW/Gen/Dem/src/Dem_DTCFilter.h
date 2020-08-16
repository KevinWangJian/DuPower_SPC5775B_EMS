

#ifndef DEM_DTCFILTER_H
#define DEM_DTCFILTER_H


#include "Dem_Types.h"
#include "Dem_DTCs.h"
#include "Dem_DTCStatusByte.h"

typedef struct
{
   boolean isNewFilterCriteria;
   uint8 DTCStatusMask;
   Dem_DTCKindType DTCKind;
   Dem_DTCFormatType DTCFormat;
   Dem_DTCOriginType DTCOrigin;
   Dem_FilterWithSeverityType FilterWithSeverity;
   Dem_DTCSeverityType DTCSeverityMask;
   Dem_FilterForFDCType FilterForFaultDetectionCounter;
   uint16 numberOfMatchingDTCs;
   Dem_DtcIdIterator searchIt, retrieveIt;
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   rba_DemObdBasic_DTCFilterState obdFilter;
#endif
} Dem_DTCFilterState;

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
    extern Dem_DTCFilterState Dem_DTCFilter;
    DEM_BITARRAY_DECLARE (Dem_DTCFilterMatching,DEM_DTCID_ARRAYLENGTH);
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

Dem_ReturnGetNumberOfFilteredDTCType Dem_GetNumberOfStandardFilteredDTC(uint16* NumberOfFilteredDTC);
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredStandardDTCID (Dem_DtcIdType* dtcId, uint32* DTC, uint8* DTCStatus, sint8* DTCFaultDetectionCounter);
void Dem_DTCFilterStandardMainFunction(void);

void Dem_SetDTCFilterstartIterator(void);
boolean Dem_IsStandardFilterFinished(const Dem_DtcIdIterator *it);
void Dem_DtcFilterInit(void);
void Dem_DTCFilterMainFunction(void);
Dem_boolean_least Dem_DTCFilterMatches (Dem_DtcIdType dtcId);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif
