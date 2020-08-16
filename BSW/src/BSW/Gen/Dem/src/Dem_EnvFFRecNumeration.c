


#include "Dem_EnvFFRecNumeration.h"

#if (DEM_CFG_FFRECNUM == DEM_CFG_FFRECNUM_CONFIGURED)

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
const uint8 Dem_Cfg_EnvFFRecNumConf[DEM_CFG_FFRECCLASS_NUMBEROF_FFRECCLASSES][DEM_CFG_FFRECCLASS_MAXNUMBEROF_FFFRECNUMS] = DEM_CFG_FFRECNUMCLASSES;
const Dem_EnvFFRec Dem_Cfg_EnvFFRec[DEM_CFG_ENVFFREC_ARRAYLENGTH] = DEM_CFG_ENVFFREC;
#if DEM_CFG_FFRECCLASS_NUMBEROF_FFRECCLASSES > 1
DEM_ARRAY_DEFINE_CONST(uint8, Dem_Cfg_EnvEventId2FrecNumClass, DEM_EVENTID_ARRAYLENGTH, DEM_CFG_ENVEVENTID2FFRECNUMCLASS);
#endif
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

uint8 Dem_EnvGetIndexOfFFRecConf(Dem_EventIdType EventId, uint8 RecNumber)
{
	uint8 idx;

	DEM_ASSERT(Dem_EvtGetMaxNumberOfFreezeFrames(EventId) <= DEM_CFG_FFRECCLASS_MAXNUMBEROF_FFFRECNUMS,DEM_DET_APIID_ENVGETINDEXOFCONFFFREC,0x0);
	for (idx = 0; idx < Dem_EvtGetMaxNumberOfFreezeFrames(EventId); idx++)
	{
		if (Dem_Cfg_EnvFFRecNumConf [Dem_EnvGetFFRecNumClassIndex(EventId)][idx] == RecNumber)
		{
			return idx;
		}
	}
	return DEM_ENV_FFRECNUM_INDEX_INVALID;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

