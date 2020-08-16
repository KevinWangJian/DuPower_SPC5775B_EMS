

#include "Dem.h"
#include "Dem_Dcm.h"
#include "Rte_Dem.h"

#include "Dem_EvMemApi.h"

#include "Dem_EvMem.h"
#include "Dem_Lock.h"
#include "Dem_EnvMain.h"
#include "Dem_Mapping.h"
#include "Dem_DTCs.h"
#include "Dem_Obd.h"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
static Dem_DtcIdType DemDtcIdCopy;
static uint32 DemDtcCodeCopy;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

/* ----------------------------------------------------------------------------
   Sync Functions DCM <-> DEM
   ----------------------------------------------------------------------------
*/


/* ----------------------------------------------------------------------------
 Helper Function
 ----------------------------------------------------------------------------
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
uint16_least Dem_EvMemGetMemoryLocIdOfDtcAndOriginWithVisibility(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin, Dem_boolean_least ShadowEntriesVisible)
{
	if (DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
	{
		return Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (DtcId, DEM_CFG_EVMEM_MEMID_PRIMARY, ShadowEntriesVisible);
	}

#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
	if (DTCOrigin == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
	{
		return Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (DtcId, DEM_CFG_EVMEM_MEMID_SECONDARY, ShadowEntriesVisible);
	}
#endif

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
	if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
	{
		return Dem_EvMemGetEventMemoryLocIdOfDtc (DtcId, DEM_CFG_EVMEM_MEMID_MIRROR);
	}
#elif DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
	if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
	{
		return Dem_EvMemGetShadowMemoryLocIdOfDtc(DtcId, DEM_CFG_EVMEM_MEMID_SHADOW);
	}
#endif

	/* should never occur */
	return DEM_EVMEM_INVALID_LOCID;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/* ----------------------------------------------------------------------------
 Sync Functions DCM <-> DEM
 ----------------------------------------------------------------------------
 */

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06
#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
Dem_EvMemDTCRecordType Dem_EvMemDTCRecord;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
DEM_INLINE void Dem_EvMemInvalidateSyncDataRecord(void)
{
	DEM_ENTERLOCK_DCM();

	Dem_EvMemDTCRecord.DtcId = DEM_DTCID_INVALID;

    DEM_EXITLOCK_DCM();
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
static Dem_boolean_least Dem_EvMemReqSyncDataRecord(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin)
{

	Dem_boolean_least returnStatus;

	DEM_ENTERLOCK_DCM();

	if ((Dem_EvMemDTCRecord.DtcId != DtcId) || (Dem_EvMemDTCRecord.DTCOrigin != DTCOrigin))
	{
		Dem_EvMemDTCRecord.DtcId = DtcId;
		Dem_EvMemDTCRecord.DTCOrigin = DTCOrigin;
		Dem_EvMemDTCRecord.ReqCounter++;
	}
	returnStatus = (Dem_boolean_least)(Dem_EvMemDTCRecord.ReqCounter == Dem_EvMemDTCRecord.DemCounter);

	DEM_EXITLOCK_DCM();

	return returnStatus;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
void Dem_EvMemApiMainFunction(void)
{
#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06

	uint16_least LocId;
	Dem_DtcIdType DtcIdStored;
	Dem_DTCOriginType DTCOriginStored;
	uint8 ReqCounterStored;


	DEM_ENTERLOCK_DCM();

	/* local copy of request parameters */
	DtcIdStored = Dem_EvMemDTCRecord.DtcId;
	DTCOriginStored = Dem_EvMemDTCRecord.DTCOrigin;
	ReqCounterStored = Dem_EvMemDTCRecord.ReqCounter;

	if (ReqCounterStored != Dem_EvMemDTCRecord.DemCounter)
	{
		Dem_EvMemDTCRecord.IsValid = FALSE;
		if (Dem_isDtcIdValid (DtcIdStored))
		{
			LocId = Dem_EvMemGetMemoryLocIdOfDtcAndOriginWithVisibility(DtcIdStored, DTCOriginStored, Dem_EvMemGetShadowVisibility());
			Dem_EvMemDTCRecord.IsValid = (boolean) Dem_EvMemIsEventMemLocIdValid (LocId);
			if (Dem_EvMemDTCRecord.IsValid)
			{
				Dem_EvMemDTCRecord.EventMemory = Dem_EvMemEventMemory[LocId];
			}
		}
		Dem_EvMemDTCRecord.DemCounter = ReqCounterStored;
	}

	DEM_EXITLOCK_DCM();

#endif
}

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04 || DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06
/* ----------------------------------------------------------------------------
 Dem_DisableDTCRecordUpdate

 Description:   Disables the event memory update of a specific DTC (only one at one time)
 Attributes:    Synchronous/Non Reentrant

 DTC			Selects the DTC in UDS format, for which DTC record update shall be disabled.
 DTCOrigin		If the Dem supports more than one event memory,
                this parameter is used to select the source memory for which DTC record update shall be disabled.
 Return:        Status of the operation to disable the event memory update of a specific DTC.
 ----------------------------------------------------------------------------
 */

Dem_ReturnDisableDTCRecordUpdateType Dem_DisableDTCRecordUpdate(uint32 DTC,Dem_DTCOriginType DTCOrigin)
{
	DEM_UNUSED_PARAM(DTC);
	DEM_UNUSED_PARAM(DTCOrigin);

    Dem_EvMemInvalidateSyncDataRecord ();
	return DEM_DISABLE_DTCRECUP_OK;
}

/* ----------------------------------------------------------------------------
 Dem_EnableDTCRecordUpdate

 Description:   Enables the DTC record update
 Attributes:    Synchronous/Non Reentrant

 Return:        E_OK:     Operation was successful
 E_NOT_OK: Operation failed
 ----------------------------------------------------------------------------
 */
Std_ReturnType Dem_EnableDTCRecordUpdate(void)
{
	return E_OK;
}

#endif

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06
/* ----------------------------------------------------------------------------
 Dem_GetExtendedDataRecordByDTC

 Description:        Gets extended data by DTC. The function stores the data in the provided DestBuffer.
 Attributes:         Asynchronous/Non Reentrant

 DTC:                This is the DTC the 'Extended Data Record' is assigned to.
 DTCKind:            This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 DTCOrigin:          If the Dem supports more than one event memory, this parameter is used to select
                     the source memory the DTCs shall be read from.
 ExtendedDataNumber: Identification/Number of requested extended data record.
                     The values 0xFE and 0xFF are not allowed. Valid values are from 0x01 to 0xEF.
 DestBuffer:         This parameter contains a byte pointer that points to the buffer, to which the extended data record shall be written to.
                     The format is raw hexadecimal values and contains no header-information.
 BufSize:            When the function is called this parameter contains the maximum number of data bytes that can be written to the buffer.
                     The function returns the actual number of written data bytes in this parameter.
 Return:             Status of the operation to retrieve extended data by DTC.

 ----------------------------------------------------------------------------
 */

Dem_ReturnGetExtendedDataRecordByDTCType Dem_GetExtendedDataRecordByDTC(uint32 DTC,
		Dem_DTCKindType DTCKind,
		Dem_DTCOriginType DTCOrigin,
		uint8 ExtendedDataNumber,
		uint8* DestBuffer,
		uint16* BufSize)
{
	Dem_DtcIdType DtcId;
	Dem_EventIdType EventId;
	Dem_TriggerType Trigger;

	if (!Dem_EvMemIsDtcKindValid (DTCKind))
	{
		DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_RECORD_WRONG_DTCKIND;
	}

	if (!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
	{
		DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_RECORD_WRONG_DTCORIGIN;
	}

	if ((DestBuffer==NULL_PTR) || (BufSize==NULL_PTR))
	{
	    return DEM_RECORD_WRONG_BUFFERSIZE;
	}

	DtcId = Dem_DtcIdFromDtcCode (DTC);
	if (!Dem_DtcIsSupported (DtcId))
	{
		DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_RECORD_WRONG_DTC;
	}

	EventId = Dem_DtcIdGetFirstEventId (DtcId);

	if (!Dem_EnvIsEDRNumberValid (EventId, ExtendedDataNumber, &Trigger))
	{
	    /* According to AR the Dcm should iterate from 0x01 to 0xEF to retrieve the extended data records
	     * for a DTC => do not trigger the Det unless it's out of the range of allowed record numbers */
	    if ( (ExtendedDataNumber < 0x01) || (ExtendedDataNumber > 0xEF) )
	    {
	        DEM_DET(DEM_DET_APIID_GETEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
	    }
		return DEM_RECORD_WRONG_NUMBER;
	}

	if (!Dem_EvMemReqSyncDataRecord (DtcId, DTCOrigin))
	{
		return DEM_RECORD_PENDING;
	}

	if (!Dem_EvMemDTCRecord.IsValid)
	{ /* if DTC is defined but no record is stored, positive response and size 0 */
		*BufSize = 0;
		return DEM_RECORD_OK;
	}

	if (!Dem_EnvIsTriggerSet(Dem_EvMemGetEventMemTriggerByPtr(&Dem_EvMemDTCRecord.EventMemory), Trigger))
	{ /* if DTC is defined but no record is stored, positive response and size 0 */
		*BufSize = 0;
		return DEM_RECORD_OK;
	}

	/* Retrieve data */
	return Dem_EnvRetrieveEDR (Dem_EvMemGetEventMemEventIdByPtr(&(Dem_EvMemDTCRecord.EventMemory)), ExtendedDataNumber, DestBuffer, BufSize, Dem_EvMemGetEventMemDataByPtr (&(Dem_EvMemDTCRecord.EventMemory)), &(Dem_EvMemDTCRecord.EventMemory));

}

/* ----------------------------------------------------------------------------
 Dem_GetSizeOfExtendedDataRecordByDTC

 Description:        Gets the size of extended data by DTC.
 Attributes:         Asynchronous/Non Reentrant

 DTC:                      This is the DTC the 'Extended Data Record' is assigned to.
 DTCKind:                  This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 DTCOrigin:                If the Dem supports more than one event memory, this parameter is used to select
                           the source memory the DTCs shall be read from.
 ExtendedDataNumber:       Identification/Number of requested extended data record. Valid values are from 0x01 to 0xEF.
                           Additionally the values 0xFE and 0xFF are explicitly allowed to request the overall size of all OBD records / all records.
 SizeOfExtendedDataRecord: Pointer to Size of the requested data record
 Return:                   Status of the operation to retrieve the size of extended data..

 ----------------------------------------------------------------------------
 */

Dem_ReturnGetSizeOfExtendedDataRecordByDTCType Dem_GetSizeOfExtendedDataRecordByDTC(uint32 DTC,
		Dem_DTCKindType DTCKind,
		Dem_DTCOriginType DTCOrigin,
		uint8 ExtendedDataNumber,
		uint16* SizeOfExtendedDataRecord)
{
	Dem_DtcIdType DtcId;
	Dem_EventIdType EventId;
	Dem_TriggerType Trigger;

	if (!Dem_EvMemIsDtcKindValid (DTCKind))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFEDRBYDTC_W_DTCKI;
	}

	if (!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFEDRBYDTC_W_DTCOR;
	}

	DtcId = Dem_DtcIdFromDtcCode (DTC);
	if (!Dem_DtcIsSupported (DtcId))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFEDRBYDTC_W_DTC;
	}

	EventId = Dem_DtcIdGetFirstEventId (DtcId);

	if ((!Dem_EnvIsEDRNumberValid (EventId, ExtendedDataNumber, &Trigger)) && (ExtendedDataNumber != 0xFF))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFEXTENDEDDATARECORDBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFEDRBYDTC_W_RNUM;
	}

	if (ExtendedDataNumber == 0xFF)
	{	/* retrieve data size of all records */
		return Dem_EnvGetSizeOfED(EventId, SizeOfExtendedDataRecord);
	}
	else
	{	/* retrieve data size */
	    return Dem_EnvGetSizeOfEDR (EventId, ExtendedDataNumber, SizeOfExtendedDataRecord);
	}
}
#endif

#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04
/* ----------------------------------------------------------------------------
 Dem_GetFreezeFrameDataByDTC

 Description:        Gets freeze frame data by DTC. The function stores the data in the provided DestBuffer.
 Attributes:         Asynchronous/Non Reentrant

 DTC:                This is the DTC the freeze frame is assigned to.
 DTCKind:            This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 DTCOrigin:          If the DEM supports more than one event memory, this parameter is used to select
                     the source memory the DTCs shall be read from.
 RecordNumber:       This parameter is a unique identifier for a freeze frame record as defined in ISO 15031-5 and ISO 14229-1.
                     This record number is unique per DTC (relative addressing).
                     The value 0xFF is not allowed. The value 0x00 indicates the DTC-specific OBD freeze frame.
 DestBuffer:         This parameter contains a byte pointer that points to the buffer, to which the freeze frame data record shall be written to.
                     The format is: {RecordNumber, NumOfDIDs, DID[1], data[1], ..., DID[N], data[N]}
 BufSize:            When the function is called this parameter contains the maximum number of data bytes that can be written to the buffer.
                     The function returns the actual number of written data bytes in this parameter.
 Return:             Status of the operation to retrieve freeze frame data by DTC.

 ----------------------------------------------------------------------------
 */

Dem_ReturnGetFreezeFrameDataByDTCType Dem_GetFreezeFrameDataByDTC(uint32 DTC,
		Dem_DTCKindType DTCKind,
		Dem_DTCOriginType DTCOrigin,
		uint8 RecordNumber,
		uint8* DestBuffer,
		uint16* BufSize)
{
	Dem_DtcIdType DtcId;
	uint8 RecordIndex;
	Dem_EventIdType EventId;

	if (!Dem_EvMemIsDtcKindValid (DTCKind))
	{
		DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_FFDATABYDTC_WRONG_DTCKIND;
	}

	if (!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
	{
		DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN;
	}

	if ((DestBuffer==NULL_PTR) || (BufSize==NULL_PTR))
	{
	    return DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
	}

    if(DTC != DemDtcCodeCopy)
    {
        DemDtcIdCopy = Dem_DtcIdFromDtcCode (DTC);
        DemDtcCodeCopy = DTC;
    }
    DtcId = DemDtcIdCopy;

	if (!Dem_DtcIsSupported (DtcId))
	{
		DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_FFDATABYDTC_WRONG_DTC;
	}

	EventId = Dem_DtcIdGetFirstEventId (DtcId);

	if (RecordNumber == 0xFFu)
	{
        DEM_DET(DEM_DET_APIID_GETFREEZEFRAMEDATABYDTC, DEM_E_WRONG_CONFIGURATION);
        return DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
	}

	if (!Dem_EnvIsFFRecNumValid(EventId,RecordNumber))
	{
		return DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER;
	}

	if (!Dem_EvMemReqSyncDataRecord (DtcId, DTCOrigin))
	{
		return DEM_GET_FFDATABYDTC_PENDING;
	}

	if (!Dem_EvMemDTCRecord.IsValid)
	{ /* if DTC is defined but no record is stored, positive response and size 0 */
		*BufSize = 0;
		return DEM_GET_FFDATABYDTC_OK;
	}

	RecordIndex = Dem_EnvGetIndexFromFFRecNum (EventId, RecordNumber);

    if (! Dem_EnvIsFFRecNumStored(&Dem_EvMemDTCRecord.EventMemory, RecordNumber))
    { /* if DTC is defined but no record is stored, positive response and size 0 */
        *BufSize = 0;
        return DEM_GET_FFDATABYDTC_OK;
    }

    /* Retrieve data */
    return Dem_EnvRetrieveFF (Dem_EvMemGetEventMemEventIdByPtr(&(Dem_EvMemDTCRecord.EventMemory)), DestBuffer, BufSize, RecordIndex, Dem_EvMemGetEventMemDataByPtr (&(Dem_EvMemDTCRecord.EventMemory)), &(Dem_EvMemDTCRecord.EventMemory));

}

/* ----------------------------------------------------------------------------
 Dem_GetSizeOfFreezeFrameByDTC

 Description:        Gets the size of freeze frame data by DTC.
 Attributes:         Asynchronous/Non Reentrant

 DTC:                This is the DTC the freeze frame is assigned to.
 DTCKind:            This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 DTCOrigin:          If the DEM supports more than one event memory, this parameter is used to select
                     the source memory the DTCs shall be read from.
 RecordNumber:       This parameter is a unique identifier for a freeze frame record as defined in ISO 15031-5 and ISO 14229-1.
                     This record number is unique per DTC (relative addressing).
                     The value 0xFF is explicitly allowed to request the overall size.
 SizeOfFreezeFrame:  Number of bytes in the requested freeze frame record.
 Return:             Status of the operation to retrieve the size of freeze frame data.

 ----------------------------------------------------------------------------
 */

Dem_ReturnGetSizeOfFreezeFrameByDTCType Dem_GetSizeOfFreezeFrameByDTC(uint32 DTC,
		Dem_DTCKindType DTCKind,
		Dem_DTCOriginType DTCOrigin,
		uint8 RecordNumber,
		uint16* SizeOfFreezeFrame)
{
	Dem_DtcIdType DtcId;
	uint8  NoOfFreezeFrames;
	Dem_EventIdType EventId;
	Dem_ReturnGetSizeOfFreezeFrameByDTCType ReturnSts;

	if (!Dem_EvMemIsDtcKindValid (DTCKind))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFFF_WRONG_DTCKIND;
	}

	if (!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFFF_WRONG_DTCOR;
	}

    if(DTC != DemDtcCodeCopy)
    {
        DemDtcIdCopy = Dem_DtcIdFromDtcCode (DTC);
        DemDtcCodeCopy = DTC;
    }
    DtcId = DemDtcIdCopy;

	if (!Dem_DtcIsSupported (DtcId))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFFF_WRONG_DTC;
	}

	EventId = Dem_DtcIdGetFirstEventId (DtcId);

	if ((!Dem_EnvIsFFRecNumValid(EventId,RecordNumber)) && (RecordNumber != 0xFF))
	{
		DEM_DET(DEM_DET_APIID_GETSIZEOFFREEZEFRAMEBYDTC, DEM_E_WRONG_CONFIGURATION);
		return DEM_GET_SIZEOFFF_WRONG_RNUM;
	}

	/* Retrieve data size of single freeze frame*/
	ReturnSts = Dem_EnvGetSizeOfFF (EventId, SizeOfFreezeFrame);
	if (RecordNumber == 0xFF)
	{   /* data size for all freeze frames (RecordNumber = 0xFF) */
		NoOfFreezeFrames = Dem_EvtGetMaxNumberOfFreezeFrames(EventId);
		*SizeOfFreezeFrame = (*SizeOfFreezeFrame) * NoOfFreezeFrames;
	}

	/* Retrieve data size */
	return ReturnSts;
}
#endif
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


#if DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x03

/* static variables Dem_SetFreezeFrameRecordFilter and Dem_GetNextFilteredRecord */
#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
static uint16_least Dem_EvMemFilteredRecordLocId;
static uint16_least Dem_EvMemFilteredRecordFreezeFrameId;
/* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
static Dem_DTCFormatType Dem_EvMemFilteredRecordDTCFormat;
#endif
/* FC_VariationPoint_END */
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
/* ----------------------------------------------------------------------------
 Dem_SetFreezeFrameRecordFilter

 Description:        Sets a freeze frame record filter.
 Attributes:         Synchronous/Non Reentrant

 DTCFormat:          Defines the output-format of the requested DTC values for the sub-sequent API calls.
 NumberOfFilteredRecords: Number of freeze frame records currently stored in the event memory.
 Return:                  Status of the operation to (re-)set a freeze frame record filter.

 ----------------------------------------------------------------------------
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

Dem_ReturnSetFilterType Dem_SetFreezeFrameRecordFilter(Dem_DTCFormatType DTCFormat, uint16* NumberOfFilteredRecords)
{
	uint16_least LocId;
/* FC_VariationPoint_START */
#if (DEM_CFG_OBD == DEM_CFG_OBD_OFF)
/* FC_VariationPoint_END */
   if (DTCFormat == DEM_DTC_FORMAT_OBD)
   {
      return DEM_WRONG_FILTER;
   }
/* FC_VariationPoint_START */
#endif
/* FC_VariationPoint_END */
	*NumberOfFilteredRecords = 0;
/* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
	Dem_EvMemFilteredRecordDTCFormat = DTCFormat;
#endif
/* FC_VariationPoint_END */
	/* use primary memory */
	for (Dem_EvMemEventMemoryLocIteratorNew     (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
		 Dem_EvMemEventMemoryLocIteratorIsValid (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
		 Dem_EvMemEventMemoryLocIteratorNext    (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY))
	{
		if ( Dem_EvMemIsVisible(Dem_EvMemGetEventMemStatus(Dem_EvMemFilteredRecordLocId), Dem_EvMemGetShadowVisibility()))
		{
			LocId = Dem_EvMemFilteredRecordLocId;
			if (Dem_LibGetParamUI8(DEM_CFG_EVCOMB) == Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
			{
				LocId = Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility (Dem_DtcIdFromEventId (Dem_EvMemGetEventMemEventId (Dem_EvMemFilteredRecordLocId)), DEM_CFG_EVMEM_MEMID_PRIMARY, Dem_EvMemGetShadowVisibility());
			}

			if (LocId == Dem_EvMemFilteredRecordLocId)
			{
				*NumberOfFilteredRecords = *NumberOfFilteredRecords + (uint16) Dem_EvMemGetEventMemFreezeFrameCounter (Dem_EvMemFilteredRecordLocId);
			}
		}
	}

	/* initialize iterators for service Dem_GetNextFilteredRecord */
	Dem_EvMemEventMemoryLocIteratorNew (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	Dem_EvMemFilteredRecordFreezeFrameId = 0;

	return DEM_FILTER_ACCEPTED;
}

/* ----------------------------------------------------------------------------
 Dem_GetNextFilteredRecord

 Description:        Gets the current DTC and its associated snapshot record numbers from the Dem.
                     The interface has an asynchronous behavior, because NvRAM access might be required.
 Attributes:         Asynchronous/Non Reentrant

 DTC:                Receives the DTC value returned by the function.
                     If the return value of the function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 RecordNumber:       Freeze frame record number of the reported DTC (relative addressing).
                     If the return value of the function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 Return:             Gets the next freeze frame record number and its associated DTC stored in the event memory.

 ----------------------------------------------------------------------------
 */

Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredRecord(uint32* DTC, uint8* RecordNumber)
{
    uint16_least LocId;
	uint16_least Status;
	Dem_EventIdType EventId;
	uint16_least FreezeFrameCounter;

	while (Dem_EvMemEventMemoryLocIteratorIsValid (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY))
	{

		Status = Dem_EvMemGetEventMemStatus (Dem_EvMemFilteredRecordLocId);
		EventId = Dem_EvMemGetEventMemEventId (Dem_EvMemFilteredRecordLocId);
		FreezeFrameCounter = Dem_EvMemGetEventMemFreezeFrameCounter (Dem_EvMemFilteredRecordLocId);


		if ( Dem_EvMemIsVisible(Status, Dem_EvMemGetShadowVisibility()))
        {
            if (Dem_LibGetParamUI8(DEM_CFG_EVCOMB) == Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
            {
                if (Dem_EvMemFilteredRecordFreezeFrameId == 0u)
                {
                    LocId = Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility(Dem_DtcIdFromEventId(EventId),
                    DEM_CFG_EVMEM_MEMID_PRIMARY, Dem_EvMemGetShadowVisibility());
                    if (LocId != Dem_EvMemFilteredRecordLocId)
                    { /* set invalid freeze frame id */

                    	Dem_EvMemFilteredRecordFreezeFrameId = 0xFFu;
                    }
                }
            }
            if (Dem_LibGetParamUI8(DEM_CFG_FFRECNUM) == Dem_LibGetParamUI8(DEM_CFG_FFRECNUM_CALCULATED))
            {

                if (Dem_EvMemFilteredRecordFreezeFrameId < FreezeFrameCounter)
                { /* calculated freeze frame numbers (first freeze frame is 1) */
                    *RecordNumber = Dem_EnvGetFFRecNumFromIndex(EventId, (uint8) Dem_EvMemFilteredRecordFreezeFrameId);
                    /* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                    if (Dem_EvMemFilteredRecordDTCFormat == DEM_DTC_FORMAT_UDS)
                    {
                        *DTC = Dem_DtcGetCode(Dem_DtcIdFromEventId (EventId));
                    }
                    else /* DEM_DTC_FORMAT_OBD */
                    {
                        *DTC = rba_DemObdBasic_Dtc_GetCode(Dem_DtcIdFromEventId (EventId));
                    }
#else
                    /* FC_VariationPoint_END */
                    *DTC = Dem_DtcGetCode(Dem_DtcIdFromEventId(EventId));
                    /* FC_VariationPoint_START */
#endif
                    /* FC_VariationPoint_END */
                    Dem_EvMemFilteredRecordFreezeFrameId++;
                    return DEM_FILTERED_OK;
                }
                else
                {
                    Dem_EvMemFilteredRecordFreezeFrameId = 0;
                }
            }
            else
            {
                /* Check if FF ID is valid */
                if (Dem_EvMemFilteredRecordFreezeFrameId != 0xFFu)
                {
                    /* loop for all FFRecNums */
                    while (Dem_EvMemFilteredRecordFreezeFrameId < Dem_EvtGetMaxNumberOfFreezeFrames(EventId))
                    {

                        *RecordNumber = Dem_EnvGetFFRecNumFromIndex(EventId, (uint8) Dem_EvMemFilteredRecordFreezeFrameId);
                        /* If FF Stored */
                        if(Dem_EnvIsTriggerSet(Dem_EnvGetFFRecordTrigger(*RecordNumber) , Dem_EvMemGetEventMemTrigger(Dem_EvMemFilteredRecordLocId)))
                        {

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
                            if (Dem_EvMemFilteredRecordDTCFormat == DEM_DTC_FORMAT_UDS)
                            {
                                *DTC = Dem_DtcGetCode(Dem_DtcIdFromEventId (EventId));
                            }
                            else /* DEM_DTC_FORMAT_OBD */
                            {
                                *DTC = rba_DemObdBasic_Dtc_GetCode(Dem_DtcIdFromEventId (EventId));
                            }
#else
                            *DTC = Dem_DtcGetCode(Dem_DtcIdFromEventId(EventId));
#endif
                            /* Update FFIdIterator */
                            Dem_EvMemFilteredRecordFreezeFrameId++;
                            /* Return FILTERED_OK */
                            return DEM_FILTERED_OK;
                        }
                        Dem_EvMemFilteredRecordFreezeFrameId++;
                    }
                }

                Dem_EvMemFilteredRecordFreezeFrameId = 0;
            }
        }
		Dem_EvMemEventMemoryLocIteratorNext (&Dem_EvMemFilteredRecordLocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	}
	return DEM_FILTERED_NO_MATCHING_DTC;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
Dem_ReadEventType Dem_ReadEventsFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_DTCOriginType origin)
{
	ReadEventsFromMemoryState->evMemId = Dem_EvMemGetEvMemIdFromOrigin(origin);
	if (Dem_EvMemIsOriginSupported(origin))
	{
		Dem_EvMemEventMemoryLocIteratorNew (&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId);
		return DEM_READEVENT_OK;
	}
	else
	{
		Dem_EvMemEventMemoryLocIteratorInvalidate(&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId);
		return DEM_READEVENT_WRONG_ORIGIN;
	}
}

Dem_ReadEventType Dem_GetNextEventFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_EventIdType* EventId, uint16* LocId)
{
	while (Dem_EvMemEventMemoryLocIteratorIsValid (&ReadEventsFromMemoryState->locIterator, ReadEventsFromMemoryState->evMemId))
	{
		*EventId = Dem_EvMemGetEventMemEventId (ReadEventsFromMemoryState->locIterator);
		/* Location Index to be filled here before updating next LocId */
		*LocId = (uint16)ReadEventsFromMemoryState->locIterator;
		Dem_EvMemEventMemoryLocIteratorNext (&ReadEventsFromMemoryState->locIterator,ReadEventsFromMemoryState->evMemId);

		if (Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus((uint16_least)*LocId)))
		{
			return DEM_READEVENT_OK;
		}
	}
	return DEM_READEVENT_NO_MATCHING_ELEMENT;
}

DEM_INLINE uint8 Dem_EvMemGetNoOfEntries(uint16_least MemId)
{
    uint16_least LocId;
    uint8 counter = 0;

    if (Dem_EvMemIsMemIdValid(MemId))
    {
        for (Dem_EvMemEventMemoryLocIteratorNew(&LocId, MemId); Dem_EvMemEventMemoryLocIteratorIsValid(&LocId, MemId);
                Dem_EvMemEventMemoryLocIteratorNext(&LocId, MemId))
        {
            if (Dem_EvMemIsStored(Dem_EvMemGetEventMemStatus(LocId)))
            {
                counter++;
            }
        }
    }
    return counter;
}

Std_ReturnType Dem_GetNumberOfEventMemoryEntries(Dem_DTCOriginType DTCOrigin, uint8* NumberOfEventMemoryEntries)
{
    Std_ReturnType retVal = E_NOT_OK;

    /*Entry Condition Check */
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES,E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(NumberOfEventMemoryEntries,DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES,E_NOT_OK);
    if (!Dem_EvMemIsDtcOriginValid(&DTCOrigin))
    {
        DEM_DET(DEM_DET_APIID_DEM_EVMEMGETNUMBEROFEVENTENTRIES, DEM_E_WRONG_CONFIGURATION);
        retVal = E_NOT_OK;
    }

    if (DTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_PRIMARY);
        retVal = E_OK;
    }

#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
    if (DTCOrigin == DEM_DTC_ORIGIN_SECONDARY_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_SECONDARY);
        retVal = E_OK;
    }
#endif

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
    if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_MIRROR);
        retVal = E_OK;
    }
#elif DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
    if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
    {
        *NumberOfEventMemoryEntries = Dem_EvMemGetNoOfEntries(DEM_CFG_EVMEM_MEMID_SHADOW);
        retVal = E_OK;
    }
#endif
    return retVal;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

