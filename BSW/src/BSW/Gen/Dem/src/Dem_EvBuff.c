

#include "Dem.h"
#include "Rte_Dem.h"

#include "Dem_EvBuff.h"

#include "Dem_Bfm.h"
#include "Dem_Cfg_EvBuff.h"
#include "Dem_Helpers.h"
#include "Dem_EnvMain.h"
#include "Dem_EventFHandling.h"
#include "Dem_EventStatus.h"
#include "Dem_EventRecheck.h"
#include "Dem_Obd.h"
/* FC_VariationPoint_START */
#include "Dem_Lock.h"

#if (DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
#include "Dem_PrjSpecificFailureMemory.h"
#endif

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"
Dem_EvtBufferState Dem_EvtBuffer;
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"


#if (DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DEFINE_CONST(Dem_NvmBlockIdType, Dem_PreStoredFFNvmId, DEM_CFG_PRESTORED_FF_SIZE, DEM_CFG_PRESTORED_FREEZEFRAME_NVMIDS);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
#endif



#define DEM_LOCATIONPRIO_NOOVERWRITE     (0u)
#define DEM_LOCATIONPRIO_TYPESHIFT       (12u)
#define DEM_LOCATIONPRIO_EMPTY           (0xFFFFFFu)
#define DEM_LOCATIONPRIO_SAME_EVENTID    (0xFFFFFFu+1u)


#if DEM_CFG_PRESTORED_FF_SIZE > DEM_CFG_EVBUFF_SIZE
#error DEM_CFG_PRESTORED_FF_SIZE must be smaller than DEM_CFG_EVBUFF_SIZE
#endif



/**
 * @param[in]  EventId          Identification of Event by ID.
 *             eventType         Type of the Event id.
 * Dem: Local function to get the priority of an event
 *
 */
DEM_INLINE uint32 Dem_EvBuffGetEventPriority (Dem_EventIdType EventId, Dem_EvBuffEventType eventType)
{
    return ((uint32)eventType << DEM_LOCATIONPRIO_TYPESHIFT) +  (uint32)EventId;
}




/**
 * @param[in]  Dem_EvtParamtype          structure containing paramters related to an event.
 * Dem: Local function to get the priority of location. I.e finding place in the buffer
 *
 */
DEM_INLINE uint32 Dem_EvBuffGetLocationPriority (const Dem_EvBuffEvent *bufferElement)
{
    /* bufferElement->counter not checked, as the same event shall not use another location
     * reason: if 2 events exist in the evbuffer for same eventId, it is not defined which one will first be retrieved to event-memory
     */

    if (bufferElement->eventId == DEM_EVENTID_INVALID)
    {
        return DEM_LOCATIONPRIO_EMPTY;
    }

    if (bufferElement->eventType == C_EVENTTYPE_SET)
    {
        /* do not overwrite set-event, because currently handling for overwritten event is not implemented */
        return DEM_LOCATIONPRIO_NOOVERWRITE;
    }

    return Dem_EvBuffGetEventPriority (bufferElement->eventId, bufferElement->eventType);
}

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/**
 * Search an empty location within buffer.
 * @warning  The function does not lock interrupts. To get an empty location
 *           and fill the location lock interrupts!
 * @return  Returns the location which was selected as write location
 *          If buffer is full, and no overwrite location was found, the return value is DEM_EVENTBUFFER_SIZE.
 *
 *  Note: If no empty location is found but multiple prestored events are
 *  available, the returned location will always be the first found prestore
 *  location.
 */
static uint8_least Dem_EvBuffGetLocationToWrite (Dem_EventIdType EventIdOfNewEvent, Dem_EvBuffEventType *typeOfNewEvent)
{
    uint8_least i = DEM_CFG_EVBUFF_SIZE;
    uint8_least checkLoc;
    uint32_least prioOfNewEvent = Dem_EvBuffGetEventPriority (EventIdOfNewEvent, *typeOfNewEvent);

    uint8_least writeLoc = DEM_CFG_EVBUFF_SIZE;
    uint32_least writeLocPrio = prioOfNewEvent;
    uint32_least tempPrio;

    while (i > 0u)
    {
        i--;

        if (*typeOfNewEvent != C_EVENTTYPE_PRESTORE)
        {
            /* Start filling the buffer from last in Normal case */
            checkLoc = i;
        }
        else
        {
#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

            /* Start filling the buffer from first in case of Pre-stored freeze frame */
            checkLoc = (DEM_CFG_EVBUFF_SIZE - 1u) - i;
            /* only locations 0 .. (prestored_ff_size-1) may be used for storing PRESTORE events */
            if (checkLoc >= DEM_CFG_PRESTORED_FF_SIZE)
            {
                break;
            }
#else
            break;
#endif
        }

        if (Dem_EvtBuffer.Locations[checkLoc].eventId == EventIdOfNewEvent)
        {
            /* allow overwriting, if type of new event has same or higher prio */
            if (Dem_EvtBuffer.Locations[checkLoc].eventType >= *typeOfNewEvent)
            {
                return checkLoc;  /* monitoring overwrite old event of itself */
            }

            if (   (Dem_EvtBuffer.Locations[checkLoc].eventType == C_EVENTTYPE_SET)
                    && (*typeOfNewEvent                     == C_EVENTTYPE_RESET))
            {
                *typeOfNewEvent = C_EVENTTYPE_SET_RESET;    /* combine events set/reset */
                return checkLoc;
            }

            /* monitoring already in SFB and not allowed to be overwritten with new event of itself */
            return DEM_CFG_EVBUFF_SIZE;
        }

        tempPrio = Dem_EvBuffGetLocationPriority (&Dem_EvtBuffer.Locations[checkLoc]);
        if (tempPrio > writeLocPrio)
        {
            writeLoc = checkLoc;
            writeLocPrio = tempPrio;
        }
    }

    /* no store-location found for new event */
    if (writeLoc == DEM_CFG_EVBUFF_SIZE)
    {
        Dem_EvtBuffer.OverflowCounter++;
        if (*typeOfNewEvent == C_EVENTTYPE_SET)
        {
            Dem_EvtBuffer.OverflowCounterSet++;
        }
    }

    return writeLoc;
}


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/**
 * @param[in]  locationIndex          Index for storeage of prestore freezeframe
 *             newEventId             EventId for which Prestore Freeze frame storage availability is to be checked
 * Dem: Local function to check if location is available for storage of prestore freezeframe
 *
 */

DEM_INLINE Dem_boolean_least Dem_EvBuffIsPrestoreLocationAvailable (uint32 locationIndex, Dem_EventIdType newEventId)
{

#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

    return (   (Dem_EvtBuffer.Locations[locationIndex].eventId == newEventId)
            && (Dem_EvtBuffer.Locations[locationIndex].eventType == C_EVENTTYPE_PRESTORE));

#else

    DEM_UNUSED_PARAM(locationIndex);
    DEM_UNUSED_PARAM(newEventId);
    return FALSE;

#endif
}


/*
 * handle elapsed counters: if counter elapsed, report failure to StateStorage
 * for storage to next IC; also check if failure storage is disabled for this failure
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
static void Dem_EvBuffHandleElapsedCounter(const Dem_EvBuffEvent *bufferElement)
{

#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

    if (   (bufferElement->eventType != C_EVENTTYPE_UNROBUST)
        && (bufferElement->eventType != C_EVENTTYPE_PRESTORE)
        )
    {
        Dem_EvtSetIsRecheckedAndWaitingForMonResult(bufferElement->eventId, FALSE);
    }

#endif

#if (DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE == DEM_CFG_DEPDEGRADATIONREASONRECOVERABLE_ON)

    if (   (bufferElement->eventType == C_EVENTTYPE_SET)
        || (bufferElement->eventType == C_EVENTTYPE_SET_RECONFIRMED)
        || (bufferElement->eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
        )
    {
        if (!Dem_EvtIsRecoverable((Dem_EventIdType)bufferElement->eventId))
        {
            Graph__setHasNonRecoverableFailure (Dem_FailureEvent__getNodeId (&(bufferElement->fEvent)));
        }
    }

#endif

    DEM_UNUSED_PARAM(bufferElement);
}


void Dem_EvBuffMainFunction(void)
{
    /*** COMPLEX ***/
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

    uint32_least i = DEM_CFG_EVBUFF_SIZE;

    DEM_ENTERLOCK_MON();

    /* D_238: decrease counters of all entries */
    while (i > 0u)
    {
        i--;

        /* if sfb-location contains failure event (valid EventId) */
        if (Dem_EvtBuffer.Locations[i].eventId != DEM_EVENTID_INVALID)
        {
            /* if countdown not elapsed */
            if (Dem_EvtBuffer.Locations[i].counter > 0)
            {
                Dem_EvtBuffer.Locations[i].counter--;

                if (Dem_EvtBuffer.Locations[i].counter == 0)
                {
                    Dem_EvBuffHandleElapsedCounter (&Dem_EvtBuffer.Locations[i]);
                }
            }
        }
    }

    DEM_EXITLOCK_MON();

#endif
}




void Dem_EvBuffClear(Dem_EventIdType EventId)
{
    uint32_least i = DEM_CFG_EVBUFF_SIZE;

    DEM_ENTERLOCK_MON(); /* DSM_D_212 */

    /* D_238: decrease counters of all entries */
    while (i > 0u)
    {
        i--;
        if (Dem_EvtBuffer.Locations[i].eventId == EventId)
        {
            Dem_EvtSetIsRecheckedAndWaitingForMonResult(EventId, FALSE);
            Dem_EvtBuffer.Locations[i].eventId = DEM_EVENTID_INVALID;
            break;
        }
    }

    DEM_EXITLOCK_MON(); /* DSM_D_212 */
}


const Dem_EvBuffEvent* Dem_EvBuffGetEvent (uint32* locationIndex)
{
    Dem_EvBuffEvent* fEvent = NULL_PTR;
    uint16_least i = DEM_CFG_EVBUFF_SIZE;

    /* D_238: decrease counters of all entries */
    while (i > 0u)
    {
        i--;

        /* if sfb-location contains failure event (valid EventId) */
        if (Dem_EvtBuffer.Locations[i].eventId != DEM_EVENTID_INVALID)
        {
            if (   (Dem_EvBuffGetCounter(&(Dem_EvtBuffer.Locations[i])) == 0)
#if  (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
                    && (Dem_EvtBuffer.Locations[i].eventType != C_EVENTTYPE_PRESTORE)
#endif
            )
            {
                *locationIndex = i;
                fEvent = &(Dem_EvtBuffer.Locations[i]);
                break;
            }
        }
    }
    return fEvent;
}


/**
 * DSM_D_229: Clear all sequential failures within buffer and return the
 *            minimum filter value.
 * @param[in]  EventId           The EventId of the new failure event.
 * @param[in]  nodeID        The SID of the new failure events node.
 * @param[in]  counterInit   The initial value for the SFB filter time of
 *                           the new failure event.
 */

#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
uint8_least Dem_EvBuffClearSequentialFailures (Dem_EventIdType EventId, Dem_ComponentIdType nodeID, uint8 counterInit)
{
    uint8_least i = DEM_CFG_EVBUFF_SIZE;
    uint8_least minCounter = counterInit;

    DEM_ENTERLOCK_MON();       /* DSM_D_212 */

    while (i > 0u)
    {
        i--;

        if (   (Dem_EvtBuffer.Locations[i].eventId != DEM_EVENTID_INVALID)
                && (   (Dem_EvtBuffer.Locations[i].eventType == C_EVENTTYPE_SET)
                        || (Dem_EvtBuffer.Locations[i].eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
                )
                && (Dem_EvtBuffer.Locations[i].counter > 0)
        )
        {
            if (   (Dem_NodeAreAncestorsFailed(Dem_FailureEvent__getNodeId(&Dem_EvtBuffer.Locations[i])))
                    || (   (Dem_FailureEvent__getNodeId(&Dem_EvtBuffer.Locations[i]) == nodeID)
                            && (Dem_EvtBuffer.Locations[i].eventId > EventId)
                            && (!Dem_NodeIgnorePriority(nodeID))
                    )
            )
            {
                /* DSM_D_229: mark previous failure as sequential and clear location*/
                Dem_EvtSetCausal (Dem_EvtBuffer.Locations[i].eventId, FALSE);
                Dem_EvtSetIsRecheckedAndWaitingForMonResult(Dem_EvtBuffer.Locations[i].eventId, FALSE);

                /* DSM_D_248, DSM_D_162: set counter to minimum */
                DEM_A_MIN_AB (minCounter, Dem_EvtBuffer.Locations[i].counter);

                Dem_EvtBuffer.Locations[i].eventId = DEM_EVENTID_INVALID;
            }
        }
    }

    DEM_EXITLOCK_MON();     /* DSM_D_212 */

    return minCounter;
}
#endif


void Dem_EvBuffEnvCaptureData(
    Dem_EventIdType EventId,
    uint8 *EnvData
    DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0,Dem_DebugDataType debug1))
{

    Dem_EnvCaptureED(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(debug0,debug1));
    Dem_EnvCaptureFF(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA DEM_DEBUGDATA_PARAM(debug0,debug1));
    /* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
    rba_DemObdBasic_FF_CaptureFF(EventId, EnvData, DEM_CFG_ENVMINSIZE_OF_RAWENVDATA);
#endif
    /* FC_VariationPoint_END */
}
/**
 * returns: whether the failure event could be inserted into SFB buffer
 */
Dem_boolean_least Dem_EvBuffInsert (Dem_EvBuffEventType eventType,
        Dem_EventIdType eventId
        DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0,Dem_DebugDataType debug1))
{
#if (DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)
    Dem_EvBuffEnvDataAlignedType EnvData;
#endif

    /* FC_VariationPoint_START */
#if( DEM_BFM_ENABLED == DEM_BFM_ON )
    rba_DemBfm_EnvironmentalData BfmBufferData;
#endif
    /* FC_VariationPoint_END */
#if (DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
    DemRbProjectSpecificFailureMemoryType PrjSpecificFailureMemoryData;
#endif

    Dem_boolean_least eventInserted = FALSE;
    uint8_least counter = 0;
    Dem_boolean_least skipCausalCheck_flag = FALSE;
    uint8_least storeLoc;

    DEM_ASSERT_ISNOTLOCKED();

    /*****  calculate counter for new location  *****/
    if (   (eventType == C_EVENTTYPE_SET)
            || (eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
    )
    {
        counter = Dem_EvBuffClearSequentialFailures (eventId, Dem_NodeIdFromEventId(eventId),
                Dem_EvtGetBufferTime(eventId));
    }

    if (eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
    {
        counter = DEM_CFG_EVBUFF_DELAY_SET_WAITINGFORMONITORING;
    }

    if (eventType == C_EVENTTYPE_SET_RECONFIRMED)
    {
            eventType = C_EVENTTYPE_SET;
            counter = 0;
            skipCausalCheck_flag = TRUE;
    }

#if (DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)
    Dem_EvBuffEnvCaptureData(eventId, EnvData.Buffer  DEM_DEBUGDATA_PARAM(debug0, debug1));
#endif
    /* FC_VariationPoint_START */
#if( DEM_BFM_ENABLED == DEM_BFM_ON )
    rba_DemBfm_EnvCaptureBFM( eventId, &BfmBufferData  DEM_DEBUGDATA_PARAM(debug0,debug1) );
#endif
    /* FC_VariationPoint_END */
#if (DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
	/* Remap eventType before passing to Dem_ProjectSpecificFailureMemoryCapture() */
    Dem_ProjectSpecificFailureMemoryCapture(eventId, eventType, &PrjSpecificFailureMemoryData);
	/* Revert the remap */

#endif

    DEM_ENTERLOCK_MON();

        /*****  check if failure still is causal  *****/
        if ((!skipCausalCheck_flag) &&  ((eventType == C_EVENTTYPE_SET)
                || (eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
                || (eventType == C_EVENTTYPE_UNROBUST))
            )
        {
                /* HINT: causality of failure has to be confirmed again, due to */
                /*       concurrency and task interruption                      */
                if (!Dem_Dependencies_CheckEventIsCausal(eventId, Dem_NodeIdFromEventId(eventId)) )
                {
                    /* Event not inserted, because failure no longer is causal */
                    /* EventId__setFailureCausal (EventId_n, FALSE);   done by function caller  */

                    DEM_EXITLOCK_MON();
                    return FALSE;
                }
        }





    /*************************************************/
    /*****  find storage location in SFB-buffer  *****/
    /*************************************************/

    storeLoc = Dem_EvBuffGetLocationToWrite(eventId, &eventType);

    if (storeLoc != DEM_CFG_EVBUFF_SIZE)
    {
        if (        (Dem_EvtBuffer.Locations[storeLoc].eventId != DEM_EVENTID_INVALID)
                && (Dem_EvtBuffer.Locations[storeLoc].eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
            )
        {
            if (Dem_EvtBuffer.Locations[storeLoc].eventId != eventId)
            {
                Dem_EvtBuffer.OverflowCounter++;
                Dem_EvtSetIsRecheckedAndWaitingForMonResult(Dem_EvtBuffer.Locations[storeLoc].eventId, FALSE);
                Dem_EvtSetCausal (Dem_EvtBuffer.Locations[storeLoc].eventId, FALSE);
                if (eventType == C_EVENTTYPE_RESET)
                {
                    Dem_EvtSetPassedWasReported (eventId, TRUE);
                }
            }

            /* if failureevent was caused by recheck logic, delete set and reset event */
            if (    (eventId == Dem_EvtBuffer.Locations[storeLoc].eventId)
                 && (eventType == C_EVENTTYPE_RESET)
                 && (!Dem_EvtIsNextReportRelevantForMemories(eventId))
               )
            {
                Dem_EvtBuffer.Locations[storeLoc].eventId = DEM_EVENTID_INVALID;

                DEM_EXITLOCK_MON();
                return FALSE;
            }
        }

        /* if not writing on a prestored event location
         AND not combining a SET and RESET event     */
        if (   !( Dem_EvBuffIsPrestoreLocationAvailable(storeLoc, eventId)
                  && (   (eventType == C_EVENTTYPE_SET)
                      || (eventType == C_EVENTTYPE_SET_WAITINGFORMONITORING)
                     )
                 )
             && (eventType != C_EVENTTYPE_SET_RESET)
           )
        {
            /* insert complete event data (environmentdata, debugdata to SFB */
            Dem_EvtBuffer.Locations[storeLoc].eventId = eventId;

#if(DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
            Dem_EvtBuffer.Locations[storeLoc].debug0 = debug0;
            Dem_EvtBuffer.Locations[storeLoc].debug1 = debug1;
#endif
#if (DEM_CFG_EVBUFF_STORES_ENVDATA == DEM_CFG_EVBUFF_STORES_ENVDATA_ON)
            DEM_MEMCPY(Dem_EvtBuffer.Locations[storeLoc].envData.Buffer, EnvData.Buffer, DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[storeLoc].envData));
#endif

#if(DEM_CFG_SUPPORT_PROJECTSPECIFIC_FAILUREMEMORY == TRUE)
            DEM_MEMCPY(&Dem_EvtBuffer.Locations[storeLoc].DemRbProjectSpecificFailureMemoryData, &PrjSpecificFailureMemoryData, DEM_SIZEOF_TYPE(DemRbProjectSpecificFailureMemoryType));
#endif

#if(DEM_BFM_ENABLED == DEM_BFM_ON)
            DEM_MEMCPY(&Dem_EvtBuffer.Locations[storeLoc].DemRbBoschFailureMemoryData, &BfmBufferData, DEM_SIZEOF_TYPE(rba_DemBfm_EnvironmentalData));
#endif

        }

        Dem_EvtBuffer.Locations[storeLoc].eventType = eventType;
        Dem_EvBuffSetCounter(&(Dem_EvtBuffer.Locations[storeLoc]), (uint8)counter);

        eventInserted = TRUE;


        /* perform checks if counter elapsed */
        if (counter == 0u)
        {
            Dem_EvBuffHandleElapsedCounter (&Dem_EvtBuffer.Locations[storeLoc]);
        }
    }


    DEM_EXITLOCK_MON();
    return eventInserted;
}


void Dem_EvBuffRemoveEvent (uint32 locationIndex)
{
    DEM_ASSERT_ISLOCKED();
    if (locationIndex < DEM_CFG_EVBUFF_SIZE)
    {
        Dem_EvtBuffer.Locations[locationIndex].eventId = DEM_EVENTID_INVALID;
    }
}


#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

/**
 * The prestored FreezeFrame of the specified eventId will be deleted.
 *
 * @param EventId The eventID which is to use to look for a prestored FreezeFrame.
 */
static void Dem_EvBuffRemovePrestored (Dem_EventIdType EventId)
{
    uint8_least i;

    DEM_ENTERLOCK_MON();

    for (i=0; i < DEM_CFG_PRESTORED_FF_SIZE; i++)
    {
        /* if SET-Event (or even RESET-event) is still in buffer, delete it */
        if (    (   (Dem_EvtBuffer.Locations[i].eventId == EventId)
                || (EventId == DEM_EVENTID_INVALID))
                && (Dem_EvtBuffer.Locations[i].eventType == C_EVENTTYPE_PRESTORE)
        )
        {
            Dem_EvtBuffer.Locations[i].eventId = DEM_EVENTID_INVALID;
        }
    }

    DEM_EXITLOCK_MON();
}


/**
 * All prestored FreezeFrames will be deleted.
 */
void Dem_EvBuffRemoveAllPrestored (void)
{
    Dem_EvBuffRemovePrestored (DEM_EVENTID_INVALID);
}

#endif


/* FC_VariationPoint_START */


/* FC_VariationPoint_END */
/**
 *  This function can be called by DSW or PSW in order to check whether for
 *  a given monitoring identifier, a failure event is still pending to be
 *  reported to FMHC. \n
 *  Background: It is possible that a component has called DIA to qualify a fault,
 *  but the transfer from DIA to FMHC (via SFB) is still pending. In such case,
 *  it is insufficient to check Fmhc_IsUpdatingEeprom(), because the EEPROM
 *  update of FMHC hasn't even started.
 *
 * @param EventId : Corresponds to the monitoring for which report pending is checked. \n
 *        If DEM_EVENTID_INVALID is passed, then the SFB will be checked for any
 *        pending failure event.
 *
 * @return FALSE = No event report is pending . \n
 *         TRUE = An event report is pending .
 */

Dem_boolean_least Dem_EvBuffIsEventPending (Dem_EventIdType EventId)
{
    Dem_boolean_least EventFound = FALSE;   /* Return value of this function (FALSE by default) */
    uint8_least i = DEM_CFG_EVBUFF_SIZE;    /* Loop index (start from the buffer end because it's filled from there) */

    DEM_ENTERLOCK_MON();

    /* Loop over sequential failure buffer (SFB) */
    while(i > 0u)
    {
        i--;

        /* Current location contains a failure event for (the given EventId) or (any EventId)? */
        if (   ((Dem_EvtBuffer.Locations[i].eventId == EventId) || (DEM_EVENTID_INVALID == EventId))

#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
                && (Dem_EvtBuffer.Locations[i].eventType != C_EVENTTYPE_PRESTORE)
#endif
        )
        {
            EventFound = TRUE;
            i = 0u;
        }
    }

    DEM_EXITLOCK_MON();

    return EventFound;
}


Std_ReturnType Dem_PrestoreFreezeFrameWithEnvData( Dem_EventIdType EventId ,Dem_DebugDataType debug0 ,Dem_DebugDataType debug1 )
{
    Std_ReturnType ReturnValue = E_NOT_OK;

#if (DEM_CFG_DEBUGDATA == DEM_CFG_DEBUGDATA_OFF)
    DEM_UNUSED_PARAM(debug0);
    DEM_UNUSED_PARAM(debug1);
#endif

#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

    DEM_ENTRY_CONDITION_CHECK_INIT_EVTIDVALID_EVTAVAILABLE(EventId,DEM_DET_APIID_PRESTOREFREEZEFRAME,E_NOT_OK);

    if (Dem_EvBuffInsert(C_EVENTTYPE_PRESTORE, EventId DEM_DEBUGDATA_PARAM(debug0, debug1)))
    {
        ReturnValue = E_OK;
    }

#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(debug0);
    DEM_UNUSED_PARAM(debug1);
#endif

    return ReturnValue;
}


Std_ReturnType Dem_PrestoreFreezeFrame(Dem_EventIdType EventId)
{
    return Dem_PrestoreFreezeFrameWithEnvData(EventId,0,0);
}


Std_ReturnType Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId)
{

#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
    DEM_ENTRY_CONDITION_CHECK_INIT_EVTIDVALID_EVTAVAILABLE(EventId,DEM_DET_APIID_DEM_CLEARPRESTOREDFREEZEFRAME,E_NOT_OK);

    Dem_EvBuffRemovePrestored(EventId);
    return E_OK;

#else
    DEM_UNUSED_PARAM(EventId);
    return E_NOT_OK;
#endif

}


#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)

/* called from Dem_Init to validate the Nv block */
void Dem_PreStoredFFInitCheckNvM(void)
{
#if (DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
    uint8 i;
    Dem_NvmResultType NvmResult;

    for (i = 0; i < DEM_CFG_PRESTORED_FF_SIZE; i++)
    {
        if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
        {
            /* Zero the content of this particular location */
            DEM_MEMSET(&Dem_EvtBuffer.Locations[i], 0, DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[i]));
            Dem_NvMClearBlockByInvalidate(Dem_PreStoredFFNvmId[i]);
        }
        else
        {
            /* Get the Result of the NvM-Read (NvM_ReadAll) */
            NvmResult = Dem_NvmGetStatus (Dem_PreStoredFFNvmId[i]);

            /* Data read successfully */
            if (NvmResult == DEM_NVM_SUCCESS)
            {
                /* Check if eventid stored in the location is valid */
                if(!Dem_isEventIdValid(Dem_EvtBuffer.Locations[i].eventId))
                {
                    NvmResult = DEM_NVM_FAILED;
                }
            }

            if(NvmResult != DEM_NVM_SUCCESS)
            {
                /* Zero the content of this particular location */
                DEM_MEMSET(&Dem_EvtBuffer.Locations[i], 0, DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[i]));
                Dem_NvMWriteBlockOnShutdown(Dem_PreStoredFFNvmId[i]);
            }
        }
    }

    //to avoid problems with "saved zone" feature the rest has to be initialized to zero
    for (i = DEM_CFG_PRESTORED_FF_SIZE; i < DEM_CFG_EVBUFF_SIZE; i++)
    {
        /* Zero the content of this particular location */
        DEM_MEMSET(&Dem_EvtBuffer.Locations[i], 0, DEM_SIZEOF_VAR(Dem_EvtBuffer.Locations[i]));
    }
    //optional
    //Dem_EvtBuffer.OverflowCounter=0;
    //Dem_EvtBuffer.OverflowCounterSet=0;

#endif
}

/* Store prestored freeze frame in NVRAM*/
void Dem_PreStoredFFShutdown(void)
{
#if (DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
    uint8 i;

    for (i = 0; i < DEM_CFG_PRESTORED_FF_SIZE; i++)
    {
        Dem_NvMWriteBlockOnShutdown(Dem_PreStoredFFNvmId[i]);
    }
#endif
}
#endif // (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
