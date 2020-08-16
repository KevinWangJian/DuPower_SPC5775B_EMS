


#ifndef DEM_MAPPING_H
#define DEM_MAPPING_H


#include "Dem_Types.h"
#include "Dem_Lib.h"

#include "Dem_Cfg_EventId.h"
#include "Dem_Cfg_DtcId.h"
#include "Dem_Cfg_NodeId.h"
#include "Dem_Cfg_Nodes.h"
#include "Dem_Cfg_EventIndicators.h"


/*** EVENTID *****************************************************************/

DEM_INLINE Dem_boolean_least Dem_isEventIdValid(Dem_EventIdType checkID)
{
   return ((0 < checkID) && (checkID <= DEM_EVENTID_COUNT));
}

/*Iterator for EventId*/

typedef uint16_least Dem_EventIdIterator; /* do not change to uint8_least */


#define DEM_EVENTIDITERATORNEW  1
DEM_INLINE void Dem_EventIdIteratorNew(Dem_EventIdIterator *it)
{
   (*it) = DEM_EVENTIDITERATORNEW;
}

DEM_INLINE Dem_boolean_least Dem_EventIdIteratorIsValid(const Dem_EventIdIterator *it)
{
   return (*it <= DEM_EVENTID_COUNT);
}

DEM_INLINE void Dem_EventIdIteratorNext(Dem_EventIdIterator *it)
{
   (*it)++;
}

DEM_INLINE Dem_EventIdType Dem_EventIdIteratorCurrent(const Dem_EventIdIterator *it)
{
   return (Dem_EventIdType)(*it);
}

/*** NODEID *****************************************************************/

#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const Dem_ComponentIdType  Dem_MapEventIdToNodeId[DEM_EVENTID_ARRAYLENGTH];
extern const Dem_EventIdType Dem_MapNodeIdToEventId[DEM_NODEID_ARRAYLENGTH];
extern const Dem_ComponentIdType  Dem_MapNodeIdToChildNodeId[DEM_CFG_CHILDNODE_LISTLENGTH];
extern const uint16 Dem_NodeToChildNodeIndex [DEM_NODEID_ARRAYLENGTH];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
#define DEM_NODEIDITERATOR_NEW()       1


DEM_INLINE Dem_boolean_least Dem_NodeIdIsValid (uint16 checkID)
{
   return ((0 < checkID) && (checkID <= DEM_NODEID_COUNT));
}

/*Iterator for NodeID*/

typedef uint16_least Dem_NodeIdIterator; /* do not change to uint8_least */


DEM_INLINE void Dem_NodeIdIteratorNew(Dem_NodeIdIterator *it)
{
   (*it) = DEM_NODEIDITERATOR_NEW();
}

DEM_INLINE Dem_boolean_least Dem_NodeIdIteratorIsValid(const Dem_NodeIdIterator *it)
{
   return (*it <= DEM_NODEID_COUNT);
}

DEM_INLINE void Dem_NodeIdIteratorNext(Dem_NodeIdIterator *it)
{
   (*it)++;
}

DEM_INLINE Dem_ComponentIdType Dem_NodeIdIteratorCurrent(const Dem_NodeIdIterator *it)
{
   return (Dem_ComponentIdType)(*it);
}

DEM_INLINE Dem_ComponentIdType  Dem_NodeIdFromEventId (Dem_EventIdType id)
{
   return Dem_MapEventIdToNodeId[id];
}



#else


DEM_INLINE Dem_ComponentIdType  Dem_NodeIdFromEventId (Dem_EventIdType id)
{
	DEM_UNUSED_PARAM(id);
	return DEM_NODEID_INVALID;
}

DEM_INLINE Dem_boolean_least Dem_NodeIdIsValid (uint16 checkID)
{
	DEM_UNUSED_PARAM(checkID);
	return FALSE;
}


#endif


/*** DTCID *****************************************************************/


#if (DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_DISABLED)

typedef Dem_EventIdType Dem_MapDtcIdToEventIdType;

#else

typedef struct {
   const Dem_EventIdType *mappingTable;
   uint16 length;
} Dem_MapDtcIdToEventIdType;

#endif
typedef Dem_DTCGroupIdType Dem_MapDtcIdToGroupIdType;
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const Dem_MapDtcIdToEventIdType  Dem_MapDtcIdToEventId[DEM_DTCID_ARRAYLENGTH];
extern const Dem_DtcIdType              Dem_MapEventIdToDtcId[DEM_EVENTID_ARRAYLENGTH];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"



DEM_INLINE Dem_boolean_least Dem_EventIdIsDtcAssigned (Dem_EventIdType id)
{
   return (Dem_MapEventIdToDtcId[id] != DEM_DTCID_INVALID);
}


DEM_INLINE Dem_boolean_least Dem_isDtcIdValid (Dem_DtcIdType id)
{
   return ((0 < id) && (id <= DEM_DTCID_COUNT));
}


DEM_INLINE Dem_DtcIdType  Dem_DtcIdFromEventId (Dem_EventIdType id)
{
   return Dem_MapEventIdToDtcId[id];
}


#if (DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_DISABLED)

DEM_INLINE Dem_EventIdType Dem_DtcIdGetEventId (Dem_DtcIdType dtcid)
{
   return Dem_MapDtcIdToEventId[dtcid];
}

#endif


DEM_INLINE Dem_EventIdType Dem_DtcIdGetFirstEventId (Dem_DtcIdType dtcid)
{
#if (DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_DISABLED)
   return Dem_DtcIdGetEventId(dtcid);
#else
   return Dem_MapDtcIdToEventId[dtcid].mappingTable[0];
#endif
}

DEM_INLINE uint16 Dem_DtcIdGetNumberOfEvents (Dem_DtcIdType dtcid)
{
#if (DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_DISABLED)
	DEM_UNUSED_PARAM(dtcid);
	return 1;
#else
   return Dem_MapDtcIdToEventId[dtcid].length;
#endif

}


/* ITERATOR for DtcID: loop over all existing DtcIds */

typedef uint16_least Dem_DtcIdIterator; /* do not change to uint8_least */

#define DEM_DTCIDITERATOR_NEW()       1
#define DEM_DTCIDITERATOR_INVALID()   (DEM_DTCID_COUNT+1)

DEM_INLINE void Dem_DtcIdIteratorNew(Dem_DtcIdIterator *it)
{
   (*it) = DEM_DTCIDITERATOR_NEW();
}

DEM_INLINE Dem_boolean_least Dem_DtcIdIteratorIsValid(const Dem_DtcIdIterator *it)
{
   return ((0u < *it) && (*it <= DEM_DTCID_COUNT));
}

DEM_INLINE void Dem_DtcIdIteratorNext(Dem_DtcIdIterator *it)
{
   (*it)++;
}

DEM_INLINE Dem_DtcIdType Dem_DtcIdIteratorCurrent(const Dem_DtcIdIterator *it)
{
   return (Dem_DtcIdType)(*it);
}

DEM_INLINE void Dem_DtcIdIteratorInvalidate(Dem_DtcIdIterator *it)
{
   (*it) =0;
}

/*----Iterator for DTCGroup Id--------------------------------*/
#define DEM_DTCGROUPIDITERATOR_NEW()       1

typedef uint8_least Dem_DtcGroupIdIterator;

DEM_INLINE void Dem_DtcGroupIdIteratorNew(Dem_DtcGroupIdIterator *it)
{
   (*it) = DEM_DTCGROUPIDITERATOR_NEW();
}

DEM_INLINE Dem_boolean_least Dem_DtcGroupIdIteratorIsValid(const Dem_DtcGroupIdIterator *it)
{
   return (*it <= DEM_DTCGROUPID_COUNT);
}

DEM_INLINE void Dem_DtcGroupIdIteratorNext(Dem_DtcGroupIdIterator *it)
{
   (*it)++;
}

DEM_INLINE Dem_DTCGroupIdType Dem_DtcGroupIdIteratorCurrent(const Dem_DtcGroupIdIterator *it)
{
   return (Dem_DTCGroupIdType)(*it);
}

DEM_INLINE Dem_boolean_least Dem_DtcGroupIdIsValid (Dem_DTCGroupIdType dtcGroupID)
{
	/*
	 * As id is of type uint8 it is always positive and hence check against less than ZERO not necessary
	 */
   return (dtcGroupID <= DEM_DTCGROUPID_COUNT);
}

/*----------------------------------------*/

/************** Iterator functions for Indicator Attributes **************************/
#if (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
typedef uint16_least Dem_EventIndicatorAttributeIterator;

DEM_INLINE void Dem_EventIndicatorAttributeIteratorNew(Dem_EventIdType EventId, Dem_EventIndicatorAttributeIterator *it)
{
   (*it) = ((EventId - 1) * DEM_INDICATOR_ATTRIBUTE_MAX_PER_EVENT) ;
}

DEM_INLINE Dem_boolean_least Dem_EventIndicatorAttributeIsValid(Dem_EventIdType EventId, const Dem_EventIndicatorAttributeIterator *it)
{
   return (*it < (EventId * DEM_INDICATOR_ATTRIBUTE_MAX_PER_EVENT));
}

DEM_INLINE void Dem_EventIndicatorAttributeNext(Dem_EventIndicatorAttributeIterator *it)
{
   (*it)++;
}

DEM_INLINE uint16_least Dem_EventIndicatorAttributeCurrent(const Dem_EventIndicatorAttributeIterator *it)
{
   return (uint16_least)(*it);
}

/*******************Indicator Id validator function *************************************/
DEM_INLINE Dem_boolean_least Dem_isIndicatorIdValid (uint8 checkID)
{
	return ((checkID  != DEM_INDICATORID_INVALID) && (checkID <= DEM_INDICATORID_COUNT));
}
#endif
/*************************************************************************************/


/*** LIST-ITERATORS ********************************************************/

/* ITERATOR for lists of EventIds: loop over all events assigned to a dtc/ */

typedef struct {
   const Dem_EventIdType* it;
   const Dem_EventIdType* end;
} Dem_EventIdListIterator;


DEM_INLINE void Dem_EventIdListIteratorNewFromDtcId(Dem_EventIdListIterator *it, Dem_DtcIdType dtcid)
{

   if (!(Dem_isDtcIdValid(dtcid)))
   {
 	  DEM_DET(DEM_DET_APIID_EVENTIDLISTITERATOR,0);
   }
#if (DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_DISABLED)
   it->it = &Dem_MapDtcIdToEventId[dtcid];
   it->end = &Dem_MapDtcIdToEventId[dtcid] + 1;
#else
   it->it = &Dem_MapDtcIdToEventId[dtcid].mappingTable[0];
   it->end = &Dem_MapDtcIdToEventId[dtcid].mappingTable[Dem_MapDtcIdToEventId[dtcid].length];
#endif
}

DEM_INLINE Dem_boolean_least Dem_EventIdListIteratorIsValid(const Dem_EventIdListIterator *it)
{
   return ((Dem_boolean_least)(it->it < it->end));
}

DEM_INLINE void Dem_EventIdListIteratorNext(Dem_EventIdListIterator *it)
{
   (it->it)++;
}

DEM_INLINE Dem_EventIdType Dem_EventIdListIteratorCurrent(const Dem_EventIdListIterator *it)
{
   return (Dem_EventIdType)(*(it->it));
}


/*** LIST-ITERATORS ********************************************************/

/* ITERATOR for lists of DtcIds: loop over all Dtcs assigned to a dtcGroup */

typedef struct {
	Dem_DtcIdType it;
	Dem_DtcIdType end;
} Dem_DtcIdListIterator;

typedef struct {
	Dem_DtcIdType dtcStartIndex;
	Dem_DtcIdType dtcEndIndex;
} Dem_DtcGroupIdMapToDtcIdType;
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const Dem_DtcGroupIdMapToDtcIdType Dem_DtcGroupIdMapToDtcId[DEM_DTCGROUPID_ARRAYLENGTH];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


DEM_INLINE void Dem_DtcIdListIteratorNewFromDtcGroup(Dem_DtcIdListIterator *it, Dem_DTCGroupIdType dtcGroup)
{
	if (!(Dem_DtcGroupIdIsValid(dtcGroup)))
	{
		DEM_DET(DEM_DET_APIID_DTCGROUPIDIDLISTITERATOR,0);
	}

	it->it = Dem_DtcGroupIdMapToDtcId[dtcGroup].dtcStartIndex;
	it->end = Dem_DtcGroupIdMapToDtcId[dtcGroup].dtcEndIndex;
}

DEM_INLINE Dem_boolean_least Dem_DtcIdListIteratorIsValid(const Dem_DtcIdListIterator *it)
{
   return (it->it <= it->end);
}

DEM_INLINE void Dem_DtcIdListIteratorNext(Dem_DtcIdListIterator *it)
{
   (it->it)++;
}

DEM_INLINE Dem_DtcIdType Dem_DtcIdListIteratorCurrent(const Dem_DtcIdListIterator *it)
{
   return (it->it);
}

/****************************DEMJ1939NODE************************************************/
#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)

typedef struct {
    const Dem_DtcIdType* it;
    const Dem_DtcIdType* end;
} Dem_DtcIdListIterator2;

typedef struct {
   const Dem_DtcIdType *mappingTable;
   uint16 length;
} Dem_J1939NodeIDMapToDtcIdType;

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const Dem_J1939NodeIDMapToDtcIdType Dem_J1939NodeIDMapToDtcId[DEM_J1939NODEID_ARRAYLENGTH];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

DEM_INLINE Dem_boolean_least Dem_J1939DcmIsNodeIdValid (Dem_J1939NodeIdType nodeId)
{
   return (nodeId < DEM_J1939NODEID_ARRAYLENGTH);
}

#define DEM_J1939NODEIDITERATOR_NEW()       0

typedef uint8_least Dem_J1939NodeIdIterator;

DEM_INLINE void Dem_J1939NodeIdIteratorNew(Dem_J1939NodeIdIterator *it)
{
   (*it) = DEM_J1939NODEIDITERATOR_NEW();
}

DEM_INLINE Dem_boolean_least Dem_J1939NodeIdIteratorIsValid(const Dem_J1939NodeIdIterator *it)
{
   return (*it < DEM_J1939NODEID_ARRAYLENGTH);
}

DEM_INLINE void Dem_J1939NodeIdIteratorNext(Dem_J1939NodeIdIterator *it)
{
   (*it)++;
}

DEM_INLINE Dem_J1939NodeIdType Dem_J1939NodeIdIteratorCurrent(const Dem_J1939NodeIdIterator *it)
{
   return (Dem_J1939NodeIdType)(*it);
}

DEM_INLINE void Dem_J1939DtcIdListIteratorNewFromJ1939NodeID(Dem_DtcIdListIterator2 *it, Dem_J1939NodeIdType nodeId)
{
    if (!(Dem_J1939DcmIsNodeIdValid(nodeId)))
    {
        DEM_DET(DEM_DET_APIID_J1939DCMNODEIDLISTITERATOR,0);
    }

    it->it = &Dem_J1939NodeIDMapToDtcId[nodeId].mappingTable[0];
    it->end = &Dem_J1939NodeIDMapToDtcId[nodeId].mappingTable[Dem_J1939NodeIDMapToDtcId[nodeId].length];
}

DEM_INLINE Dem_boolean_least Dem_J1939DtcIdListIteratorIsValid(const Dem_DtcIdListIterator2 *it)
{
   return (it->it < it->end);
}

DEM_INLINE void Dem_J1939DtcIdListIteratorNext(Dem_DtcIdListIterator2 *it)
{
   (it->it)++;
}

DEM_INLINE Dem_DtcIdType Dem_J1939DtcIdListIteratorCurrent(const Dem_DtcIdListIterator2 *it)
{
   return (Dem_DtcIdType)(*(it->it));
}
#endif

/*** LIST-ITERATOR ********************************************************/

#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

/* ITERATOR for lists of EventIds: loop over all events assigned to a nodeid */

typedef struct {
   Dem_EventIdType it;
   Dem_EventIdType end;
} Dem_EventIdListIterator2;


DEM_INLINE void Dem_EventIdListIterator2NewFromNodeId(Dem_EventIdListIterator2 *it, Dem_ComponentIdType nodeid)
{
   if (!(Dem_NodeIdIsValid(nodeid)))
   {
 	  DEM_DET(DEM_DET_APIID_EVENTIDLISTITERATOR,1);
   }
   it->it = Dem_MapNodeIdToEventId[nodeid-1] + 1;
   it->end = Dem_MapNodeIdToEventId[nodeid];
}

DEM_INLINE Dem_boolean_least Dem_EventIdListIterator2IsValid(const Dem_EventIdListIterator2 *it)
{
   return (it->it <= it->end);
}

DEM_INLINE void Dem_EventIdListIterator2Next(Dem_EventIdListIterator2 *it)
{
   (it->it)++;
}

DEM_INLINE Dem_EventIdType Dem_EventIdListIterator2Current(const Dem_EventIdListIterator2 *it)
{
   return (it->it);
}


/*** LIST-ITERATORS ********************************************************/

/* ITERATOR for lists of nodeIds: loop over all childnodes of a node */

typedef struct {
	const Dem_ComponentIdType* it;
	const Dem_ComponentIdType* end;
} Dem_NodeIdListIterator;


DEM_INLINE void Dem_NodeIdListIteratorNewFromNodeId(Dem_NodeIdListIterator *it, Dem_ComponentIdType nodeid)
{
	if (!(Dem_NodeIdIsValid(nodeid)))
	{
		DEM_DET(DEM_DET_APIID_EVENTIDLISTITERATOR,2);
	}
	it->it = &Dem_MapNodeIdToChildNodeId[Dem_NodeToChildNodeIndex[nodeid-1]];
	it->end = &Dem_MapNodeIdToChildNodeId[Dem_NodeToChildNodeIndex[nodeid]];
}

DEM_INLINE Dem_boolean_least Dem_NodeIdListIteratorIsValid(const Dem_NodeIdListIterator *it)
{
	return (Dem_boolean_least)(it->it < it->end);
}

DEM_INLINE void Dem_NodeIdListIteratorNext(Dem_NodeIdListIterator *it)
{
	(it->it)++;
}

DEM_INLINE Dem_ComponentIdType Dem_NodeIdListIteratorCurrent(const Dem_NodeIdListIterator *it)
{
	return (Dem_ComponentIdType)(*(it->it));
}

#endif
#endif
