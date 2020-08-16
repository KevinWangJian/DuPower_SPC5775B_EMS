

#ifndef DEM_NODES_H
#define DEM_NODES_H


#include "Dem_Types.h"
#include "Dem_Cfg_Nodes.h"
#include "Dem_Cfg_NodeId.h"
#include "Dem_Cfg_StorageCondition.h"
#include "Dem_Array.h"
#include "rba_DiagLib_Bits8.h"


#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)


#define DEM_NODE_INFINITE_RECOVERIES  255
#define DEM_NODE_NO_RECOVERIES          0

#define DEM_NODESTATUS_FAILED                   0
#define DEM_NODESTATUS_SUSPICIOUS               1
#define DEM_NODESTATUS_NOTINIT                  2
#define DEM_NODESTATUS_NOTAVAILABLE             3
#define DEM_NODESTATUS_FAILEDFILTERED           4
#define DEM_NODESTATUS_FAILEDNOTRECOVERABLE     5
#define DEM_NODESTATUS_PENDING                  6

#if DEM_CFG_DEPENDENCY_PENDING_ON
#define DEM_NODESTATUS_COUNT                    7
#else
#define DEM_NODESTATUS_COUNT                    6
#endif

#define DEM_NODESTATUS__NODEMASK               ((uint8)0x80)
#define DEM_NODESTATUS__ANCESTORMASK           ((uint8)0x7F)


DEM_INLINE void Dem_NodeStatusSet(uint8 *status)            { (*status) |= DEM_NODESTATUS__NODEMASK;  }
DEM_INLINE void Dem_NodeStatusReset(uint8 *status)          { (*status) &= (uint8)~DEM_NODESTATUS__NODEMASK; }
DEM_INLINE Dem_boolean_least Dem_NodeStatusIsSet(uint8 status)  { return ((status) & DEM_NODESTATUS__NODEMASK) > 0; }
DEM_INLINE uint8 Dem_NodeStatusAncestorCounter(uint8 status)  { return ((status) & DEM_NODESTATUS__ANCESTORMASK); }
DEM_INLINE Dem_boolean_least Dem_NodeStatusIsAnyAncestorSet (uint8 status) { return ((status) & DEM_NODESTATUS__ANCESTORMASK) > 0; }


typedef struct
{
	uint8 status[DEM_NODESTATUS_COUNT];
#if (DEM_CFG_DEPRECOVERYLIMIT == DEM_CFG_DEPRECOVERYLIMIT_ON)
	uint8 performedRecoveries;
#endif
	uint8 stateFlags;
} Dem_NodeState;

#define DEM_NODE_STATEFLAG_RECHECKONCLEAR    0
#define DEM_NODE_STATEFLAG_HASCAUSALFAULT    1
#define DEM_NODE_STATEFLAG_RECOVERYBLOCKED    2


typedef struct
{
#if (DEM_CFG_DEPRECOVERYLIMIT == DEM_CFG_DEPRECOVERYLIMIT_ON)
	uint8 allowedRecoveries;
#endif
#if (DEM_CFG_NODEFAILEDCALLBACK_COUNT > 0)
	uint8 nodeFailedCallbackIdx;
#endif
	uint8 paramFlags;
} Dem_NodeParam;

typedef Std_ReturnType (*Dem_NodeFailedCallbackType)(boolean testFailed);


#define DEM_NODE_PARAMFLAG_IGNOREPRIORITY    0

#if (DEM_CFG_DEPRECOVERYLIMIT == DEM_CFG_DEPRECOVERYLIMIT_ON)
	#define DEM_NODES_INIT_ALLOWEDRECOVERIES(X)    (X),
#else
	#define DEM_NODES_INIT_ALLOWEDRECOVERIES(X)
#endif
#if (DEM_CFG_NODEFAILEDCALLBACK_COUNT > 0)
	#define DEM_NODES_INIT_NODEFAILEDCALLBACK(X)    (X),
#else
	#define DEM_NODES_INIT_NODEFAILEDCALLBACK(X)
#endif

#define DEM_NODES_INIT(ALLOWEDRECOVERIES,IGNORES_PRIO,NODEFAILEDCALLBACK)        \
    {                                              			  \
		DEM_NODES_INIT_ALLOWEDRECOVERIES(ALLOWEDRECOVERIES)   \
		DEM_NODES_INIT_NODEFAILEDCALLBACK(NODEFAILEDCALLBACK)  \
		((IGNORES_PRIO) << DEM_NODE_PARAMFLAG_IGNOREPRIORITY)   \
    }



#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

DEM_ARRAY_DECLARE(      Dem_NodeState, Dem_AllNodesState, DEM_NODEID_ARRAYLENGTH);

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"



#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

DEM_ARRAY_DECLARE_CONST(Dem_NodeParam, Dem_AllNodesParam, DEM_NODEID_ARRAYLENGTH);
DEM_ARRAY_DECLARE_CONST(Dem_NodeFailedCallbackType, Dem_NodeFailedCallbacks, DEM_CFG_NODEFAILEDCALLBACK_ARRAYLENGTH);

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"



#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_SetNodeStatus (const Dem_ComponentIdType NodeId, uint8 statusIndex);

Dem_boolean_least Dem_Dependencies_CheckEventIsCausal(Dem_EventIdType EventId, Dem_ComponentIdType NodeId);

#if DEM_CFG_DEPENDENCY_PENDING_ON
Dem_boolean_least Dem_Dependencies_CheckEventIsCausalPending(Dem_EventIdType EventId, Dem_ComponentIdType NodeId);
void Dem_Dependencies_SetNodePending(Dem_EventIdType EventId , Dem_boolean_least setBit);
#endif


/*************   Status Querries   ***************/

DEM_INLINE boolean Dem_NodeIsFailed(Dem_ComponentIdType NodeId)
{
	return (Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILED] != 0);
}

DEM_INLINE boolean Dem_NodeIsFailedItself(Dem_ComponentIdType NodeId)
{
	return Dem_NodeStatusIsSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILED]);
}


DEM_INLINE boolean Dem_NodeIsSuspicious(Dem_ComponentIdType NodeId)
{
   return (Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_SUSPICIOUS] != 0);
}

DEM_INLINE boolean Dem_NodeIsSuspiciousItself(Dem_ComponentIdType NodeId)
{
   return Dem_NodeStatusIsSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_SUSPICIOUS]);
}


DEM_INLINE boolean Dem_NodeIsFailedFilteredItself(Dem_ComponentIdType NodeId)
{
   return (Dem_NodeStatusIsSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILEDFILTERED]));
}


DEM_INLINE boolean Dem_NodeIsFailedNotRecoverable(Dem_ComponentIdType NodeId)
{
    return (Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILEDNOTRECOVERABLE] != 0);
}

DEM_INLINE boolean Dem_NodeIsFailedNotRecoverableItself(Dem_ComponentIdType NodeId)
{
    return Dem_NodeStatusIsSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_FAILEDNOTRECOVERABLE]);
}


DEM_INLINE boolean Dem_NodeIsAvailable(Dem_ComponentIdType NodeId)
{
	   return (Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_NOTAVAILABLE] == 0);
}


DEM_INLINE boolean Dem_NodeIsInitialized(Dem_ComponentIdType NodeId)
{
	   return (Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_NOTINIT] == 0);
}

DEM_INLINE boolean Dem_NodeAreAncestorsInitialized(Dem_ComponentIdType NodeId)
{
	return !Dem_NodeStatusIsAnyAncestorSet(Dem_AllNodesState[NodeId].status[DEM_NODESTATUS_NOTINIT]);
}

DEM_INLINE boolean Dem_NodeIsRestrictedUsable(Dem_ComponentIdType NodeId)
{
	return (   (Dem_NodeIsInitialized(NodeId))
			&& (Dem_NodeIsAvailable(NodeId))
			&& (!Dem_NodeIsFailed(NodeId))
			);
}

DEM_INLINE boolean Dem_NodeIsUsable(Dem_ComponentIdType NodeId)
{
	return (   (Dem_NodeIsRestrictedUsable(NodeId))
			&& (!Dem_NodeIsSuspicious(NodeId))
			);
}



DEM_INLINE boolean Dem_NodeRecoveryAllowed (Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(NodeId);

    return (TRUE
#if (DEM_CFG_DEPRECOVERYLIMIT == DEM_CFG_DEPRECOVERYLIMIT_ON)
            && (    (Dem_AllNodesState[NodeId].performedRecoveries < Dem_AllNodesParam[NodeId].allowedRecoveries)
                 || (DEM_NODE_INFINITE_RECOVERIES == Dem_AllNodesParam[NodeId].allowedRecoveries)
               )

#endif
           );
}


DEM_INLINE void Dem_NodeCallFailedCallback (Dem_ComponentIdType NodeId, boolean failed)
{
#if (DEM_CFG_NODEFAILEDCALLBACK_COUNT > 0)
	if (Dem_AllNodesParam[NodeId].nodeFailedCallbackIdx != 0)
	{
		(Dem_NodeFailedCallbacks[Dem_AllNodesParam[NodeId].nodeFailedCallbackIdx])(failed);
	}
#else
	DEM_UNUSED_PARAM(NodeId);
	DEM_UNUSED_PARAM(failed);
#endif
}


void Dem_NodeSetFailed(Dem_ComponentIdType NodeId, Dem_boolean_least failed, Dem_boolean_least forceReset);
void Dem_Dependencies_SetNodeFailed(Dem_ComponentIdType NodeId, boolean EventIsCausal, boolean EventStorageFiltered, boolean EventIsRecoverable);
void Dem_Dependencies_ResetNodeFailed(Dem_ComponentIdType NodeId);
void Dem_Dependencies_ResetNodeFailedFiltered(Dem_ComponentIdType NodeId);
void Dem_Dependencies_ResetNodeFailedNotRecoverable(Dem_ComponentIdType NodeId);

void Dem_NodeSetSuspicious(Dem_ComponentIdType NodeId, Dem_boolean_least suspicious);
void Dem_NodeSetHasCausalFault (const Dem_ComponentIdType NodeId, Dem_boolean_least causalFault);

void Dem_NodeSetAvailable(Dem_ComponentIdType ComponentId, boolean AvailableStatus);


DEM_INLINE void Dem_NodeSetRecovered(Dem_ComponentIdType NodeId)
{
	DEM_UNUSED_PARAM(NodeId);
#if (DEM_CFG_DEPRECOVERYLIMIT == DEM_CFG_DEPRECOVERYLIMIT_ON)
	if (Dem_AllNodesState[NodeId].performedRecoveries < Dem_AllNodesParam[NodeId].allowedRecoveries)
	{
		Dem_AllNodesState[NodeId].performedRecoveries++;
	}
#endif
}

DEM_INLINE void Dem_NodeSetRecoveryBlocked (Dem_ComponentIdType NodeId, Dem_boolean_least newHasTriggered)
{
    rba_DiagLib_Bit8OverwriteBit(&(Dem_AllNodesState[NodeId].stateFlags), DEM_NODE_STATEFLAG_RECOVERYBLOCKED, newHasTriggered);
}

DEM_INLINE Dem_boolean_least Dem_NodeIsRecoveryBlocked (Dem_ComponentIdType NodeId)
{
	return rba_DiagLib_Bit8IsBitSet(Dem_AllNodesState[NodeId].stateFlags, DEM_NODE_STATEFLAG_RECOVERYBLOCKED);
}

DEM_INLINE void Dem_NodeSetRecheckOnClear (Dem_ComponentIdType NodeId, Dem_boolean_least newRecheckOnClear)
{
    rba_DiagLib_Bit8OverwriteBit(&(Dem_AllNodesState[NodeId].stateFlags), DEM_NODE_STATEFLAG_RECHECKONCLEAR, newRecheckOnClear);
}

DEM_INLINE Dem_boolean_least Dem_NodeIsRecheckOnClear (Dem_ComponentIdType NodeId)
{
	return rba_DiagLib_Bit8IsBitSet(Dem_AllNodesState[NodeId].stateFlags, DEM_NODE_STATEFLAG_RECHECKONCLEAR);
}

DEM_INLINE Dem_boolean_least Dem_NodeIgnorePriority(Dem_ComponentIdType NodeId)
{
	return rba_DiagLib_Bit8IsBitSet(Dem_AllNodesParam[NodeId].paramFlags, DEM_NODE_PARAMFLAG_IGNOREPRIORITY);
}



void Dem_NodeRecheckOnClear (void);






#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


#else

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


DEM_INLINE Dem_boolean_least Dem_Dependencies_CheckEventIsCausal(Dem_EventIdType EventId, Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(NodeId);
    return TRUE;
}
DEM_INLINE void Dem_Dependencies_ResetNodeFailed(Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(NodeId);
}

DEM_INLINE void Dem_Dependencies_SetNodeFailed(Dem_ComponentIdType NodeId, boolean EventIsCausal, boolean EventStorageFiltered, boolean EventIsRecoverable)
{
    DEM_UNUSED_PARAM(NodeId);
    DEM_UNUSED_PARAM(EventIsCausal);
    DEM_UNUSED_PARAM(EventStorageFiltered);
    DEM_UNUSED_PARAM(EventIsRecoverable);
}

DEM_INLINE void Dem_Dependencies_ResetNodeFailedFiltered(Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(NodeId);
}


DEM_INLINE boolean Dem_NodeIsAvailable(Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(NodeId);
    return TRUE;
}


DEM_INLINE boolean Dem_NodeRecoveryAllowed (Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(NodeId);
    return TRUE;
}

DEM_INLINE void Dem_NodeSetRecovered(Dem_ComponentIdType NodeId)
{
    DEM_UNUSED_PARAM(NodeId);
}

DEM_INLINE void Dem_NodeSetFailed(Dem_ComponentIdType NodeId, Dem_boolean_least failed, Dem_boolean_least forceReset)
{
    DEM_UNUSED_PARAM(forceReset);
    DEM_UNUSED_PARAM(NodeId);
    DEM_UNUSED_PARAM(failed);
}

DEM_INLINE void Dem_NodeSetSuspicious(Dem_ComponentIdType NodeId, Dem_boolean_least suspicious)
{
    DEM_UNUSED_PARAM(NodeId);
    DEM_UNUSED_PARAM(suspicious);
}

DEM_INLINE Std_ReturnType Dem_NodeSetAvailable (Dem_ComponentIdType ComponentId, boolean AvailableStatus)
{
    DEM_UNUSED_PARAM(ComponentId);
    DEM_UNUSED_PARAM(AvailableStatus);
    return E_OK;
}

DEM_INLINE void Dem_NodeSetHasCausalFault (const Dem_ComponentIdType NodeId, Dem_boolean_least causalFault)
{
    DEM_UNUSED_PARAM(NodeId);
    DEM_UNUSED_PARAM(causalFault);
}

DEM_INLINE void Dem_NodeSetRecheckOnClear (Dem_ComponentIdType NodeId, Dem_boolean_least newRecheckOnClear) { DEM_UNUSED_PARAM(NodeId); DEM_UNUSED_PARAM(newRecheckOnClear); }
DEM_INLINE void Dem_NodeRecheckOnClear (void) {}



#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif


#endif
