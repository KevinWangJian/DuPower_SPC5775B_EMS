


#ifndef DEM_PRV_INTERNALAPI_H
#define DEM_PRV_INTERNALAPI_H

#include "Dem_DTCs.h"
#include "Dem_Bfm.h"
#include "Dem_EnvMain.h"

/***********************************************************************/
/************ Event related Internal Functions *************************/
/***********************************************************************/

/* Internal function for getting the event priority from Event Id */
DEM_INLINE uint8 Dem_InternalGetEventPriority (Dem_EventIdType EventId)
{
     return Dem_EvtGetEventPriority(EventId);
}

/* Internal function for checking if the event is suppressed */
DEM_INLINE Dem_boolean_least Dem_InternalEvtIsSuppressed (Dem_EventIdType EventId)
{
    return Dem_EvtIsSuppressed(EventId);
}

/* Internal function for checking if Event is requesting Warning Indicator*/
DEM_INLINE Dem_boolean_least Dem_InternalEvtRequestsWarningIndicator (Dem_EventIdType EventId)
{
    return Dem_EvtRequestsWarningIndicator(EventId);
}

/***********************************************************************/
/************ Event Memory related Internal Functions ******************/
/***********************************************************************/

/* Internal function for getting Occurence Counter from an event memory Pointer */
DEM_INLINE uint16_least Dem_InternalGetEventMemOccurrenceCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return Dem_EvMemGetEventMemOccurrenceCounterByPtr(EventMemory);
}

/* Internal function for getting Occurence Counter from an event memory Index */
DEM_INLINE uint16_least Dem_InternalGetEventMemOccurrenceCounter(uint16_least LocId)
{
    return Dem_InternalGetEventMemOccurrenceCounterByPtr(&Dem_EvMemEventMemory[LocId]);
}


/* Internal function for getting Event Id from an event memory Index */
DEM_INLINE Dem_EventIdType Dem_InternalGetEventMemEventId (uint16_least LocId)
{
    return Dem_EvMemGetEventMemEventId(LocId);
}

/* Internal function for getting Time Id from an event memory Index */
DEM_INLINE uint32 Dem_InternalGetEventMemTimeId (uint16_least LocId)
{
     return Dem_EvMemGetEventMemTimeId(LocId);
}

/* Internal function for getting Aging Counter from an event memory pointer */
DEM_INLINE uint16_least Dem_InternalGetEventMemAgingCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return Dem_EvMemGetEventMemAgingCounterByPtr(EventMemory);
}

/* Internal function for getting Aging Counter from an event memory Index */
DEM_INLINE uint16_least Dem_InternalGetEventMemAgingCounter(uint16_least LocId)
{
    return Dem_InternalGetEventMemAgingCounterByPtr(&Dem_EvMemEventMemory[LocId]);
}

/* Internal function to check if the Event memory location Id is valid */
DEM_INLINE Dem_boolean_least Dem_InternalIsEvMemLocIdValid(uint16_least LocId)
{
    return Dem_EvMemIsEventMemLocIdValid(LocId);
}

/* Internal function to clear the Event memory location on Displacement.
 * Provided for using only in Customer specific displacement / storage strategy */
DEM_INLINE void Dem_InternalForceClrEvMemLocOnDisplacement(uint16_least LocId)
{
    Dem_EvMemForceClearEventMemoryLocation(LocId, DEM_EVMEM_WRITEMASK_CLEAR, DEM_EVMEM_ACTIONTYPE_DISPLACEMENT);
}

/***********************************************************************/
/************ DTC related Internal Functions ***************************/
/***********************************************************************/

/* Internal function for getting the Dtc code from Dtc Id */
DEM_INLINE Dem_DtcCodeType Dem_InternalGetDtcCode (Dem_DtcIdType dtcId)
{
    return Dem_DtcGetCode(dtcId);
}

/* Internal function for checking if a Dtc Id is valid */
DEM_INLINE Dem_boolean_least Dem_InternalDtcIdIsValid (Dem_DtcIdType dtcId)
{
    return Dem_isDtcIdValid (dtcId);
}

/* Internal function for getting Dtc id for an event id */
DEM_INLINE Dem_DtcIdType  Dem_InternalDtcIdFromEventId (Dem_EventIdType eventId)
{
    return Dem_DtcIdFromEventId (eventId);
}

/***********************************************************************/
/************ BFM related Internal Functions ***************************/
/***********************************************************************/

/* Internal function to get direct read access to a BFM record.
 * Caution: only use this function within the BFM task context, eg inside a callback function.
 * The function is not interrupt protected!!!
 * The interface needs to be enabled through configuration switch: DemRbEnableBfmDirectAccessInterface */
#if( (DEM_BFM_ENABLED == DEM_BFM_ON) && (RBA_DEMBFM_ENABLE_DIRECT_ACCESS_INTERFACE == DEM_BFM_ON) )
DEM_INLINE rba_DemBfm_ReturnType Dem_InternalBfmRecordGetDirectReadAccess( rba_DemBfm_LocationDataType location,
        rba_DemBfm_Record const **bfmRecord, boolean *isMarkedForDeletion, boolean *isEmpty, boolean *isModified,
        boolean *isLockedPerm, boolean *isLockedTemp )
{
   return rba_DemBfm_RecordGetDirectReadAccess(location, bfmRecord, isMarkedForDeletion, isEmpty,
            isModified, isLockedPerm, isLockedTemp );
}
#endif

/***********************************************************************/
/************ ENV related Internal Functions ***************************/
/***********************************************************************/

/* Internal function to store freeze frame
 *  Caution: only use this function within the DEM task context, eg inside a callback function.*/
DEM_INLINE void Dem_InternalEnvCopyRawFF(Dem_EventIdType EventId,
        uint8* dest,
        uint16 destSize,
        uint8 ffIndex,
        const uint8* src)
{
    Dem_EnvCopyRawFF(EventId, dest, destSize, ffIndex, src);
}

/***********************************************************************/
/************************ Internal macro checks ************************/
/***********************************************************************/

#ifndef DEM_DTCID_ARRAYLENGTH
#error "DEM_DTCID_ARRAYLENGTH is not available in the project, please check if it is modified or deleted "
#else
#define DEM_INTERNAL_DTCID_ARRAYLENGTH  DEM_DTCID_ARRAYLENGTH
#endif


#endif /* DEM_PRV_INTERNALAPI_H */

