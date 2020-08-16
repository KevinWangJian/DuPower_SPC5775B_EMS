

#include "Dem.h"
#include "Rte_Dem.h"
#include "Dem_Dependencies.h"

#include "Dem_Events.h"
#include "Dem_EventStatus.h"
#include "Dem_Mapping.h"
#include "Dem_Cfg_ExtPrototypes.h"

#include "Dem_Obd.h"

#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

DEM_ARRAY_DEFINE(      Dem_NodeState, Dem_AllNodesState, DEM_NODEID_ARRAYLENGTH);

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"



#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

/* MR12 RULE 1.3 VIOLATION: A function-like macro shall not be invoked without all of its arguments, hence some of the arguments are optional based on configuration */
DEM_ARRAY_DEFINE_CONST(Dem_NodeParam, Dem_AllNodesParam, DEM_NODEID_ARRAYLENGTH, DEM_CFG_NODEPARAMS);
#if (DEM_CFG_NODEFAILEDCALLBACK_COUNT > 0)
DEM_ARRAY_DEFINE_CONST(Dem_NodeFailedCallbackType, Dem_NodeFailedCallbacks, DEM_CFG_NODEFAILEDCALLBACK_ARRAYLENGTH, DEM_CFG_NODEFAILEDCALLBACKS);
#endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"



#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_SetNodeStatus (const Dem_ComponentIdType NodeId, uint8 statusIndex)
{
    Dem_NodeIdListIterator childIt;

    DEM_ASSERT_ISLOCKED();
	if (!Dem_NodeStatusIsSet(Dem_AllNodesState[NodeId].status[statusIndex]))
	{
		Dem_NodeStatusSet(&(Dem_AllNodesState[NodeId].status[statusIndex]));
#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
        if ((statusIndex==DEM_NODESTATUS_FAILED)&&(!Dem_NodeStatusIsAnyAncestorSet(Dem_AllNodesState[NodeId].status[statusIndex])))
        {
            FiM_DemTriggerOnComponentStatus(NodeId, TRUE);
        }
#endif

		for (Dem_NodeIdListIteratorNewFromNodeId (&childIt, NodeId);
				Dem_NodeIdListIteratorIsValid (&childIt);
				Dem_NodeIdListIteratorNext (&childIt))
		{
			Dem_AllNodesState[Dem_NodeIdListIteratorCurrent(&childIt)].status[statusIndex]++;
#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
            if ((statusIndex==DEM_NODESTATUS_FAILED)&&(Dem_AllNodesState[Dem_NodeIdListIteratorCurrent(&childIt)].status[statusIndex] == 1))
            {
                FiM_DemTriggerOnComponentStatus(Dem_NodeIdListIteratorCurrent(&childIt), TRUE);
            }
#endif
		}
	}
}

static void Dem_ResetNodeStatus (const Dem_ComponentIdType NodeId, uint8 statusIndex)
{
    Dem_NodeIdListIterator childIt;

    DEM_ASSERT_ISLOCKED();
	if (Dem_NodeStatusIsSet(Dem_AllNodesState[NodeId].status[statusIndex]))
	{
		Dem_NodeStatusReset(&(Dem_AllNodesState[NodeId].status[statusIndex]));
#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
        if ((statusIndex==DEM_NODESTATUS_FAILED)&&(!Dem_NodeStatusIsAnyAncestorSet(Dem_AllNodesState[NodeId].status[statusIndex])))
        {
            FiM_DemTriggerOnComponentStatus(NodeId, FALSE);
        }
#endif

		for (Dem_NodeIdListIteratorNewFromNodeId (&childIt, NodeId);
				Dem_NodeIdListIteratorIsValid (&childIt);
				Dem_NodeIdListIteratorNext (&childIt))
		{
			Dem_AllNodesState[Dem_NodeIdListIteratorCurrent(&childIt)].status[statusIndex]--;
#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
            if ((statusIndex==DEM_NODESTATUS_FAILED)&&(Dem_AllNodesState[Dem_NodeIdListIteratorCurrent(&childIt)].status[statusIndex] == 0))
            {
                FiM_DemTriggerOnComponentStatus(Dem_NodeIdListIteratorCurrent(&childIt), FALSE);
            }
#endif
		}
	}
}


/* MR12 RULE 20.7 VIOLATION : Macro parameter FUNCTIONNAME may not be enclosed in (). */
#define DEM_NODE_CHECK_EVENTS_ATTRIBUTE(EVTIT, NODEID, FUNCTIONNAME, STATEVAR)             \
do {                                                                        \
	(STATEVAR) = FALSE;                                                     \
	for (Dem_EventIdListIterator2NewFromNodeId(&(EVTIT), NODEID);             \
			Dem_EventIdListIterator2IsValid(&(EVTIT));                        \
			Dem_EventIdListIterator2Next(&(EVTIT)))                           \
	{                                                                       \
		(STATEVAR) = (STATEVAR) || FUNCTIONNAME(Dem_EventIdListIterator2Current(&(EVTIT)));   \
	}                                                                       \
} while (FALSE)




typedef Dem_boolean_least (*DemEvtStatusFuncptr)(Dem_EventIdType EventId);

DEM_INLINE Dem_boolean_least Dem_Dependencies_CheckEventIsCausalGeneric(Dem_EventIdType EventId, Dem_ComponentIdType NodeId, uint8 StatusIndex, DemEvtStatusFuncptr FuncPointer)
{
    Dem_EventIdListIterator2 evtIt;

    DEM_ASSERT_ISLOCKED();

    if (!Dem_NodeIdIsValid(NodeId))
    {
        return TRUE;
    }

    /* DSM_D_37: failure sequential, if one ancestor is invalid */
    if ( Dem_NodeStatusIsAnyAncestorSet(Dem_AllNodesState[NodeId].status[StatusIndex]) )
    {
        return FALSE;
    }
    else
    {
        if (Dem_NodeIgnorePriority(NodeId))
        {
            return TRUE;
        }
        else
        {
            Dem_EventIdListIterator2NewFromNodeId (&evtIt, NodeId);

            /* DSM_D_37: failure sequential, if monitoring with higher */
            /* prio at node has reported failure */
            while (Dem_EventIdListIterator2IsValid(&evtIt))
            {
                /* only check events with higher prio at node; not event itself nor lower prio events, therefore cancel loop */
                if (Dem_EventIdListIterator2Current(&evtIt) == EventId)
                {
                    return TRUE;
                }

                if (FuncPointer(Dem_EventIdListIterator2Current(&evtIt)))
                {
                    return FALSE;
                }

                Dem_EventIdListIterator2Next (&evtIt);
            }
        }
    }

    /* should never be reached */
    DEM_ASSERT(Dem_LibGetParamBool(FALSE), DEM_DET_APIID_EVENTDEPENDENCIES_ISCAUSAL, 0);
    return TRUE;
}

Dem_boolean_least Dem_Dependencies_CheckEventIsCausal(Dem_EventIdType EventId, Dem_ComponentIdType NodeId)
{
    return Dem_Dependencies_CheckEventIsCausalGeneric(EventId, NodeId, DEM_NODESTATUS_FAILED, &Dem_EvtSt_GetTestFailed);
}

#if DEM_CFG_DEPENDENCY_PENDING_ON
/*To check the event is not having any stored pending OBD event(s) which is of higher prio to it in the graph .TRUE - no high prio pending OBD events*/
Dem_boolean_least Dem_Dependencies_CheckEventIsCausalPending(Dem_EventIdType EventId, Dem_ComponentIdType NodeId)
{
    return Dem_Dependencies_CheckEventIsCausalGeneric(EventId, NodeId, DEM_NODESTATUS_PENDING, &Dem_EvtSt_GetPending);
}

static void Dem_NodeSetPending(Dem_ComponentIdType NodeId, Dem_boolean_least IsPending)
{
    Dem_boolean_least anyEvtStoredPending;
    Dem_EventIdListIterator2 evtIt;

    DEM_ASSERT_ISLOCKED();

    if(IsPending)
    {
        Dem_SetNodeStatus (NodeId, DEM_NODESTATUS_PENDING);
    }
    else
    {
        DEM_NODE_CHECK_EVENTS_ATTRIBUTE (evtIt, NodeId, Dem_EvtSt_GetPending, anyEvtStoredPending);

        if(!anyEvtStoredPending)
        {
            Dem_ResetNodeStatus(NodeId, DEM_NODESTATUS_PENDING);
        }

    }
}

void Dem_Dependencies_SetNodePending(Dem_EventIdType EventId , Dem_boolean_least setBit)
{

    Dem_ComponentIdType NodeId;

    NodeId = Dem_NodeIdFromEventId(EventId);

    if (!Dem_NodeIdIsValid(NodeId))
    {
        return;
    }

    /* to Set/reset Node Status Pending */
    Dem_NodeSetPending( NodeId ,setBit);
}
#endif

void Dem_Dependencies_SetNodeFailed(Dem_ComponentIdType NodeId, boolean EventIsCausal, boolean EventStorageFiltered, boolean EventIsRecoverable)
{
    DEM_ASSERT_ISLOCKED();

    DEM_ASSERT(!(EventIsCausal && EventStorageFiltered), DEM_DET_APIID_EVENTDEPENDENCIES, 0);

    if (!Dem_NodeIdIsValid(NodeId))
    {
        return;
    }

    /* calculate statemachine */
    if (Dem_NodeIsFailedItself(NodeId))
    {
        if (Dem_NodeIsFailedFilteredItself(NodeId))
        {
            /* state FailedFiltered */
            if (EventIsCausal && !(EventStorageFiltered))
            {
                Dem_ResetNodeStatus(NodeId, DEM_NODESTATUS_FAILEDFILTERED);
                if (!EventIsRecoverable)
                {
                    Dem_SetNodeStatus(NodeId, DEM_NODESTATUS_FAILEDNOTRECOVERABLE);
                }
            }
        } else
        {
            /* state Failed */
            if (EventIsCausal && !EventIsRecoverable)
            {
                Dem_SetNodeStatus(NodeId, DEM_NODESTATUS_FAILEDNOTRECOVERABLE);
            }
        }
    } else
    {
        /* state Valid */
        Dem_SetNodeStatus(NodeId, DEM_NODESTATUS_FAILED);
        if (EventIsCausal && !EventIsRecoverable)
        {
            Dem_SetNodeStatus(NodeId, DEM_NODESTATUS_FAILEDNOTRECOVERABLE);
        } else
        {
            if (EventStorageFiltered)
            {
                Dem_SetNodeStatus(NodeId, DEM_NODESTATUS_FAILEDFILTERED);
            }
        }
        

        Dem_NodeCallFailedCallback(NodeId, TRUE);
    }
}


void Dem_Dependencies_ResetNodeFailed(Dem_ComponentIdType NodeId)
{
    Dem_boolean_least anyMonFailed;
    Dem_EventIdListIterator2 evtIt;

    if (!Dem_NodeIdIsValid(NodeId))
    {
        return;
    }

    DEM_ASSERT_ISLOCKED();

    DEM_NODE_CHECK_EVENTS_ATTRIBUTE (evtIt, NodeId, Dem_EvtSt_GetTestFailed, anyMonFailed);

    if (!anyMonFailed)
    {
        Dem_ResetNodeStatus(NodeId,DEM_NODESTATUS_FAILED);
        Dem_ResetNodeStatus(NodeId,DEM_NODESTATUS_FAILEDFILTERED);
        Dem_ResetNodeStatus(NodeId,DEM_NODESTATUS_FAILEDNOTRECOVERABLE);
        Dem_NodeCallFailedCallback(NodeId, FALSE);
    }
}


void Dem_Dependencies_ResetNodeFailedFiltered(Dem_ComponentIdType NodeId)
{
    DEM_ASSERT_ISLOCKED();
    Dem_ResetNodeStatus(NodeId,DEM_NODESTATUS_FAILEDFILTERED);
}


void Dem_Dependencies_ResetNodeFailedNotRecoverable(Dem_ComponentIdType NodeId)
{
    Dem_boolean_least anyMonNotRecoverable;
    Dem_EventIdListIterator2 evtIt;

    if (!Dem_NodeIdIsValid(NodeId))
    {
        return;
    }

    DEM_ASSERT_ISLOCKED();

    DEM_NODE_CHECK_EVENTS_ATTRIBUTE (evtIt, NodeId, Dem_EvtIsNotRecoverableTOC, anyMonNotRecoverable);

    if (!anyMonNotRecoverable)
    {
        Dem_ResetNodeStatus(NodeId,DEM_NODESTATUS_FAILEDNOTRECOVERABLE);
    }
}


void Dem_NodeSetSuspicious(Dem_ComponentIdType NodeId, Dem_boolean_least suspicious)
{
	Dem_boolean_least anyMonSuspicious;
	Dem_EventIdListIterator2 evtIt;

	DEM_ASSERT_ISLOCKED();

	if (suspicious)
	{
		Dem_SetNodeStatus (NodeId, DEM_NODESTATUS_SUSPICIOUS);
	}
	else
	{
		/* check if any event is testfailed at node */
		DEM_NODE_CHECK_EVENTS_ATTRIBUTE (evtIt, NodeId, Dem_EvtIsSuspicious, anyMonSuspicious);

		if (!anyMonSuspicious)
		{
			Dem_ResetNodeStatus(NodeId,DEM_NODESTATUS_SUSPICIOUS);
		}
	}
}



void Dem_NodeSetHasCausalFault (const Dem_ComponentIdType NodeId, Dem_boolean_least causalFault)
{
	Dem_EventIdListIterator2 evtIt;
	Dem_boolean_least hasCausalFault;


	DEM_ASSERT_ISLOCKED();

	if (causalFault)
	{
	    rba_DiagLib_Bit8OverwriteBit(&(Dem_AllNodesState[NodeId].stateFlags), DEM_NODE_STATEFLAG_HASCAUSALFAULT, TRUE);
	}
	else
	{
		DEM_NODE_CHECK_EVENTS_ATTRIBUTE (evtIt, NodeId, Dem_EvtIsCausal, hasCausalFault);
		rba_DiagLib_Bit8OverwriteBit(&(Dem_AllNodesState[NodeId].stateFlags), DEM_NODE_STATEFLAG_HASCAUSALFAULT, hasCausalFault);
	}
}


void Dem_NodeSetAvailable (Dem_ComponentIdType ComponentId, boolean AvailableStatus)
{
	DEM_ENTERLOCK_MON();

	if (!AvailableStatus)
	{
		Dem_SetNodeStatus (ComponentId, DEM_NODESTATUS_NOTAVAILABLE);
	}
	else
	{
		Dem_ResetNodeStatus(ComponentId, DEM_NODESTATUS_NOTAVAILABLE);
	}

	DEM_EXITLOCK_MON();
}


void Dem_NodeRecheckOnClear (void)
{
	Dem_NodeIdIterator nodeIt;
	for (Dem_NodeIdIteratorNew(&nodeIt); Dem_NodeIdIteratorIsValid(&nodeIt); Dem_NodeIdIteratorNext(&nodeIt))
	{
		if (Dem_NodeIsRecheckOnClear(Dem_NodeIdIteratorCurrent(&nodeIt)))
		{
		    DEM_ENTERLOCK_MON();
		    Dem_NodeSetRecheckOnClear (Dem_NodeIdIteratorCurrent(&nodeIt), FALSE);
			Dem_Dependencies_ResetNodeFailed(Dem_NodeIdIteratorCurrent(&nodeIt));
			Dem_NodeSetHasCausalFault(Dem_NodeIdIteratorCurrent(&nodeIt), FALSE);
            DEM_EXITLOCK_MON();
		}
	}
}

DEM_INLINE void Dem_SetEventAvailableFromNode(Dem_ComponentIdType ComponentId, boolean AvailableStatus)
{
    Dem_NodeIdListIterator childIt;
    Dem_EventIdListIterator2 evtIt;
    Dem_EventIdType eventId;

    for (Dem_EventIdListIterator2NewFromNodeId(&evtIt, ComponentId); Dem_EventIdListIterator2IsValid(&evtIt);
            Dem_EventIdListIterator2Next(&evtIt))
    {
        eventId = Dem_EventIdListIterator2Current(&evtIt);
        if (AvailableStatus == Dem_EvtIsSuppressed(eventId))
        {
            (void)Dem_SetEventAvailable(eventId, AvailableStatus);
        }
    }

    for (Dem_NodeIdListIteratorNewFromNodeId(&childIt, ComponentId); Dem_NodeIdListIteratorIsValid(&childIt);
            Dem_NodeIdListIteratorNext(&childIt))
    {
        for (Dem_EventIdListIterator2NewFromNodeId(&evtIt, Dem_NodeIdListIteratorCurrent(&childIt));
                Dem_EventIdListIterator2IsValid(&evtIt);
                Dem_EventIdListIterator2Next(&evtIt))
        {
            eventId = Dem_EventIdListIterator2Current(&evtIt);
            if (AvailableStatus == Dem_EvtIsSuppressed(eventId))
            {
                (void)Dem_SetEventAvailable(eventId, AvailableStatus);
            }
        }
    }
}

Std_ReturnType Dem_SetComponentAvailable(Dem_ComponentIdType ComponentId, boolean AvailableStatus)
{
    /*  Entry Condition Check */
    DEM_ENTRY_CONDITION_CHECK_DEM_PREINITIALIZED(DEM_DET_APIID_DEM_SETCOMPONENTAVAILABLE,E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_COMPONENT_ID_VALID(ComponentId , DEM_DET_APIID_DEM_SETCOMPONENTAVAILABLE , E_NOT_OK);

    Dem_NodeSetAvailable(ComponentId, AvailableStatus);
    Dem_SetEventAvailableFromNode(ComponentId, AvailableStatus);
    return E_OK;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentSuspicious (Dem_ComponentIdType ComponentId, boolean* ComponentSuspicious)
{
#if ((DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON) && (DEM_CFG_SUSPICIOUS_SUPPORT))
    if ((!Dem_NodeIdIsValid(ComponentId)) && (!Dem_NodeIsAvailable (ComponentId)))
    {
        return E_NOT_OK;
    }

    *ComponentSuspicious = Dem_NodeIsSuspicious(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentSuspicious);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentUsable (Dem_ComponentIdType ComponentId, boolean* ComponentUsable)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    if(!Dem_NodeIdIsValid(ComponentId))
    {
        return E_NOT_OK;
    }

    *ComponentUsable = Dem_NodeIsUsable(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentUsable);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentRestrictedUsable (Dem_ComponentIdType ComponentId, boolean* ComponentRestrictedUsable)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    if(!Dem_NodeIdIsValid(ComponentId))
    {
        return E_NOT_OK;
    }

   *ComponentRestrictedUsable = Dem_NodeIsRestrictedUsable(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentRestrictedUsable);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentInitialized (Dem_ComponentIdType ComponentId, boolean* ComponentInitialized)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    if(!Dem_NodeIdIsValid(ComponentId))
    {
        return E_NOT_OK;
    }

    *ComponentInitialized = Dem_NodeIsInitialized(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentInitialized);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentFailed (Dem_ComponentIdType ComponentId, boolean* ComponentFailed)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

    /*  Entry Condition Check    */
    DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_DEM_GETCOMPONENTFAILED, E_NOT_OK );
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(ComponentFailed,DEM_DET_APIID_DEM_GETCOMPONENTFAILED,E_NOT_OK );
    DEM_ENTRY_CONDITION_CHECK_COMPONENT_ID_VALID(ComponentId , DEM_DET_APIID_DEM_SETCOMPONENTAVAILABLE , E_NOT_OK);

    *ComponentFailed = Dem_NodeIsFailed(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentFailed);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentFailedItself(Dem_ComponentIdType ComponentId, boolean* ComponentFailedItself)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    if(!Dem_NodeIdIsValid(ComponentId))
    {
        return E_NOT_OK;
    }

   *ComponentFailedItself = Dem_NodeIsFailedItself(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentFailedItself);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentSuspiciousItself(Dem_ComponentIdType ComponentId, boolean* ComponentSuspiciousItself)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    if(!Dem_NodeIdIsValid(ComponentId))
    {
        return E_NOT_OK;
    }

   *ComponentSuspiciousItself = Dem_NodeIsSuspiciousItself(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentSuspiciousItself);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentAvailable(Dem_ComponentIdType ComponentId, boolean* ComponentAvailable)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    if(!Dem_NodeIdIsValid(ComponentId))
    {
        return E_NOT_OK;
    }

   *ComponentAvailable = Dem_NodeIsAvailable(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentAvailable);
    return E_NOT_OK;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
Std_ReturnType Dem_GetComponentAreAncestorsInitialized(Dem_ComponentIdType ComponentId, boolean* ComponentAreAncestorsInitialized)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    if(!Dem_NodeIdIsValid(ComponentId))
    {
        return E_NOT_OK;
    }
   *ComponentAreAncestorsInitialized = Dem_NodeAreAncestorsInitialized(ComponentId);
    return E_OK;
#else
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(ComponentAreAncestorsInitialized);
    return E_NOT_OK;
#endif
}


void Dem_NodeSetInitialized(Dem_ComponentIdType NodeId, boolean init)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    DEM_ENTERLOCK_MON();

    if (!init)
    {
        Dem_SetNodeStatus (NodeId, DEM_NODESTATUS_NOTINIT);
    }
    else
    {
        Dem_ResetNodeStatus(NodeId,DEM_NODESTATUS_NOTINIT);
    }

    DEM_EXITLOCK_MON();
#else
    DEM_UNUSED_PARAM(NodeId);
    DEM_UNUSED_PARAM(init);
#endif
}



/*************************************************************************************
 * simple querry functions, which are also provided publically
 */

#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

boolean Dem_NodeAreAncestorsFailed(Dem_ComponentIdType NodeId)
{
    return Dem_NodeStatusIsAnyAncestorSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILED]);
}

boolean Dem_NodeAreAncestorsSuspicious(Dem_ComponentIdType NodeId)
{
    return Dem_NodeStatusIsAnyAncestorSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_SUSPICIOUS]);
}

boolean Dem_NodeAreAncestorsAvailable(Dem_ComponentIdType NodeId)
{
    return !Dem_NodeStatusIsAnyAncestorSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_NOTAVAILABLE]);
}

boolean Dem_NodeAreAncestorsRestrictedUsable(Dem_ComponentIdType NodeId)
{
    return (   (Dem_NodeAreAncestorsInitialized(NodeId))
            && (Dem_NodeAreAncestorsAvailable(NodeId))
            && (!Dem_NodeAreAncestorsFailed(NodeId))
            );
}

boolean Dem_NodeAreAncestorsUsable(Dem_ComponentIdType NodeId)
{
    return (   (Dem_NodeAreAncestorsRestrictedUsable(NodeId))
            && (!Dem_NodeAreAncestorsSuspicious(NodeId))
            );
}

boolean Dem_NodeHasCausalFault (Dem_ComponentIdType NodeId)
{
    return rba_DiagLib_Bit8IsBitSet(Dem_AllNodesState[NodeId].stateFlags, DEM_NODE_STATEFLAG_HASCAUSALFAULT);
}

boolean Dem_NodeAreAllFailedFiltered(Dem_ComponentIdType NodeId)
{
    return (   (Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILEDFILTERED] != 0)
            && (   Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILEDFILTERED]
                == Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILED]
               )
            );
}

#else /* DEM_CFG_DEPENDENCY */

boolean Dem_NodeAreAllFailedFiltered(Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(NodeId);
    return FALSE;
}

#endif /* DEM_CFG_DEPENDENCY */



#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

