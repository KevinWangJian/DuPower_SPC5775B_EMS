

#include "Dem_EventRecheck.h"
#include "Dem_Types.h"
#include "Dem_Events.h"
#include "Dem_EventStatus.h"
#include "Dem_EvBuffEvent.h"
#include "Dem_EvBuff.h"
#include "Dem_Lock.h"
#include "Dem_Mapping.h"
#include "Dem_Dependencies.h"
#include "Dem_Helpers.h"
#include "Dem_Obd.h"


#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)


#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"

#define DEM_RECHECK_DECREASE_VALUE_FOR_RECHECKED_EVENT  5

static boolean Dem_RecheckRecheckNodeNotRecoverableRequested = FALSE;

#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"




#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_DependencyInit(void)
{
	Dem_EventIdListIterator2 evtIt;
	Dem_NodeIdIterator nodeIt;
	Dem_ComponentIdType currentNode;
    Dem_boolean_least setFailed;

#if DEM_CFG_DEPENDENCY_PENDING_ON
    Dem_boolean_least setPending;
#endif

	/* set Failed state of all nodes according to failed state of events restored from NVM */
	for (Dem_NodeIdIteratorNew(&nodeIt); Dem_NodeIdIteratorIsValid(&nodeIt); Dem_NodeIdIteratorNext(&nodeIt))
	{
		currentNode = Dem_NodeIdIteratorCurrent(&nodeIt);
		setFailed = FALSE;
#if DEM_CFG_DEPENDENCY_PENDING_ON
        setPending = FALSE;
#endif

		DEM_ENTERLOCK_MON();

		for (Dem_EventIdListIterator2NewFromNodeId (&evtIt, currentNode);
				Dem_EventIdListIterator2IsValid(&evtIt);
				Dem_EventIdListIterator2Next (&evtIt))
		{
			if ( Dem_EvtSt_GetTestFailed(Dem_EventIdListIterator2Current(&evtIt)) && (!setFailed))
			{
			    Dem_SetNodeStatus (currentNode, DEM_NODESTATUS_FAILED);
                setFailed = TRUE;
				/* explicitly requested to have the same behavior on startup and on failed-report according callback */
				Dem_NodeCallFailedCallback(currentNode, TRUE);
			}

#if DEM_CFG_DEPENDENCY_PENDING_ON
            if (Dem_EvtSt_GetPending(Dem_EventIdListIterator2Current(&evtIt)) && (!setPending))
            {
                (void)Dem_SetNodeStatus (currentNode, DEM_NODESTATUS_PENDING);
                setPending = TRUE;
            }
#endif

            if( setFailed
#if DEM_CFG_DEPENDENCY_PENDING_ON
                    && setPending
#endif
            )
            {
                break; /* if at lest one event is failed (and pending), the node is failed (and pending) and no further event of this
                            node needs to be checked */
            }
        }

		DEM_EXITLOCK_MON();
	}
}



/********************************************************************************************************
 * Recheck of the node recoverable information
 */

void Dem_RecheckNodeNotRecoverableRequest(void)
{
    Dem_RecheckRecheckNodeNotRecoverableRequested = TRUE;
}

static void Dem_RecheckNodeNotRecoverable(void)
{
    /** perform a recheck of nodeNotRecoverable information after a change of operationcycle,
     * as events may become recoverable due to the OpCycle change
     */

    Dem_NodeIdIterator nodeIt;
    Dem_ComponentIdType node;

    if (Dem_RecheckRecheckNodeNotRecoverableRequested)
    {
        for (Dem_NodeIdIteratorNew(&nodeIt); Dem_NodeIdIteratorIsValid(&nodeIt); Dem_NodeIdIteratorNext(&nodeIt))
        {
            node = Dem_NodeIdIteratorCurrent(&nodeIt);
            if (Dem_NodeIsFailedNotRecoverableItself(node))
            {
                DEM_ENTERLOCK_MON();
                Dem_Dependencies_ResetNodeFailedNotRecoverable(node);
                DEM_EXITLOCK_MON();
            }
        }

        Dem_RecheckRecheckNodeNotRecoverableRequested = FALSE;
    }
}



/********************************************************************************************************
 * Recheck of the event is causal information
 */

/* The restart of cyclic check (Dem_DependencyRestartCyclicCheck) is no longer required, as the function
 * Dem_Dependencies_CheckEventIsCausal always checks the status of the ancestors and all events with higher
 * priority at same node. Therefore a reenabling of storage condition will properly be considered
 */


static void Dem_DependencyRecheckCausalityOfEvent (Dem_EventIdType EventId, Dem_ComponentIdType NodeId)
{
    Dem_EvBuffEventType eventType = C_EVENTTYPE_SET_WAITINGFORMONITORING;
    Dem_boolean_least triggerEvBuffInsert = FALSE;
    Dem_boolean_least triggerCalcNodeHasFilteredStorage = FALSE;
    Dem_boolean_least newIsCausal, areAllFulfilled;

    DEM_ENTERLOCK_MON();

    if (    Dem_EvtSt_GetTestFailed(EventId)
            && Dem_NodeIsAvailable (NodeId)
            && !Dem_EvtIsSuppressed(EventId)
       )
    {
        /* SEQUENTIAL and STORAGEISFILTERED */
        if (!Dem_EvtIsCausal(EventId))
        {
            newIsCausal = Dem_Dependencies_CheckEventIsCausal(EventId, NodeId);
            areAllFulfilled = Dem_StoCoAreAllFulfilled(Dem_EvtGetStorageConditions(EventId));


            /* STORAGEISFILTERED -> ISCAUSAL   and  SEQUENTIAL -> ISCAUSAL */
            if (newIsCausal)
            {
                if (areAllFulfilled)
                {
                    Dem_EvtSetCausal (EventId, TRUE);
                    Dem_EvtSetIsRecheckedAndWaitingForMonResult(EventId, TRUE);
                    Dem_EvtSetStorageFiltered (EventId, FALSE);

                    Dem_EvtSetInitMonitoring (EventId, DEM_INIT_MONITOR_STORAGE_REENABLED);

                    Dem_Dependencies_ResetNodeFailedFiltered(NodeId);
                    triggerEvBuffInsert = TRUE;
                }
                else
                {
                    Dem_StoCoRecheckReplacementStorage(Dem_EvtGetStorageConditions(EventId));
                }
            }

            /* SEQUENTIAL -> STORAGEISFILTERED */
            if (!Dem_EvtIsStorageFiltered(EventId) && newIsCausal && !areAllFulfilled)
            {
                Dem_StoCoSetHasFilteredEvent(Dem_EvtGetStorageConditions(EventId)
                            DEM_DEBUGDATA_PARAM((Dem_DebugDataType)EventId,0));
                triggerCalcNodeHasFilteredStorage = TRUE;
            }
        }

        /* INVALID_STATE: Causal & StorageFiltered shall not occure, but must be rechecked! */
        if (   Dem_EvtIsCausal(EventId)
            && Dem_EvtIsStorageFiltered(EventId)
        )
        {
            if (Dem_StoCoAreAllFulfilled(Dem_EvtGetStorageConditions(EventId)))
            {
                Dem_EvtSetStorageFiltered (EventId, FALSE);
            }
            else
            {
                Dem_EvtSetCausal (EventId, FALSE);
                Dem_StoCoSetHasFilteredEvent(Dem_EvtGetStorageConditions(EventId)
                                            DEM_DEBUGDATA_PARAM((Dem_DebugDataType)EventId,0));
            }
        }
    }

    DEM_EXITLOCK_MON();

    if (triggerEvBuffInsert)
    {
        if (!Dem_EvBuffInsert (eventType, EventId DEM_DEBUGDATA_PARAM((Dem_DebugDataType)0xffffffffu, (Dem_DebugDataType)0xffffffffu)))
        {
            DEM_ENTERLOCK_MON();
            Dem_EvtSetCausal (EventId, FALSE);
            Dem_EvtSetIsRecheckedAndWaitingForMonResult(EventId, FALSE);
            DEM_EXITLOCK_MON();
        }
   }
}


static void Dem_Dependency_RecheckCausalityMain (void)
{
    /* check all EventIds; whether they were not stored due to an evbuffer overflow */

    static Dem_EventIdIterator Dem_RecheckEventIterator = DEM_EVENTIDITERATORNEW;
    Dem_EventIdType eventId;
    sint16_least eventsCheckedCounter = DEM_MIN(DEM_CFG_FAILUREDEPENDENCY_RECHECK_LIMIT, DEM_EVENTID_COUNT); // search configured number, but at maximum number of events

    while (eventsCheckedCounter > 0)
    {
        eventsCheckedCounter--;
        eventId = Dem_EventIdIteratorCurrent(&Dem_RecheckEventIterator);

        /* if event is failed and either filtered or not causal  then perform recheck */
        if (   Dem_EvtSt_GetTestFailed(eventId)
            && (   !Dem_EvtIsCausal(eventId)
                || Dem_EvtIsStorageFiltered(eventId)
               )
           )
        {
            /* recheck causality, insert into SFB and set GCT */
            Dem_DependencyRecheckCausalityOfEvent(eventId, Dem_NodeIdFromEventId(eventId));

            /* the actual check is more time consuming so additionally dec the counter (load-balancing of mainfunction) */
            eventsCheckedCounter -= DEM_RECHECK_DECREASE_VALUE_FOR_RECHECKED_EVENT  ;
        }

        Dem_EventIdIteratorNext(&Dem_RecheckEventIterator);
        if (!Dem_EventIdIteratorIsValid(&Dem_RecheckEventIterator))
        {
            Dem_EventIdIteratorNew(&Dem_RecheckEventIterator);
        }
    }
}



void Dem_DependencyMainFunction(void)
{
    Dem_Dependency_RecheckCausalityMain ();
    Dem_RecheckNodeNotRecoverable();
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

