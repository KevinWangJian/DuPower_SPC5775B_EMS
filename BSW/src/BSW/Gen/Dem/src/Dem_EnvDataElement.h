
#ifndef DEM_ENVDATAELEMENT_H
#define DEM_ENVDATAELEMENT_H

#include "Dem_Types.h"
#include "Dem_Lib.h"
#include "Dem_Cfg_EnvDataElement.h"
#include "Dem_InternalEnvData.h"


typedef Std_ReturnType (*Dem_ReadExternalDataElementFnc)(uint8* Buffer);
typedef Std_ReturnType (*Dem_ReadInternalDataElementFnc)(uint8* Buffer, const Dem_InternalEnvData* internalData);


typedef struct
{
#if (DEM_CFG_ENV_DATAELEMENTS_EXTERN_AVAILABILITY == STD_ON)
    Dem_ReadExternalDataElementFnc ReadExternalFnc;
#endif
#if (DEM_CFG_ENV_DATAELEMENTS_INTERN_AVAILABILITY == STD_ON)
    Dem_ReadInternalDataElementFnc ReadInternalFnc;
#endif
    uint8 Size;
	boolean captureOnRetrieve;
} Dem_EnvDataElement;


#if (DEM_CFG_ENV_DATAELEMENTS_EXTERN_AVAILABILITY == STD_ON)
#define DEM_ENV_DATAELEMENTS_EXTCS_INIT(VAL)   (VAL),
#else
#define DEM_ENV_DATAELEMENTS_EXTCS_INIT(VAL)
#endif

#if (DEM_CFG_ENV_DATAELEMENTS_INTERN_AVAILABILITY == STD_ON)
#define DEM_ENV_DATAELEMENTS_INTERN_INIT(VAL)   (VAL),
#else
#define DEM_ENV_DATAELEMENTS_INTERN_INIT(VAL)
#endif

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const Dem_EnvDataElement Dem_Cfg_EnvDataElement[DEM_CFG_ENV_DATAELEMENTS_ARRAYLENGTH];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

DEM_INLINE void Dem_EnvInsertPadding(uint8* const* start, uint8 size)
{
	DEM_MEMSET(*start,0xFF,size);
}

DEM_INLINE void Dem_EnvDACapture(uint8 dataElementId, uint8** start, const uint8* end, const Dem_InternalEnvData* internalEnvData)
{
	Std_ReturnType result = E_NOT_OK;
	DEM_ASSERT((*start + Dem_Cfg_EnvDataElement[dataElementId].Size) <= end,DEM_DET_APIID_ENVDACAPTURE, 0);

	if (!Dem_Cfg_EnvDataElement[dataElementId].captureOnRetrieve)
	{
		#if (DEM_CFG_ENV_DATAELEMENTS_EXTERN_AVAILABILITY == STD_ON)
		if (Dem_Cfg_EnvDataElement[dataElementId].ReadExternalFnc != NULL_PTR)
		{
			result = (Dem_Cfg_EnvDataElement[dataElementId].ReadExternalFnc)(*start);
		}
		#endif

		#if (DEM_CFG_ENV_DATAELEMENTS_INTERN_AVAILABILITY == STD_ON)
		if (Dem_Cfg_EnvDataElement[dataElementId].ReadInternalFnc != NULL_PTR)
		{
			result = (Dem_Cfg_EnvDataElement[dataElementId].ReadInternalFnc)(*start, internalEnvData);
		}
		#endif

		if (result != E_OK)
		{
			Dem_EnvInsertPadding (start, Dem_Cfg_EnvDataElement[dataElementId].Size);
			DEM_DET(DEM_DET_APIID_ENVDACAPTURE, DEM_E_NODATAAVAILABLE);
		}
	}
	else
	{
		Dem_EnvInsertPadding (start, Dem_Cfg_EnvDataElement[dataElementId].Size);
	}

	*start += Dem_Cfg_EnvDataElement[dataElementId].Size;
}

DEM_INLINE void Dem_EnvDACopy(uint8 dataElementId, uint8** start, const uint8* end, const uint8** src)
{
	DEM_ASSERT((*start + Dem_Cfg_EnvDataElement[dataElementId].Size) <= end, DEM_DET_APIID_ENVDAUPDATE, 0);

	DEM_MEMCPY(*start, *src, Dem_Cfg_EnvDataElement[dataElementId].Size);
	*start += Dem_Cfg_EnvDataElement[dataElementId].Size;
	*src += Dem_Cfg_EnvDataElement[dataElementId].Size;
}

DEM_INLINE void Dem_EnvDASkip(uint8 dataElementId, uint8** start, const uint8* end, const uint8** src)
{
	DEM_ASSERT((*start + Dem_Cfg_EnvDataElement[dataElementId].Size) <= end, DEM_DET_APIID_ENVDASKIP, 0);

	*start += Dem_Cfg_EnvDataElement[dataElementId].Size;
	*src += Dem_Cfg_EnvDataElement[dataElementId].Size;
}

/* copies DataElement data from input stream to output stream. if capture on retrieve
 is configured, the data is captured and directly written to output stream */
DEM_INLINE Dem_boolean_least Dem_EnvDARetrieve(uint8 dataElementId,
		uint8** start,
		const uint8* end,
		const uint8** src,
		const Dem_InternalEnvData* internalEnvData)
{
	Std_ReturnType result = E_NOT_OK;

	if ((*start + Dem_Cfg_EnvDataElement[dataElementId].Size )> end)
	{
		return FALSE;
	}

	if (Dem_Cfg_EnvDataElement[dataElementId].captureOnRetrieve)
	{
#if (DEM_CFG_ENV_DATAELEMENTS_EXTERN_AVAILABILITY == STD_ON)
		if (Dem_Cfg_EnvDataElement[dataElementId].ReadExternalFnc != NULL_PTR)
		{
			result = (Dem_Cfg_EnvDataElement[dataElementId].ReadExternalFnc)(*start);
		}
#endif

#if (DEM_CFG_ENV_DATAELEMENTS_INTERN_AVAILABILITY == STD_ON)
		if (Dem_Cfg_EnvDataElement[dataElementId].ReadInternalFnc != NULL_PTR)
		{
			result = (Dem_Cfg_EnvDataElement[dataElementId].ReadInternalFnc)(*start, internalEnvData);
		}
#endif

		if (result != E_OK)
		{
			Dem_EnvInsertPadding (start, Dem_Cfg_EnvDataElement[dataElementId].Size);
			DEM_DET(DEM_DET_APIID_ENVDARETRIEVE, DEM_E_NODATAAVAILABLE);
		}
	}
	else
	{
	    DEM_MEMCPY(*start, *src, Dem_Cfg_EnvDataElement[dataElementId].Size);
	}
	*start += Dem_Cfg_EnvDataElement[dataElementId].Size;
	*src += Dem_Cfg_EnvDataElement[dataElementId].Size;
	return TRUE;
}

DEM_INLINE uint8 Dem_EnvDAGetSizeOf(uint8 dataElementId)
{
	return Dem_Cfg_EnvDataElement[dataElementId].Size;
}
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#if (DEM_CFG_READDEM_DEBUG0_SUPPORTED)
Std_ReturnType Dem_ReadDebug0(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_DEBUG1_SUPPORTED)
Std_ReturnType Dem_ReadDebug1(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

Std_ReturnType Dem_ReadEventStatusByte( uint8* buffer, const Dem_InternalEnvData* internalData );

#if (DEM_CFG_READDEM_AGINGCTR_UPCNT_SUPPORTED)
Std_ReturnType Dem_ReadAgingCtr(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_OCCCTR_SUPPORTED)
Std_ReturnType Dem_ReadOccCtr(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_SIGNIFICANCE_SUPPORTED)
Std_ReturnType Dem_ReadSignificance(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_OVFLIND_SUPPORTED)
Std_ReturnType Dem_ReadOvflInd(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_CURRENT_FDC_SUPPORTED)
Std_ReturnType Dem_ReadCurrentFDC(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED)
Std_ReturnType Dem_ReadMaxFdcDuringCurrentCycle(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED)
Std_ReturnType Dem_ReadMaxFdcSinceLastClear(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_CYCLES_SINCE_FIRST_FAILED_SUPPORTED)
Std_ReturnType Dem_ReadCyclesSinceFirstFailed(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED)
Std_ReturnType Dem_ReadCyclesSinceLastFailed(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED)
Std_ReturnType Dem_ReadCyclesSinceLastFailedExcludingTNC(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_FAILED_CYCLES_SUPPORTED)
Std_ReturnType Dem_ReadFailedCycles(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#if (DEM_CFG_READDEM_EVENT_ID_SUPPORTED)
Std_ReturnType Dem_ReadEventId(uint8* Buffer, const Dem_InternalEnvData* internalData);
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif
