

#include "Dem.h"

#include "Dem_DisturbanceMemory.h"

#include "Dem_Events.h"
#include "Dem_EventStatus.h"
#include "Dem_Nvm.h"
#include "Dem_EnvMain.h"
#include "Dem_Main.h"


#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)


/*----------------Global Variables definition-----------------------------------------------------------------------*/
#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DEFINE( Dem_DistMemLocationType, Dem_DistMemLocations, DEM_CFG_DISTURBANCE_MEMORY_ARRAYLENGTH);
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
uint8 Dem_DistMemNextEmptyIndex = DEM_CFG_DISTURBANCE_MEMORY_SIZE;
static boolean Dem_DistMemIsLocked = FALSE;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DEFINE( Dem_DistMemLocationStatusType, Dem_DistMemLocationsStatus, DEM_CFG_DISTURBANCE_MEMORY_ARRAYLENGTH);
uint8 Dem_DistMemReadIndex;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"



/*----------------Disturbance Memory - Interfaces-----------------------------------------------------------------------*/
DEM_INLINE void Dem_DistMemReArrangeEvents (void)
{
	uint8 tempNextStoreIndex;
	uint8 ctr;

	tempNextStoreIndex = DEM_CFG_DISTURBANCE_MEMORY_SIZE;	  /* Re arrangement has to be evaluated beginning from end index */
	DEM_ENTERLOCK_MON();
	for(ctr = DEM_CFG_DISTURBANCE_MEMORY_SIZE; ctr > 0; ctr--)
	{
		if((Dem_DistMemLocations[ctr].eventId != DEM_EVENTID_INVALID) && (Dem_DistMemLocations[ctr].disturbanceCtr != 0))/* event to be retained */
		{
			/* if a event with disturbance ctr>0 found, and there was an empty location before this location then replace and remove here */
			if(ctr < tempNextStoreIndex)
			{
				/* relocate the event to new location */
				DEM_MEMCPY(&Dem_DistMemLocations[tempNextStoreIndex], &Dem_DistMemLocations[ctr], DEM_SIZEOF_TYPE(Dem_DistMemLocationType));
				/* update the events distmem_index */
				Dem_DistMemSetStatusByte(tempNextStoreIndex , DEM_DIST_MEM_INIT_STATUS_BYTE);
				Dem_EvtSetEventsDistMemIndex(Dem_DistMemLocations[tempNextStoreIndex].eventId, tempNextStoreIndex);

				/* remove the event from original location
				   Not clearing debug,env data, status byte explicitly here, since the location
				   is set to Invalid which is sufficient */
				Dem_DistMemSetStoredEventId(ctr , DEM_EVENTID_INVALID);

			}
			tempNextStoreIndex--;
		}
		else /* disturbance ctr is 0, event to be removed */
		{
		    /* Not clearing debug,env data, status byte explicitly here, since the location
			 is set to Invalid which is sufficient */
			Dem_EvtSetEventsDistMemIndex (Dem_DistMemLocations[ctr].eventId, DEM_DIST_MEM_INVALID_LOC);
			Dem_DistMemSetStoredEventId (ctr , DEM_EVENTID_INVALID);
		}
	}
	Dem_DistMemNextEmptyIndex = tempNextStoreIndex;
	DEM_EXITLOCK_MON(); /* TBD - locking time */
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
Std_ReturnType Dem_ClearDisturbanceMemory (void)
{
	uint8 ctr;
	DEM_ENTERLOCK_MON();

	/*clearing until valid entry in Disturbance Memory*/
	for(ctr = DEM_CFG_DISTURBANCE_MEMORY_SIZE; ctr > Dem_DistMemNextEmptyIndex; ctr--)
	{
		/* Clear the event table index of the  stored event */
		Dem_EvtSetEventsDistMemIndex(Dem_DistMemGetStoredEventId(ctr) , DEM_DIST_MEM_INVALID_LOC);
		/* NOTE - debug,env data, status byte not cleared explicitly ,bcos
		location is set to Invalid which is sufficient
		Initialize the Next empty index to start Index

		remove the event - Set the event stored as invalid. */
		Dem_DistMemSetStoredEventId(ctr , DEM_EVENTID_INVALID);
	}
	Dem_DistMemNextEmptyIndex = DEM_CFG_DISTURBANCE_MEMORY_SIZE;
	DEM_EXITLOCK_MON();
	return E_OK;
}

/*Called from De-bounce module when the report to Dem_SetEventStatus is Pre-passed or passed
for the events which is already stored in Disturbance memory allowing it to increment the disturbance ctr if
the last report is pre-failed and the event was not in De-bounce threshold limit
NOTE:This implementation is done only for Dem_DebCounterClass_Filter - needs to be extended for AR ctr based and time based filters also*/

void Dem_DistMemReportPassed(Dem_EventIdType EventId)
{
    uint8 eventDistMemIndex;
    if(!Dem_DistMemIsLocked )
    {

        if (Dem_OpMoIsInitialized())
        {
            if(Dem_EvtIsEventStoredInDistMem(EventId))
            {
            /* Update disturbed flag & disturbed Ctr(until 255 max only) if TestCurrent flag changed 1->0 & */
            DEM_ENTERLOCK_MON();
            eventDistMemIndex = Dem_EvtGetEventsDistMemIndex(EventId);
            if(Dem_DistMemEvtGetTestCurrent_Flag(eventDistMemIndex))
            {
                Dem_DistMemEvtSetTestDisturbed_Flag(eventDistMemIndex);
                if(Dem_DistMemLocations[eventDistMemIndex].disturbanceCtr < DEM_DIST_MEM_MAX_DIST_CTR_LIMIT )
                {
                    Dem_DistMemLocations[eventDistMemIndex].disturbanceCtr++;
                }
                Dem_DistMemEvtWriteTestCurrent_Flag (eventDistMemIndex, FALSE);
            }
            DEM_EXITLOCK_MON();
                /* callback after every disturbance, allowing to capture project specific data on disturbances*/
#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE == DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE_ON)
                Dem_PrjDistMemCallbackOnDisturbance(EventId);
#endif
            }
        }
        else
        {
            DEM_DET(DEM_DET_APIID_DISTMEMORY, DEM_E_UNINIT);
            return;
        }
    }
    else
    {
        return;
    }
}


void Dem_DistMemReportFailed(Dem_EventIdType EventId
        					 DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1))
{
	if(!Dem_DistMemIsLocked )
	{
		Dem_boolean_least updateData = FALSE;
		uint8 eventDistMemIndex = 0;

		DEM_ENTERLOCK_MON();

    /*If event is already stored in DistMem, Update the record if required */
    /* Update of disturbance ctr is done through call to Dem_DistMemReportPassed */
		if(Dem_EvtIsEventStoredInDistMem(EventId))
		{
			eventDistMemIndex = Dem_EvtGetEventsDistMemIndex(EventId);

    	/* Update Debug date and extended data if TestCurrent flag changed 0->1 */
			if(!Dem_DistMemEvtGetTestCurrent_Flag(eventDistMemIndex))
			{
				updateData = TRUE;
			}
		}
		else if (!Dem_DistMemIsFull()) 	/* If event is not stored yet in DistMem,and the report is PreFailed/Failed(current flag 1 enter(its ensured
        due to simultaneous processes, it has to be checked, that the DisMem is not full */
    	{
			eventDistMemIndex = Dem_DistMemNextEmptyIndex;

			Dem_DistMemNextEmptyIndex --;
			Dem_EvtSetEventsDistMemIndex(EventId, eventDistMemIndex);

        /* the new Event with reported Test failed ,EventId is stored in the next empty location of Dist.Mem */
			Dem_DistMemLocations[eventDistMemIndex].eventId = EventId;
			Dem_DistMemLocations[eventDistMemIndex].disturbanceCtr = 0;

        /* Initial value on new entry of event: TEST_CURRENT=1, TEST_DISTURBED=0, UPDATEEXTDATA_REQUIRED=1 */
			Dem_DistMemSetStatusByte(eventDistMemIndex , DEM_DIST_MEM_NEW_ENTRY_STATUS_BYTE);

			updateData = TRUE;
    	}
		else
		{
    	/* To avoid Misra Warning */
		}

		if (updateData)
		{
			Dem_DistMemEvtWriteTestCurrent_Flag (eventDistMemIndex, TRUE);

	#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
			Dem_DistMemLocations[eventDistMemIndex].debug0 = debug0;
			Dem_DistMemLocations[eventDistMemIndex].debug1 = debug1;
	#endif

		/* Set extended flag to update the data in distMem in the next main function */
	#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
			Dem_DistMemRequestUpdateEvtExtData(eventDistMemIndex);
	#endif
		}

		DEM_EXITLOCK_MON();
	}
	else
	{
		return;
	}
}


/* Called from DemMain function to update Extended data of any events in DistMem if required */
void Dem_DistMemMainFunction(void)
{

#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
	uint8 ctr;
	Dem_boolean_least capture = FALSE;

	for(ctr = DEM_CFG_DISTURBANCE_MEMORY_SIZE; ctr > Dem_DistMemNextEmptyIndex; ctr--)
	{
		if(Dem_DistMemIsUpdateEvtExtDataNecessary(ctr))
		{
			DEM_ENTERLOCK_MON();
			if(Dem_DistMemIsUpdateEvtExtDataNecessary(ctr))
			{
				Dem_DistMemClearUpdateEvtExtData(ctr);
				capture = TRUE;
			}

			if (capture)
			{
				Dem_EnvCaptureForDisturbanceMemory(Dem_DistMemLocations[ctr].eventId,
						Dem_DistMemLocations[ctr].extData,
						DEM_CFG_DIST_MEM_EXT_DATA_SIZE
						DEM_DEBUGDATA_PARAM(Dem_DistMemLocations[ctr].debug0, Dem_DistMemLocations[ctr].debug1));
				capture = FALSE;
			}
            DEM_EXITLOCK_MON();
		}
	}
#endif
}

/* called from Dem_Init to validate the Nv block */
void Dem_DistMemInitCheckNvM(void)
{
	Dem_NvmResultType NvmResult;
    uint8 ctr;

    if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
    {
        /* Zero the content of the record */
        DEM_MEMSET( &Dem_DistMemLocations, 0x00, DEM_SIZEOF_VAR(Dem_DistMemLocations) );
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_DISTURBANCE_MEMORY);
    }
    else
    {
        /* get the Result of the NvM-Read (NvM_ReadAll) */
        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_DISTURBANCE_MEMORY);

        /* data successfull read */
        if (NvmResult == DEM_NVM_SUCCESS)
        {
            for(ctr = DEM_CFG_DISTURBANCE_MEMORY_SIZE; ctr > 0; ctr--)
            {
                /* Check if eventid stored in the location is valid */
                if(!Dem_isEventIdValid(Dem_DistMemLocations[ctr].eventId))
                {
                    /* Zero the content of that particular location */
                    DEM_MEMSET( &Dem_DistMemLocations[ctr], 0x00, DEM_SIZEOF_VAR(Dem_DistMemLocations[ctr]) );
                    Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DISTURBANCE_MEMORY);
                }
            }
        }
        else
        {
            /* Zero the content of the record */
            DEM_MEMSET( &Dem_DistMemLocations, 0x00, DEM_SIZEOF_VAR(Dem_DistMemLocations) );
            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DISTURBANCE_MEMORY);
        }
    }

}

/* called from Dem_Init. Initialize internal variables. backup from NvM */
void Dem_DistMemInit(void)
{
	/* TBC pending
	   Store back from NvM - Event Id,DisturbanceCtr,Env data and debug info are from previous POC.
	   Though status flag is taken from NvM backup, its re calculated once again below in this function.. */

	/* Re arrange the valid events(with disturbance ctr > 0) to end index */
	Dem_DistMemReArrangeEvents();
}


Std_ReturnType Dem_ReadDisturbanceMemory (void)
{
	// Initialize the read index
	Dem_DistMemReadIndex = DEM_CFG_DISTURBANCE_MEMORY_SIZE;

	return E_OK;
}

Std_ReturnType Dem_GetNextDisturbanceData (Dem_EventIdType* EventId, uint8* DestBuffer, uint8* BufSize)
{
	Std_ReturnType retVal = E_NOT_OK;
	uint8 disMem_DataSize;
	uint8 arrayindex;

	//Calculate the actual buffer size
	disMem_DataSize = 4u

#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
			+(uint8)(2u*(DEM_SIZEOF_TYPE(Dem_DebugDataType)))
#endif
#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
			+DEM_CFG_DIST_MEM_EXT_DATA_SIZE
#endif
#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE == DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE_ON)
            + DEM_CFG_DIST_MEM_PRJ_DATA_SIZE
#endif
			;

	if((EventId == NULL_PTR)||(DestBuffer == NULL_PTR)||(BufSize == NULL_PTR))
	{
		return E_NOT_OK;
	}

	DEM_ENTERLOCK_MON();

	// Ensure that data's are available for the requested event id in the disturbance memory
	if(Dem_DistMemReadIndex != Dem_DistMemNextEmptyIndex)
	{
		// Check whether the data can fit into the available buffer size
		if((*BufSize) >= disMem_DataSize)
		{
			//Calculate the EventId for the current disturbance memory location
			*EventId = Dem_DistMemGetStoredEventId(Dem_DistMemReadIndex);

			// Get the EventStatusExtended into the buffer
			*DestBuffer = (uint8)Dem_EvtGetIsoByte(*EventId);
			DestBuffer++;

			// Get the DisturbanceStatus
			*DestBuffer = ( ((uint8)(DEM_BOOL2BIT(Dem_DistMemEvtGetTestDisturbed_Flag(Dem_DistMemReadIndex)) << 1u))
			              | DEM_BOOL2BIT(Dem_DistMemEvtGetTestCurrent_Flag(Dem_DistMemReadIndex)) );
			DestBuffer++;

			//check whether the debugdata is supported or not, and if supported check the size which is configured
#if (DEM_CFG_DEBUGDATA == DEM_CFG_DEBUGDATA_8BIT)
			// Copy the DisturbanceEventDebugData debugdata0 and debugdata1
			*DestBuffer = Dem_DistMemLocations[Dem_DistMemReadIndex].debug0;
			DestBuffer++;
			*DestBuffer = Dem_DistMemLocations[Dem_DistMemReadIndex].debug1;
			DestBuffer++;

#endif
#if (DEM_CFG_DEBUGDATA == DEM_CFG_DEBUGDATA_32BIT)
			// Copy the DisturbanceEventDebugData debugdata0 which is of 4bytes (Supported bigendian)
			*DestBuffer = (uint8)((Dem_DistMemLocations[Dem_DistMemReadIndex].debug0)>>24u);
			DestBuffer++;
			*DestBuffer = (uint8)((Dem_DistMemLocations[Dem_DistMemReadIndex].debug0) >>16u);
			DestBuffer++;
			*DestBuffer = (uint8)((Dem_DistMemLocations[Dem_DistMemReadIndex].debug0)>>8u);
			DestBuffer++;
			*DestBuffer = (uint8)(Dem_DistMemLocations[Dem_DistMemReadIndex].debug0);
			DestBuffer++;

			// Copy the DisturbanceEventDebugData debugdata1 which is of 4bytes
			*DestBuffer = (uint8)((Dem_DistMemLocations[Dem_DistMemReadIndex].debug1)>>24u);
			DestBuffer++;
			*DestBuffer = (uint8)((Dem_DistMemLocations[Dem_DistMemReadIndex].debug1)>>16u);
			DestBuffer++;
			*DestBuffer = (uint8)((Dem_DistMemLocations[Dem_DistMemReadIndex].debug1)>>8u);
			DestBuffer++;
			*DestBuffer = (uint8)(Dem_DistMemLocations[Dem_DistMemReadIndex].debug1);
			DestBuffer++;
#endif

			//Get the DisturbanceGeneralStatusFlags
			*DestBuffer = DEM_BOOL2BIT(Dem_DistMemEvtGetTestCurrent_Flag(Dem_DistMemReadIndex));
			DestBuffer++;

			//Get the DisturbanceCounter and load it into the buffer
			*DestBuffer = Dem_DistMemGetStoredDisturbanceCounter(Dem_DistMemReadIndex);
			DestBuffer++;

			// Check whether the Extended data usage is supported
#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
			//Copy the Extended data into the buffer
			for(arrayindex = 0; arrayindex < DEM_CFG_DIST_MEM_EXT_DATA_SIZE; arrayindex++)
			{
				*DestBuffer = Dem_DistMemLocations[Dem_DistMemReadIndex].extData[arrayindex];
				DestBuffer++;
			}
#endif
#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE == DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE_ON)
			/*After this function call there should not be any  update for DestBuffer happens*/
			Dem_GetNextDisturbanceMemProjData(Dem_DistMemReadIndex, DestBuffer);
#endif

			// Update the actual buffer size into the inout parameter
			*BufSize = disMem_DataSize;

			//Decrement the read index to point to the next index
			Dem_DistMemReadIndex--;

			retVal =  E_OK;
		}
		else
		{
			//Return E_NOT_OK since the destbuffer is too small
			retVal =  E_NOT_OK;
		}
	}
	else
	{
		// no element found and out parameters are undefined
		retVal =  E_NOT_OK;
	}
	DEM_EXITLOCK_MON();

	return retVal;
}

Std_ReturnType Dem_LockDisturbanceMemory(boolean Lock)
{

    DEM_ENTERLOCK_MON();
    Dem_DistMemIsLocked = Lock;
    DEM_EXITLOCK_MON();

    return E_OK;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif

