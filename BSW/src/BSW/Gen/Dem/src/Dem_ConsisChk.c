
#include "Dem_ConsisChk.h"

#include "Dem_Bfm.h"

#include "Dem_Mapping.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

static void Dem_ConsistencyCheckForFailedDTC(void)
{
	uint16_least LocId, EventMemStatus;
	uint32 MaxFailedTimeIdinEvMem = 0;
	Dem_EventIdType EventIdForMaxFailedTimeId = 0;
	Dem_DtcIdType LastFailed_DtcId;

	for (Dem_EvMemEventMemoryLocIteratorNew     (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	     Dem_EvMemEventMemoryLocIteratorIsValid (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	     Dem_EvMemEventMemoryLocIteratorNext    (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY))
	{
	    EventMemStatus = Dem_EvMemGetEventMemStatus (LocId);

	    //check for the location is empty
	    if (!Dem_EvMemIsEmpty (EventMemStatus))
	    {
	        //Get the TimeStamp of the latest failed event
	        if((EventMemStatus & DEM_EVMEM_STSMASK_TESTFAILED) != 0u)
	        {
	            //Get the maximum TimeStamp and the eventId for that particular location
	            if(Dem_EvMemEventMemory[LocId].TimeId > MaxFailedTimeIdinEvMem)
	            {
	                MaxFailedTimeIdinEvMem = Dem_EvMemEventMemory[LocId].TimeId;
	                EventIdForMaxFailedTimeId = Dem_EvMemGetEventMemEventId(LocId);
	            }
	        }
	    }
	}

	//Get the Last Failed DTC ID
	LastFailed_DtcId = Dem_DtcIdFromEventId (EventIdForMaxFailedTimeId);

	//check if the Dtc Id already exist in the EvMem and it is the recently updated location
	if((MaxFailedTimeIdinEvMem != 0u) && (Dem_isDtcIdValid (LastFailed_DtcId)))
	{
		//Update the Id of the DTCOccurenceByTime in the GenericNvdata
		Dem_EvMemGenSetDtcByOccIndex(LastFailed_DtcId,DEM_MOST_RECENT_FAILED_DTC);
	}
}

static void Dem_ConsistencyCheckForConfirmedDTC(void)
{
	uint16_least LocId, EventMemStatus;
	uint32 MaxConfirmedTimeIdinEvMem = 0;
	Dem_EventIdType EventIdForMaxConfirmedTimeId = 0;
	Dem_DtcIdType LastConfirmed_DtcId;

	for (Dem_EvMemEventMemoryLocIteratorNew     (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	     Dem_EvMemEventMemoryLocIteratorIsValid (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY);
	     Dem_EvMemEventMemoryLocIteratorNext    (&LocId, DEM_CFG_EVMEM_MEMID_PRIMARY))

	{
	    EventMemStatus = Dem_EvMemGetEventMemStatus (LocId);

	    //check for the location is empty
	    if (!Dem_EvMemIsEmpty (EventMemStatus))
	    {
	        //Get the TimeStamp for latest confirmed event
	        if((EventMemStatus & DEM_EVMEM_STSMASK_CONFIRMED) != 0u)
	        {
	            //Get the maximum TimeStamp and the eventId for that particular location
	            if(Dem_EvMemEventMemory[LocId].TimeId > MaxConfirmedTimeIdinEvMem)
	            {
	                MaxConfirmedTimeIdinEvMem = Dem_EvMemEventMemory[LocId].TimeId;
	                EventIdForMaxConfirmedTimeId = Dem_EvMemGetEventMemEventId(LocId);
	            }
	        }
	    }

	}

	//Get the Last Confirmed DTC ID
	LastConfirmed_DtcId = Dem_DtcIdFromEventId (EventIdForMaxConfirmedTimeId);

	//check if the Dtc Id already exist in the EvMem and it is the recently updated location
	if((MaxConfirmedTimeIdinEvMem != 0u) && (Dem_isDtcIdValid (LastConfirmed_DtcId)))
	{
		//Update the Id of the DTCOccurenceByTime in the GenericNvdata
		Dem_EvMemGenSetDtcByOccIndex(LastConfirmed_DtcId,DEM_MOST_REC_DET_CONFIRMED_DTC);
	}
}

void Dem_ConsistencyCheckForDTC(void)
{
	//Check whether the Last failed DTC stored in the GenNv data is invalid or out of range
	if (!Dem_isDtcIdValid(Dem_EvMemGenGetLastFailedDtcFromGenNvData()))
	{
		Dem_ConsistencyCheckForFailedDTC();
	}

	//Check whether the Last confirmed DTC stored in the GenNv data is invalid or out of range
	if (!Dem_isDtcIdValid(Dem_EvMemGenGetLastConfirmedDtcFromGenNvData()))
	{
		Dem_ConsistencyCheckForConfirmedDTC();
	}
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
