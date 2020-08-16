

#ifndef DEM_DISTURBANCEMEMORY_H
#define DEM_DISTURBANCEMEMORY_H


#include "Dem_Types.h"

#include "Dem_Array.h"
#include "rba_DiagLib_Bits8.h"
#include "rba_DiagLib_Bits16.h"
#include "Dem_Events.h"
#include "Dem_Cfg_DistMem.h"
#include "Dem_Cfg_EnvMain.h"
#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE == DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE_ON)
#include "Dem_PrjDisturbanceMemory.h"
#endif



#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)


#define DEM_DIST_MEM_BP_FLAG_TEST_CURRENT      (0u)
#define DEM_DIST_MEM_BP_FLAG_TEST_DISTURBED    (1u)
#define DEM_DIST_MEM_BP_UPDATE_EXTN_DATA       (2u)




typedef uint8 Dem_DistMemLocationStatusType;
#define DEM_DIST_MEM_ISBITSET      rba_DiagLib_Bit8IsBitSet
#define DEM_DIST_MEM_OVERWRITEBIT  rba_DiagLib_Bit8OverwriteBit
#define DEM_DIST_MEM_CLEARBIT      rba_DiagLib_Bit8ClearBit
#define DEM_DIST_MEM_SETBIT        rba_DiagLib_Bit8SetBit


/* Location 0 in Disturbance Memory is considered as Invalid location */
#define DEM_DIST_MEM_INVALID_LOC  		0u
/* After Dem_Init, Events stored back from NvM to Disturbance Memory, events get the default status 0
   Default status flag with TEST_CURRENT-0,TEST_DISTURBED-0 & UpdateExtndata Required No */
#define DEM_DIST_MEM_INIT_STATUS_BYTE	0u
/* Events stored to  Disturbance Memory first time gets the default status TEST_CURRENT-1,TEST_DISTURBED-0 & UpdateExtndata Required Yes */
#define DEM_DIST_MEM_NEW_ENTRY_STATUS_BYTE ((uint8)(1u<<DEM_DIST_MEM_BP_FLAG_TEST_CURRENT) | (uint8)(1u<<DEM_DIST_MEM_BP_UPDATE_EXTN_DATA))

#define DEM_DIST_MEM_MAX_DIST_CTR_LIMIT  255u
/*---Disturbance memory storage type ---------------------------------------------------------------------------------*/
/* Type that holds the elements of disturbance memory structure. EventId ,disturbanceCtr ,env data & debug data stored in
   This type holds the elements that are stored persistently in NvRam */

typedef struct
{
	uint8 disturbanceCtr;
#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
	uint8 extData[DEM_CFG_DIST_MEM_EXT_DATA_SIZE];
#endif
	Dem_EventIdType eventId;
	#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
	Dem_DebugDataType debug0;
	Dem_DebugDataType debug1;
	#endif
#if(DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE == DEM_CFG_DIST_MEM_CALLBACK_ON_DISTURBANCE_ON)
	Dem_DistMemPrjDataType distMemPrjData;
#endif
} Dem_DistMemLocationType;


/* RAM block base address - #define DEM_DIST_MEM_NVRAM_RAM_BASE_ADDRESS &Dem_DistMemLocations[1]
and size is size-of(Dem_DistMemLocationsType) * DEM_CFG_DISTURBANCE_MEMORY_SIZE */


/*---GLOBAL VARIABLES  declaration ---------------------------------------------------------------------------------*/
#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE( Dem_DistMemLocationType, Dem_DistMemLocations, (DEM_CFG_DISTURBANCE_MEMORY_ARRAYLENGTH));
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
extern uint8 Dem_DistMemNextEmptyIndex;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE( Dem_DistMemLocationStatusType, Dem_DistMemLocationsStatus, (DEM_CFG_DISTURBANCE_MEMORY_ARRAYLENGTH));
extern uint8 Dem_DistMemReadIndex;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"




/*-- EVENT ID in DISTURBANCE MEMORY---------------------------------------------------------------------------------*/


DEM_INLINE Dem_EventIdType Dem_DistMemGetStoredEventId (uint8 DistMemIndex)
{
   return Dem_DistMemLocations[DistMemIndex].eventId;
}

DEM_INLINE void Dem_DistMemSetStoredEventId (uint8 DistMemIndex , Dem_EventIdType EventId)
{
   Dem_DistMemLocations[DistMemIndex].eventId = EventId;
}

/*-- DISTURBANCE COUNTER in DISTURBANCE MEMORY---------------------------------------------------------------------------------*/
DEM_INLINE uint8 Dem_DistMemGetStoredDisturbanceCounter (uint8 DistMemIndex)
{
   return Dem_DistMemLocations[DistMemIndex].disturbanceCtr;
}

/*-- TEST_CURRENT FLAG----------------------------------------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_DistMemEvtGetTestCurrent_Flag (uint8 DistMemIndex)
{
   return DEM_DIST_MEM_ISBITSET (Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_CURRENT);
}


DEM_INLINE void Dem_DistMemEvtWriteTestCurrent_Flag (uint8 DistMemIndex , Dem_boolean_least setBit )
{
	DEM_DIST_MEM_OVERWRITEBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_CURRENT , setBit);
}



/*-- TEST_DISTURBED FLAG--------------------------------------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_DistMemEvtGetTestDisturbed_Flag (uint8 DistMemIndex)
{
   return DEM_DIST_MEM_ISBITSET (Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_DISTURBED);
}

DEM_INLINE void Dem_DistMemEvtSetTestDisturbed_Flag (uint8 DistMemIndex)
{
	DEM_DIST_MEM_SETBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_FLAG_TEST_DISTURBED);
}



/*-- UPDATE_EXTN_DATA FLAG------------------------------------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_DistMemIsUpdateEvtExtDataNecessary (uint8 DistMemIndex)
{
   return DEM_DIST_MEM_ISBITSET (Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_UPDATE_EXTN_DATA);
}

DEM_INLINE void Dem_DistMemRequestUpdateEvtExtData (uint8 DistMemIndex)
{
	DEM_DIST_MEM_SETBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_UPDATE_EXTN_DATA);
}

DEM_INLINE void Dem_DistMemClearUpdateEvtExtData (uint8 DistMemIndex)
{
	DEM_DIST_MEM_CLEARBIT (&Dem_DistMemLocationsStatus[DistMemIndex], DEM_DIST_MEM_BP_UPDATE_EXTN_DATA);
}

/*-- DISTURBANCE MEMORY EVENTS STATUS BYTE AS A WHOLE---------------------------------------------------------------*/


DEM_INLINE void Dem_DistMemSetStatusByte (uint8 DistMemIndex , uint8 newStatus)
{
	Dem_DistMemLocationsStatus[DistMemIndex] = newStatus;
}





/*-- DISTURBANCE MEMORY ENV DATA--------------------------------------------------------------------------------------*/

#if(DEM_CFG_DIST_MEM_EXTENDED_DATA_USED == STD_ON)
DEM_INLINE void Dem_DistMemGetEnvData (uint8 DistMemIndex ,uint8* dest, uint8 size)
{
	DEM_MEMCPY(dest, Dem_DistMemLocations[DistMemIndex].extData , size );
}
#endif



/*---APIs  declaration ---------------------------------------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_DistMemIsFull (void)
{
	return (Dem_DistMemNextEmptyIndex == 0);
}


DEM_INLINE Dem_boolean_least Dem_DistMemIsReportFailedNecessary (Dem_EventIdType eventId, Dem_EventStatusType eventStatus)
{
   return (   ((eventStatus==DEM_EVENT_STATUS_FAILED) || (eventStatus==DEM_EVENT_STATUS_PREFAILED))
		   && (Dem_EvtIsEventStoredInDistMem(eventId) || !Dem_DistMemIsFull()));
}



#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_DistMemReportFailed(Dem_EventIdType EventId
							 DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0, Dem_DebugDataType debug1));
void Dem_DistMemReportPassed(Dem_EventIdType EventId);

void Dem_DistMemInitCheckNvM(void);
void Dem_DistMemInit(void);
void Dem_DistMemMainFunction(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif


#endif
