

#ifndef DEM_INTERNALENVDATA_H
#define DEM_INTERNALENVDATA_H


#include "Dem_Types.h"
#include "Dem_EvMemTypes.h"

/**
 * Used to pass information about the event to internal data element read functions
 */
typedef struct
{
    /** Id of the event */
	Dem_EventIdType eventId;
#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
	/** Debug data */
	Dem_DebugDataType debug0;
	/** Debug data */
	Dem_DebugDataType debug1;
#endif
	/** Event memory location of the event. Only set on retrieval (otherwise == NULL_PTR) */
	Dem_EvMemEventMemoryType *evMemLocation;
} Dem_InternalEnvData;


#endif

