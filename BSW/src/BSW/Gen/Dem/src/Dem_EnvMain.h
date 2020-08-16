


#ifndef DEM_ENVMAIN_H
#define DEM_ENVMAIN_H


#include "Dem_Mapping.h"
#include "Dem_Cfg_EnvMain.h"
#include "Dem_Cfg_DistMem.h"
#include "Dem_EnvExtendedData.h"
#include "Dem_EnvFreezeFrame.h"
#include "Dem_EnvFFRecNumeration.h"



/* Dem-internal functions for capture, copy and update */

typedef struct
{
	uint8 extDataId;
	uint8 freezeFrameId;
} Dem_EnvDataMap;
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const Dem_EnvDataMap Dem_Cfg_EnvEventId2EnvData[DEM_EVENTID_ARRAYLENGTH];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

DEM_INLINE Dem_boolean_least Dem_EnvHasExtendedData(Dem_EventIdType EventId)
{
	return (Dem_Cfg_EnvEventId2EnvData[EventId].extDataId != 0);
}
DEM_INLINE Dem_boolean_least Dem_EnvHasFreezeFrame(Dem_EventIdType EventId)
{
	return (Dem_Cfg_EnvEventId2EnvData[EventId].freezeFrameId != 0);
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_EnvCaptureED (Dem_EventIdType EventId, uint8* dest, uint16 destSize DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));

#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
void Dem_EnvCaptureForDisturbanceMemory(Dem_EventIdType EventId, uint8* dest, uint16 destSize  DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));
#endif
void Dem_EnvCaptureFF (Dem_EventIdType EventId, uint8* dest, uint16 destSize DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));
void Dem_EnvCopyRawFF (Dem_EventIdType EventId, uint8* dest, uint16 destSize, uint8 ffIndex, const uint8* src);
void Dem_EnvCopyRawED (Dem_EventIdType EventId, uint8* dest, uint16 destSize, const uint8* src, Dem_EnvTriggerParamType* triggerParam);


/* Support functions for DCM-querries: Dem_GetExtendedDataRecordByDTC, Dem_GetFreezeFrameDataByDTC */

Dem_boolean_least Dem_EnvIsEDRNumberValid(Dem_EventIdType EventId, uint8 RecordNumber, Dem_TriggerType* trigger);
Dem_ReturnGetExtendedDataRecordByDTCType Dem_EnvRetrieveEDR(Dem_EventIdType EventId, uint8 RecordNumber, uint8* dest, uint16* destSize, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation); /* according Figure 49 */
Dem_ReturnGetFreezeFrameDataByDTCType Dem_EnvRetrieveFF(Dem_EventIdType EventId, uint8* dest, uint16* destSize, uint8 ffIndex, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation); /* according Figure 48 */

Dem_ReturnGetSizeOfExtendedDataRecordByDTCType Dem_EnvGetSizeOfEDR(Dem_EventIdType EventId, uint8 RecordNumber, uint16* size); /* according Figure 49 */
Dem_ReturnGetSizeOfExtendedDataRecordByDTCType Dem_EnvGetSizeOfED(Dem_EventIdType EventId, uint16* size);
Dem_ReturnGetSizeOfFreezeFrameByDTCType Dem_EnvGetSizeOfFF(Dem_EventIdType EventId, uint16* size); /* according Figure 48 */


/* Support functions for DLT: Dem_GetEventExtendedDataRecord, Dem_GetEventFreezeFrameData */

Std_ReturnType Dem_EnvRetrieveRawED(Dem_EventIdType EventId, uint8* dest, uint16* destSize, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
Dem_boolean_least Dem_EnvRetrieveRawEDR(Dem_EventIdType EventId, uint8 RecordNumber, uint8* dest, uint16* destSize, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
Std_ReturnType Dem_EnvRetrieveRawFF(Dem_EventIdType EventId, uint8* dest, uint16* destSize, uint8 ffIndex, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);
Dem_boolean_least Dem_EnvRetrieveRawDid(Dem_EventIdType EventId, uint8* dest, uint16* destSize, uint8 ffIndex, uint16 did, const uint8* src, Dem_EvMemEventMemoryType *evMemLocation);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

