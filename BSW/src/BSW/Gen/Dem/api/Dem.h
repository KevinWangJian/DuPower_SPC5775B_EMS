


#ifndef DEM_H
#define DEM_H


/**
 * \file
 * \brief DEM-Interface according to AUTOSAR 4.2
 */


#include "Dem_Types.h"

#include "Dem_Cfg_Version.h"
#include "Dem_Cfg_EventId.h"
#include "Dem_Cfg_DtcId.h"
#include "Dem_Cfg_NodeId.h"
#include "Dem_Cfg_Main.h"
#include "Dem_Cfg_Deb.h"
#include "Dem_Cfg_EnableCondition.h"
#include "Dem_Cfg_EventCategory.h"
#include "Dem_Cfg_EventIndicators.h"
#include "Dem_Cfg_OperationCycle.h"
#include "Dem_Cfg_StorageCondition.h"

#include "Dem_Dlt.h"      /* For backward compatibility. Remove as soon as the Dlt has updated its #includes to
                             Dem_Dlt.h instead of Dem.h */
#include "Dem_Dcm.h"      /* For backward compatibility. Remove as soon as the Dcm has updated its #includes to
                             Dem_Dcm.h instead of Dem.h */
#include "Dem_J1939Dcm.h" /* For backward compatibility. Remove as soon as the J1939Dcm has updated its #includes to
                             Dem_J1939Dcm.h instead of Dem.h */

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
#include "rba_DemBfm.h"
#endif

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
#include "rba_DemObdBasic.h"
#endif

#ifdef DEM_CFG_EXTPROTOTYPES_H
#error "Do not include 'Dem_Cfg_ExtPrototypes.h' in header file"
#endif

/**
 * \defgroup DEM_H    DEM - Public interface
 * This interface provides functionality to report errors
 * as specified by AUTOSAR.\n
 * To use this interface include the header <b>Dem.h</b>
 * @{
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/* ---------------------------------------- */
/* RTE / BSWMD API                          */
/* ---------------------------------------- */
#if (DEM_CFG_CHECKAPICONSISTENCY == FALSE)
    #ifndef RTE_TYPE_H
    #error "If the RTE is not used, then /Dem/DemGeneral/DemRbGeneral/DemRbCheckApiConsistency has to be set to True."
    #endif

#else  /* DEM_CFG_CHECKAPICONSISTENCY */

#if (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
/** @AR @RTE
 *
 * Dem205: Gets the indicator status derived from the event status.
 *
 * @param [in]  IndicatorId         Number of indicator
 * @param [out] IndicatorStatus     Status of the indicator, like off, on, or blinking.
 * @return  E_OK = Get Indicator Status operation was successful \n
 *          E_NOT_OK = Get Indicator Status operation failed or is not supported
 */
Std_ReturnType Dem_GetIndicatorStatus(uint8 IndicatorId, Dem_IndicatorStatusType* IndicatorStatus);
#endif

/** @AR @RTE
 *
 * Gets information about the status of a specific operation cycle. This API \n
 * can only be used through the RTE and therefore no declaration is exported via Dem.h.
 *
 * @param [in]   OperationCycleId   Identification of operation cycle, like power cycle, driving cycle.
 * @param [out]  CycleState         Cycle status information
 * @return  E_OK: read out of operation cycle was successful\n
 *          E_NOT_OK: read out of operation cycle failed
 */
Std_ReturnType Dem_GetOperationCycleState(uint8 OperationCycleId, Dem_OperationCycleStateType* CycleState);


/** @AR
 *
 * Dem266: Processes all not event based Dem internal functions.
 */
void Dem_MainFunction(void);


/** @AR @RTE
 *
 * Sets an operation cycle state. This API can only be used through the RTE and therefore
 * no declaration is exported via Dem.h.
 *
 * @param OperationCycleId    Identification of operation cycle, like power cycle, driving cycle.
 * @param CycleState          New operation cycle state: (re-)start or end
 *
 * @return  E_OK: set of operation cycle was successful\n
 *          E_NOT_OK: set of operation cycle failed
 */
Std_ReturnType Dem_SetOperationCycleState(uint8 OperationCycleId, Dem_OperationCycleStateType CycleState);

/** @AR @RTE
 *
 * Dem559: Gets the event memory overflow indication status.
 *
 * @param[in]       DTCOrigin                 If the Dem supports more than one event memory, this parameter is used to select
 *                                            the source memory the DTCs shall be read from.
 * @param[in,out]   OverflowIndication        This parameter returns TRUE if the according event memory was overflowed,
 *                                            otherwise it returns FALSE.
 * @return          E_OK: Operation was successful\n
 *                  E_NOT_OK: Operation failed or is not supported
 */
Std_ReturnType Dem_GetEventMemoryOverflow(Dem_DTCOriginType DTCOrigin, boolean* OverflowIndication);

/** @AR @RTE
 *
 * Returns the number of entries currently stored in the requested event memory.
 *
 * @param [in]   DTCOrigin                      If the Dem supports more than one event memory this parameter is used to select the source memory\n
 *                                              the number of entries shall be read from.
 * @param [out]  NumberOfEventMemoryEntries     Number of entries currently stored in the requested event memory.
 *
 * @return  E_OK: Operation was successful \n
 *          E_NOT_OK: Operation failed
 */
Std_ReturnType Dem_GetNumberOfEventMemoryEntries(Dem_DTCOriginType DTCOrigin, uint8* NumberOfEventMemoryEntries);

/** @AR @RTE
 *
 * Sets the WIR status bit via failsafe SW-Cs.
 *
 * @param [in] EventId      Event Identification of an event by assigned EventId. The Event Number is configured in the DEM.
 * @param [in] WIRStatus    Requested status of event related WIR-bit (regarding to the current status of function inhibition)
 *              WIRStatus = TRUE -> WIR-bit shall be set to "1" WIRStatus = FALSE -> WIR-bit shall be set to "0"
 *
 * @return  E_OK = The request is accepted
 *          E_NOT_OK = The request is accepted E_NOT_OK: not be accepted
 */
Std_ReturnType Dem_SetWIRStatus(Dem_EventIdType EventId, boolean WIRStatus);



/**
 * \defgroup DEM_EVT    Event status information
 * Functions to report or retrieve information about an event
 * @{
 */
/** @AR @RTE
 *
 * Gets the debouncing status of an event. This function shall not be used for EventId with native debouncing within
 * their functions. It is rather for EventIds using debouncing within the Dem.
 *
 * @param [in]   EventId            Identification of an event by assigned EventId.
 * @param [out]  DebouncingState    Bit 0 Temporarily Defective (corresponds to 0 < FDC < 127) \n
 *                                  Bit 1 finally Defective (corresponds to FDC = 127) \n
 *                                  Bit 2 temporarily healed (corresponds to -128 < FDC < 0) \n
 *                                  Bit 3 Test complete (corresponds to FDC = -128 or FDC = 127) \n
 *                                  Bit 4 DTR Update (= Test complete && Debouncing complete && enable conditions / storage conditions fulfilled)
 * @return  E_OK: get of debouncing status per event state successful \n
 *          E_NOT_OK: get of debouncing per event state failed
 */
Std_ReturnType Dem_GetDebouncingOfEvent(Dem_EventIdType EventId, Dem_DebouncingStateType* DebouncingState);


/** @AR @RTE
 *
 * Dem198: Gets the DTC of an event.
 *
 * @param [in]  EventId     Identification of an event by assigned EventId.
 * @param [in]  DTCFormat   Defines the output-format of the requested DTC value.
 * @param [out]  DTCOfEvent  Receives the DTC value returned by the function.
 *                          If the return value of the function is other than E_OK
 *                          this parameter does not contain valid data.
 * @return  E_OK: get of DTC was successful\n
 *          E_NOT_OK: the call was not successful\n
 *          E_NO_DTC_AVAILABLE: there is no DTC
 */
Std_ReturnType Dem_GetDTCOfEvent(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent);


/** @AR @RTE
 *
 * Dem196: Gets the event failed status of an event.
 *
 * @param [in]   EventId          identifier of event
 * @param [out]  EventFailed      TRUE - Last Failed \n
                                 FALSE - not Last Failed
 * @return  E_OK: get of "EventFailed" was successful \n
 *          E_NOT_OK: get of "EventFailed" was not successful
 */
Std_ReturnType Dem_GetEventFailed(Dem_EventIdType EventId, boolean* EventFailed);


/** @AR @RTE
 *
 * Gets the current extended event status of an event.
 *
 * @param [in] EventId Identification of an event by assigned EventId.
 * @param [in,out] EventStatusExtended UDS DTC status byte of the requested event (refer to chapter "Status bit support").
 *                            If the return value of the function call is E_NOT_OK, this parameter does not contain valid data.
 *
 * @return  E_OK = get of event status was successful \n
 *          E_NOT_OK = get of event status failed
 *
 * @see  Dem_SetEventStatus
 */
Std_ReturnType Dem_GetEventStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType* EventStatusExtended);


/** @AR @RTE
 *
 * Dem197: The function Dem_GetEventTested shall read the negated
 * TestNotCompletedThisOperationCycle status of the requested Event.
 *
 * @param [in]   EventId          Identification of Event by ID.
 * @param [out]  EventTested      TRUE, if event is tested in this cycle\n
 *                               FALSE, if event is not tested in this cycle
 * @return  E_OK = Get of event state "tested" was successful \n
 *          E_NOT_OK = Get of event state "tested" failed
 */
Std_ReturnType Dem_GetEventTested(Dem_EventIdType EventId, boolean* EventTested);


/** @AR @RTE
 *
 * Dem181: Gets the fault detection counter of an event.
 *
 * @param [in]  EventId  Identification of an event by assigned EventId.
 * @param [out] FaultDetectionCounter  This parameter receives the Fault Detection
 * Counter information of the requested EventId. If the return value of the function call
 * is other than E_OK this parameter does not contain valid data. -128dec...127dec PASSED... FAILED
 * according to ISO 14229-1

 * @return       E_OK = Operation was successful \n
 *           E_NOT_OK = Operation was not successful
 */
Std_ReturnType Dem_GetFaultDetectionCounter(Dem_EventIdType EventId, sint8* FaultDetectionCounter);


/** @AR @RTE
 *
 * Dem185: Resets the event failed status.
 *
 * @param [in]  EventId          identifier of calling event
 * @return  E_OK = reset of event status was successful \n
 *          E_NOT_OK = reset of event status failed or was not accepted.
 */
Std_ReturnType Dem_ResetEventStatus(Dem_EventIdType EventId);


/** @AR @RTE
 *
 * Dem183: Set the status of an event.
 *
 * @param [in]  EventId          identifier of calling event
 * @param [in]  EventStatus      status of event to be set
 * @return  E_OK = Event Status set was successful \n
 *          E_NOT_OK = Event Status set was not successful
 */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

/**@}*//* End of Doxygen subgroup DEM_EVT */



/**
 * \defgroup DEM_SUP    Dynamic suppression
 * Functions to dynamically suppress certain functionality
 * @{
 */
/** @AR @RTE
 *
 * Gets a storage condition.
 *
 * @param [in]   StorageConditionID            This parameter identifies the storage condition.
 * @param [out]  ConditionFulfilled            This parameter specifies whether the storage condition
 *                                             assigned to the StorageConditionID is fulfilled (TRUE)
 *                                             or not fulfilled (FALSE).
 * @return       E_OK = return value if the DEM_CFG_STORAGECONDITION is ON \n
 *               E_NOT_OK = return value if the DEM_CFG_STORAGECONDITION is OFF
 */
Std_ReturnType Dem_GetStorageCondition(uint8 StorageConditionID, boolean* ConditionFulfilled);


/** @AR @RTE
 *
 * Dem589: Set the suppression status of a specific DTC.
 *
 * @param [in]  DTC  Diagnostic Trouble Code.
 * @param [in]  DTCFormat  Defines the output-format of the requested DTC value.
 * @param [in]  SuppressionStatus  This parameter specifies whether the respective DTC shall be disabled (TRUE) or enabled (FALSE).
 * @return  E_OK: Operation was successful\n
 *          E_NOT_OK: Operation failed or event entry for this DTC still exists
 */
Std_ReturnType Dem_SetDTCSuppression(uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus);


/** @AR @RTE
 *
 * Dem201: Allows activation or deactivation of enableconditions.
 * This function is only available, if enable conditions are configured.
 *
 * @param [in] EnableConditionID   This parameter identifies the enable condition.
 * @param [in] ConditionFulfilled  This parameter specifies whether the enable condition assigned to the
 *                                 EnableConditionID is fulfilled (TRUE) or not fulfilled (FALSE).
 * @return  E_OK = Set of enable condition was successful \n
 *          E_NOT_OK = Set of enable condition was not successful
 */
Std_ReturnType Dem_SetEnableCondition(uint8 EnableConditionID, boolean ConditionFulfilled);

#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
/** @AR @RTE
 *
 * Set the available status of a specific Event.
 *
 * @param [in] EventId: Identification of an event by assigned EventId.
 * @param [in] AvailableStatus: This parameter specifies whether the respective Event shall be available (TRUE) or not (FALSE).
 *
 * @return  E_OK = Operation was successful. \n
 *          E_NOT_OK = Available status of the event could not be set.
 */
    Std_ReturnType Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus);
#endif


/** @AR @RTE
 *
 * Dem556: Sets a storage condition.
 *
 * @param [in]  StorageConditionID  This parameter identifies the storage condition.
 * @param [in]  ConditionFulfilled  This parameter specifies whether the storage condition
 *                                 assigned to the StorageConditionID is fulfilled (TRUE)
 *                                 or not fulfilled (FALSE).
 * @return  In case the storage condition could be set successfully the API call returns E_OK.
 *          If the setting of the storage condition failed the return value of the function is E_NOT_OK.
 */
Std_ReturnType Dem_SetStorageCondition(uint8 StorageConditionID, boolean ConditionFulfilled);

/**@}*//* End of Doxygen subgroup DEM_SUP */



/**
 * \defgroup DEM_EVMEM    Event memory
 * Functions to retrieve or modify data in or related to the event memory
 * @{
 */
/** @AR @RTE
 *
 * Dem193: Clears a prestored freeze frame of a specific event.
 *
 * @param [in]  EventId          Identification of Event by ID.
 * @return  E_OK = Clearing of prestored freezeframe was succssful \n
 *          E_NOT_OK = Clearing of prestored freezeframe was not successful
 */
Std_ReturnType Dem_ClearPrestoredFreezeFrame(Dem_EventIdType EventId);


/** @AR @RTE
 *
 * Gets the data of an extended data record by event.
 *
 * @param [in]   EventId          Identification of an event by assigned EventId.
 * @param [in]   RecordNumber     Identification of requested Extended data record.Valid values are between 0x01 and 0xEF as defined in ISO14229-1.
 * @param [out]  DestBuffer       This parameter contains a byte pointer that points to the buffer, to which the extended \n
 *                                data shall be written to. The format is raw hexadecimal values and contains no header-information.
 * @param [inout]  BufSize        When the function is called this parameter contains the maximum number of data bytes \n
 *                                that can be written to the buffer. The function returns the actual number of written data bytes in this parameter.
 * @return  E_OK: Operation was successful \n
 *          E_NOT_OK: Operation could not be performed
 */
Std_ReturnType Dem_GetEventExtendedDataRecordEx(Dem_EventIdType EventId, uint8 RecordNumber, uint8* DestBuffer, uint16* BufSize);


/** @AR @RTE
 *
 * Gets the data of a freeze frame by event.
 *
 * @param [in]   EventId          Identification of an event by assigned EventId.
 * @param [in]   RecordNumber     This parameter is a unique identifier for a freezeframe record as defined in ISO14229-1. 0xFF\n
 *                                means most recent freeze frame record is returned.0x00 is only supported if the Dem module\n
 *                                supports WWH-OBD (refer to DemOBDSupport)
 * @param [in]   DataId           This parameter specifies the DID (ISO14229-1) that shall be copied to the destination buffer.
 * @param [out]  DestBuffer       This parameter contains a byte pointer that points to the buffer, to which the freeze frame data record\n
 *                                shall be written to. The format is raw hexadecimal values and contains no header-information.
 * @param [inout]  BufSize        When the function is called this parameter contains the maximum number of data bytes that can be written to the buffer.\n
 *                                The function returns the actual number of written data bytes in this parameter.
 * @return  E_OK: Operation was successful \n
 *          E_NOT_OK: Operation could not be performed
 */
Std_ReturnType Dem_GetEventFreezeFrameDataEx(Dem_EventIdType EventId, uint8 RecordNumber, uint16 DataId, uint8* DestBuffer, uint16* BufSize);


/** @AR @RTE
 *
 * Dem188: Captures the freeze frame data for a specific event.
 *
 * @param [in]  EventId          Identification of Event by ID.
 * @return  E_OK = storing of prestored freezeframe was succssful \n
 *          E_NOT_OK = storing of prestored freezeframe was not successful
 */
Std_ReturnType Dem_PrestoreFreezeFrame(Dem_EventIdType EventId);

/** @AR @RTE
 *
 * Stops the debounce counter
 *
 * @param[in]  EventId  Identification of an event by assigned EventId.
 * @param[in]  DebounceResetStatus  This parameter specifies what to to with the debounce counter.
 * Timebased filter may be stopped using FREEZE. In case of using RESET, the counter will be reset additionally.
 * The TestFailed flag is not changed with calling this interface.

 * @return       Always returns E_OK
 */
Std_ReturnType Dem_ResetEventDebounceStatus(Dem_EventIdType EventId, Dem_DebounceResetStatusType DebounceResetStatus);

/**@}*//* End of Doxygen subgroup DEM_EVMEM */

#endif /* DEM_CFG_CHECKAPICONSISTENCY */



/* ---------------------------------------- */
/* C-only API                               */
/* ---------------------------------------- */

/**
 *
 * Switch between different debounce parameter sets.
 *
 * @param [in] CounterParamSetId       Identification of an Paramset.
 *                                     1. User can use the symbolic name as ParamsetId with naming convention DemConf_DemConf_DemRbDebounceCounterSet_xx available in
 *                                        Dem_Cfg_Deb.h, to switch to new paramset.
 *                                     2. Additional if user needs to switch to standard parameters, then DemConf_DemRbDebounceCounterSet_Standard shall be used.
 *
 * @return  E_OK = Switching to new debounce parameter set was successful \n
 *          E_NOT_OK = Switching to new debounce parameter set is not supported
 */
Std_ReturnType Dem_DebSwitchToParameters(uint8 CounterParamSetId);


/**
 *
 * Gets the Fault detection counter of the specified dtcCode.
 *
 * @param[in]  dtcCode - defines the mapping DtcCode from which a DTC Id shall be retrieved.
 * @param[out] FaultDetectionCounter - theFault Detection Counter for the specified dtcCode.
 * @return  E_OK:When valid dtcCode is passed and also when the pointer argument is not a null pointer\n
 *          E_NOT_OK:When either an invalid dtcCode is passed or when the pointer argument is a null pointer
 */
Std_ReturnType Dem_GetDtcFaultDetectionCounter(Dem_DtcCodeType dtcCode, sint8* FaultDetectionCounter);

/**
 * @ingroup DEM_EXT_H
 *
 * Get the available status of a specific Event.
 *
 * @param [in] EventId : Identification of an event by assigned EventId.
 * @param [out] AvailableStatus : This parameter specifies whether the respective Event is available (FALSE) or not (TRUE).
 *
 * @return  E_OK = Operation was successful. \n
 *          E_NOT_OK = Specified EventId is invalid or AvailableStatus is a NULL_PTR.
 */
Std_ReturnType Dem_GetEventAvailable(Dem_EventIdType EventId, boolean* AvailableStatus);

#if (DEM_CFG_ERASE_ALL_DATA_SUPPORTED != DEM_CFG_ERASE_ALL_OFF)
/**
 *
 * Interface to Query the Result of Erase all Data .
 * @param[in]  EraseResult pointer.
 * @return Std_ReturnType (always E_OK)
 */
Std_ReturnType Dem_GetEraseAllNvMDataResult(Dem_EraseAllStatusType* EraseResult);
#endif /* DEM_CFG_ERASE_ALL_DATA_SUPPORTED */


#if (DEM_CFG_VERSION_INFO_API == DEM_CFG_VERSION_INFO_API_ON)
/** @AR
 *
 * Dem177: Returns the version information of this module.
 *
 * @param versioninfo   Pointer to where to store the version information of this module.
 */
void Dem_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif /* DEM_CFG_VERSION_INFO_API */


#if (DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
/**
 *
 * Function to Enable Alternative DtcCode during startup.
 */
void Dem_SwitchToAlternativeDtc(void);
#endif /* DEM_CFG_ALTERNATIVEDTC */


#if(DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED)
/**
 *
 * Dem182: Trigger the storage to NVM for all persistently stored DEM-internal data.
 * @return Always E_OK
 */
Std_ReturnType Dem_TriggerStorageToNvm(void);
#endif


#if (DEM_CFG_DEBTIMEBASED_CONFIGURED_CYCLICTASKTIME) /*configured as seperate cyclic task for Time based Debounce*/
/**
*
* An optional Interface,to be called periodically, if in case reference cyclic task time for Time Based Debounce method
* is chosen other than Dem_MainFunction cyclic time. Ref:- DemRbDebounceTimeBasedTaskTime in DemGeneralRB.
*
* The API is only exported if its configured
*/
void Dem_TimeBasedDebounceMainFunction(void);
#endif /*DEM_CFG_DEBTIMEBASED_CONFIGURED_CYCLICTASKTIME*/



/**
 * \addtogroup DEM_EVT    Event status information
 * Functions to report or retrieve information about an event
 * @{
 */

/**
 *
 * Trigger function to set the history status upon events reporting as failed.
 */
void Dem_AllowHistoryStatus(void);


/**
 *
 * Function to query the Last Reported Event Status
 *
 * @param [in] EventId for which the Last Reported Status is needed
 * @return Dem_EventStatusType returns the Last Reported Status of the event
 */
Dem_EventStatusType Dem_EvtGetLastReportedEventStatus(Dem_EventIdType EventId);


/**
 *
 * Return the DTCKind of a specified event.
 *
 * @param [in] EventId - defines the event for which the DTC kind shall be retrieved
 * @param[out] DtcKind - the DTCKind
 *
 * @return  E_OK = if DTCKind is returned correctly
 * @return  E_NOT_OK = invalid eventId or no DTC assigned
 */
Std_ReturnType Dem_GetDtcKindOfEvent(Dem_EventIdType EventId, Dem_DTCKindType *DtcKind);


/**
 *
 * Return the category of a specified event.
 *
 * @param [in] EventId - defines the event for which the category shall be retrieved
 * @param[out] EventCategory - the category of the event
 *
 * @return E_OK = if category is returned correctly
 * @return E_NOT_OK = invalid eventId or no category assigned
 */
Std_ReturnType Dem_GetEventCategory(Dem_EventIdType EventId, Dem_EventCategoryType *EventCategory);


/**
 *
 * Gets the status whether the event FDC value has reached the FDCThreshold.
 * @param [in]   EventId          identifier of event
 * @param [out]  FdcThresholdReached  TRUE - Event FDC value has reached the FDCThreshold \n
                                      FALSE - Event FDC value not reached the FDCThreshold
 * @return  E_OK: get of "FdcThresholdReached" was successful \n
 *          E_NOT_OK: get of "FdcThresholdReached" was not successful
 */
Std_ReturnType Dem_GetEventFdcThresholdReached(Dem_EventIdType EventId, boolean* FdcThresholdReached);


/**
 *
 * Interface to get the suspicious status of an event.
 * @param [in]   EventId          identifier of an event
 * @param [out]  EventSuspicious  TRUE - Event is suspicious
                                  FALSE - Event is not suspicious
 * @return  E_OK: getting "EventSuspicious" was successful
 *          E_NOT_OK: getting "EventSuspicious" was not successful
 */
Std_ReturnType Dem_GetEventSuspicious(Dem_EventIdType EventId, boolean* EventSuspicious);


/**
 *
 * Interface to get the HistoryStatus
 *
 * @param [in]  EventId for which the HistoryStatus is needed
 * @param [out] HistoryStatus for the specified event
 * @return E_OK: When the pointer argument is not a null pointer
 * @return E_NOT_OK: When the pointer argument is a null pointer
 */
Std_ReturnType Dem_GetHistoryStatus(Dem_EventIdType EventId, boolean *historyStatus);


/**
 *
 * Global good check function: checks if there have been modifications to a global counter,
 * that indicates the necessity of initialising the monitorings again\n
 * You have to pass a buffer for the local copy of the global counter and a paramter that will contain the result of the comparison.
 * The local copy and the global counter are compared.
 * The local copy is updated if necessary.
 *
 * @param [in,out] localCounter pointer to your local copy of the global counter
 * @param [out] modified will contain the result of the comparison\n
 *              TRUE = monitoring should reinitialize\n
 *              FALSE = reinitialization is not necessary
 * @return  E_OK = you can trust the conent of the paramter "modified"
 * @return  E_NOT_OK = invalid pointers have been passed
 */
Std_ReturnType Dem_IsAnyInitMonitorForEventRequested(uint16 *localCounter, boolean *modified);


/**
 *
 * Checks if the diagnostic monitor of a specific event shall be initialized. This interface may be used alternatively to the
 * AR-defined callback mechanism.
 *
 * @param [in] EventId the identifier of the calling event
 * @param [out] InitMonitorReason Specific (re-)initialization reason evaluated from the monitor to identify the initialization kind to be performed.
 * @return  TRUE = Event Status shall be initialized\n
 *          FALSE = No action necessary for monitoring. The return value InitMonitorReason is invalid.
 */
boolean Dem_IsInitMonitorForEventRequested(Dem_EventIdType EventId, Dem_InitMonitorReasonType* InitMonitorReason);


/**
 *
 * Interface to manipulate the dem-internal debouncing
 *
 * @param [in] EventId the identifier of the calling event
 * @param [in] DebugData0 free defineable debug data
 * @param [in] DebugData1 free defineable debug data
 * @param [in] manipulationValue The parameter specifies the value which is to be added to the current debounce level
 *
 * @return  E_OK = Operation was successful
 */
Std_ReturnType Dem_ManipulateEventDebounceStatus(Dem_EventIdType EventId, Dem_DebugDataType debug0, Dem_DebugDataType debug1, sint16 manipulationValue);


/**
*
* Overwrite the WIR (warning indicator) bit of an event's ISO14229 byte.
*
* @param[in]  EventId the event id where the status of the WIR bit shall be overwritten
* @param[in]  WIRStatus  the status that shall be written, TRUE==set, FALSE==reset
* @return Std_ReturnType returns whether the function was executed or not
*/
Std_ReturnType Dem_OverwriteWIRStatus(Dem_EventIdType EventId, boolean WIRStatus);


/** @AR
 *
 * Dem206: Reports errors to the DEM. The api is called by monitoring
 * functions to set the status of BSW errors
 *
 * @param[in]  EventId          Identification of Event by ID.
 * @param[in]  EventStatus      Status of event to be set.
 *
 * Corresponding DIA Functions: Dem_SetEventStatusWithEnvData, FUN_DIA_setDL_V
 */
void Dem_ReportErrorStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);


/**
 *
 * Set the status of BSW errors and additionally allow to specify environmental
 * data, which may be stored to memory within snapshot data.
 *
 * @param [in] EventId        the identifier of the calling event
 * @param [in] EventStatus    status of the calling event
 * @param [in] debug0         free defineable debug data
 * @param [in] debug1         free defineable debug data
 *
 * Corresponding DIA Functions: Dem_SetEventStatusWithEnvData, FUN_DIA_setDL_V
 */
void Dem_ReportErrorStatusWithEnvData( Dem_EventIdType EventId,Dem_EventStatusType EventStatus,Dem_DebugDataType debug0,Dem_DebugDataType debug1);

/**
 *
 * Set the status of an event and additionally allow to specify environmental
 * data, which may be stored to memory within snapshot data.
 *
 * @param [in] EventId        the identifier of the calling event
 * @param [in] EventStatus    status of the calling event
 * @param [in] debug0         free defineable debug data
 * @param [in] debug1         free defineable debug data
 *
 * @return  E_OK = Event Status set was successful \n
 *          E_NOT_OK = Event Status set was not successful
 *
 * @see  Dem_SetEventStatus()
 */
Std_ReturnType Dem_SetEventStatusWithEnvData(Dem_EventIdType EventId,
                                             Dem_EventStatusType EventStatus,
                                             Dem_DebugDataType debug0,
                                             Dem_DebugDataType debug1);


#if(DEM_CFG_SUSPICIOUS_SUPPORT)
/**
 *
 * This function is used by a monitoring to report the failure suspicion state.
 *
 * @param EventId specifies the identifier of the calling monitoring
 * @param suspicion specifies whether to set or reset a failure suspicion. TRUE=set suspicious, FALSE=reset suspicious
 */
void Dem_SetEventSuspicion(Dem_EventIdType EventId, boolean suspicion);
#endif /* DEM_CFG_SUSPICIOUS_SUPPORT */


/**
 *
 * Sets the indicator status for a particular event.
 *
 * @param [in] EventId                 Identification of an event by assigned EventId.
 * @param [in] IndicatorId             Number of indicator
 * @param [in] IndicatorActivation     TRUE/FALSE: set the indicator status according to the configuration
 * @return  E_OK = Set Indicator Status operation was successful \n
 *          E_NOT_OK = Set Indicator Status operation failed or is not supported
 */
Std_ReturnType Dem_SetIndicatorStatusForEvent(Dem_EventIdType EventId, Dem_IndicatorIdType IndicatorId, boolean IndicatorActivation);

/**@}*//* End of Doxygen subgroup DEM_EVT */



/**
 * \addtogroup DEM_SUP    Dynamic suppression
 * Functions to dynamically suppress certain functionality
 * @{
 */

/**
 *
 * Interface to lock the FailureInfo.
 * @return E_OK: FailureInfo is locked.
 * @return E_NOT_OK: FailureInfo is not locked.
*/
Std_ReturnType Dem_LockAllFailureInfo(void);


/**
 *
 * Interface to query whether a Component(Node) is available. A Component may be unavailable due to a variant code configuration or other conditions.
 *
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param [in]   ComponentId           identifier of the component
 * @param [out]  ComponentAvailable    TRUE - The component is available.
 *                                     FALSE - The component is not available.
 * @return  E_OK: getting "ComponentAvailable" was successful
 *          E_NOT_OK: getting "ComponentAvailable" was not successful
 */
Std_ReturnType Dem_GetComponentAvailable(Dem_ComponentIdType ComponentId, boolean* ComponentAvailable);


#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
/** @AR
 *
 * Set the availability of a specific DemComponent.
 *
 * @param[in] ComponentId        Identification of a DemComponent.
 * @param[in] AvailableStatus    This parameter specifies whether the respective Component shall be available (TRUE) or not(FALSE).
 * @return    E_OK               Operation was successful.
 */
Std_ReturnType Dem_SetComponentAvailable(Dem_ComponentIdType ComponentId, boolean AvailableStatus);
#endif /* DEM_CFG_DEPENDENCY */


/**
 * @deprecated Please use Dem_SetEventAvailable() instead
 *
 * Dem_01048: Set the suppression status of a specific Event.
 *
 * @note When OBD Support is enabled in Dem, then it is not possible to set the suppression status of an event that refers to
 * an emission relevant DTC.
 *
 * @param [in] EventId : Identification of an event by assigned EventId
 * @param [in] SuppressionStatus : This parameter specifies whether the respective Event shall be suppressed (TRUE) or not (FALSE).
 *
 * @return  E_OK = Operation was successful.\n
 *          E_NOT_OK = Suppression status of the event could not be set.
 */
Std_ReturnType Dem_SetEventSuppression(Dem_EventIdType EventId, boolean SuppressionStatus);


/**
 *
 * Set the suppression status of all events assigned to a specific DTC.
 *
 * This API is supported only when Event suppression is enabled (i.e. DemGeneral/DemAvailabilitySupport set to
 * DEM_EVENT_AVAILABILITY).
 *
 * Events that have a status bit of TestFailed, Pending, Confirmed or WarningIndicatorRequested set, will not be
 * suppressed (i.e. they are skipped).
 *
 * @param [in]  DTC                Diagnostic Trouble Code.
 * @param [in]  DTCFormat          Defines the output-format of the requested DTC value.(Only UDS format is supported currently)
 * @param [in]  SuppressionStatus  This parameter specifies whether the events associated with the DTC shall be
 *                                 suppressed (TRUE) or not (FALSE)
 *
 * @return  E_OK     = Operation was successful.\n
 *          E_NOT_OK = Event suppression support is disabled or the operation failed due to
 *                     DTCFormat != DEM_DTC_FORMAT_UDS or DTC is invalid or one or more of its
 *                     Events could not be suppressed (e.g. because it has the TestFailed, Pending, Confirmed or WIR
 *                     status bit set). !! CAUTION - it is possible that some events are suppressed and some left
 *                     unsuppressed, if E_NOT OK is returned. To overcome this uncertainty situation, this API may be
 *                     called again with suppression status "FALSE" to make all the events available.
 */
Std_ReturnType Dem_SetEventSuppressionByDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus);

/**@}*//* End of Doxygen subgroup DEM_SUP */



/**
 * \defgroup DEM_EVMEM    Event memory
 * Functions to retrieve or modify data in or related to the event memory
 * @{
 */

/** @AR @RTE
 * @deprecated Please use Dem_GetEventExtendedDataRecordEx() instead.
 *
 * Gets the data of an extended data record by event.
 *
 * @note In CUBAS the C version of this function has already been extended with the BufSize parameter like
 * Dem_GetEventExtendedDataRecordEx(). So they are identical if you don't call it via the RTE.
 *
 * @param [in] EventId       Identification of an event by assigned EventId
 *
 * @param [in]RecordNumber   Identification of requested Extended data record. Valid values are between 0x01 and 0xEF as defined in ISO14229-1.
 *                           0xFF means data of all extended data records are returned.
 *
 * @param [out] DestBuffer   This parameter contains a byte pointer that points to the buffer, to which the extended data shall be
 *                           written to. The format is raw hexadecimal values and contains no header-information.
 *
 * @param [in,out] BufSize   When the function is called this parameter contains the maximum
 *                           number of data bytes that can be written to the buffer.
 *                           The function returns the actual number of written data bytes in this
 *                           parameter.
 *
 * @return                   E_OK = Operation was successful,
 *                           E_NOT_OK = Operation failed.
 */
Std_ReturnType Dem_GetEventExtendedDataRecord(
        Dem_EventIdType EventId,
        uint8 RecordNumber,
        uint8* DestBuffer,
        uint16* BufSize
);


/** @AR @RTE
 * @deprecated Please use Dem_GetEventFreezeFrameDataEx() instead.
 *
 * Gets the data of a freeze frame record by event.
 *
 * @note In CUBAS the C version of this function has already been extended with the BufSize parameter like
 * Dem_GetEventFreezeFrameDataEx(). So they are identical if you don't call it via the RTE.
 *
 * @param [in] EventId             Identification of an event by assigned EventId
 *
 * @param [in] RecordNumber        This parameter is a unique identifier for a freeze frame record as defined in ISO15031-5 and ISO14229-1.
 *                                 0xFF means most recent freeze frame record is returned.
 *
 * @param [in] ReportTotalRecord   This parameter is obsolete and shall be set to FALSE. This function requests a single PID/DID.
 *
 * @param [in] DataId              This parameter specifies the PID (ISO15031-5) or data identifier (ISO14229-1) that shall be copied to the destination buffer.
 *                                 If ReportTotalRecord is TRUE, the value of DataId is ignored.
 *
 * @param [out] DestBuffer         This parameter contains a byte pointer that points to the buffer, to which the freeze frame data shall be
 *                                 written to. The format is raw hexadecimal values and contains no header-information.
 *
 * @param [in,out] BufSize         When the function is called this parameter contains the maximum
 *                                 number of data bytes that can be written to the buffer.
 *                                 The function returns the actual number of written data bytes in this
 *                                 parameter.
 *
 * @return                         E_OK = Operation was successful,
 *                                 E_NOT_OK = Operation failed.
 */
Std_ReturnType Dem_GetEventFreezeFrameData(
        Dem_EventIdType EventId,
        uint8 RecordNumber,
        boolean ReportTotalRecord,
        uint16 DataId,
        uint8* DestBuffer,
        uint16* BufSize
);


/**
 *
 * Interface to get the lock
 *
 * @return TRUE: Event Memory is locked
 * @return FALSE: Event Memory is unlocked
 */
boolean Dem_GetEvMemLock(void);


/**
*
* Read eventids and Location Ids from event memory after read was started with Dem_ReadEventsFromMemory().
* Additional Hint: in concurrently running systems, the eventID returned by this interface may later on already be removed from event memory (e.g. due to displacement or event combination).
* @param[in]   ReadEventsFromMemory     State Read event and event related information from memory
* @param[out]  EventId           The next found eventId is stored in the variable, but only if the return value is DEM_READEVENT_OK.
* @param[out]  LocId             The Location Id to read further event related information [e.g. Occurence Counter]
* @return      Returns, whether reading was successful or no event was found (NO_MATCHING_ELEMENT).
*/
Dem_ReadEventType Dem_GetNextEventFromMemory (Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_EventIdType* EventId, uint16* LocId);


/**
 *
 * Interface to lock the event memory.
 *
 * @param [in] Lock: describes whether the event memory is locked or unlocked
 * @return E_OK: Accessing any of the functions is possible
 * @return E_NOT_OK: Only read and clear functions are accessible. Accessing other functions are not possible since the memory is locked for any insertion of events.
 */
Std_ReturnType Dem_LockEventMemory(boolean Lock);


/**
 *
 * Dem188: Stores a prestored freeze frame of a specific event along with the debug information.
 *
 * @param[in]  EventId          Identification of Event by ID.
 * @param[in]  debug0           First envData information
 * @param[in]  debug1           Second envData inforation
 * @return  E_OK = storing of prestored freezeframe was succssful \n
 *          E_NOT_OK = storing of prestored freezeframe was not successful
 *
 * @see Dem_PrestoreFreezeFrame() is the corresponding AUTOSAR function.
 */
Std_ReturnType Dem_PrestoreFreezeFrameWithEnvData(Dem_EventIdType EventId ,Dem_DebugDataType debug0 ,Dem_DebugDataType debug1);


/**
 *
 * Start reading the eventIds from the event memory.
 *
 * @param[in]  ReadEventsFromMemory  State Read event and event related information from memory
 * @param[in]  origin                Specify the event memory which shall be read (see \ref Dem_DTCOriginType).
 * @return     \ref Dem_ReadEventType : Basically returns, whether a valid origin was requested
 * @see Dem_GetNextEventFromMemory
 */
Dem_ReadEventType Dem_ReadEventsFromMemory(Dem_ReadEventsFromMemoryType* ReadEventsFromMemoryState, Dem_DTCOriginType origin);

/**@}*//* End of Doxygen subgroup DEM_EVMEM */



/**
 * \addtogroup DEM_DISTMEM    Disturbance Memory
 * Functions to retrieve or modify data in or related to the disturbance memory
 * @{
 */

/**
 *
 * Interface to clear events that are stored in disturbance memory.
 *
 * @return  E_OK: Clear disturbance memory was successful\n
 *          E_NOT_OK: Clear disturbance memory was not successful\n
 */
Std_ReturnType Dem_ClearDisturbanceMemory(void);


/**
 *
 * Interface to get the actual data from the disturbance memory.
 *
 * @param [out] EventId the identifier of the calling event
 * @param [out] DestBuffer Parameter contains a byte pointer that points to the buffer
 * @param [in,out] BufSize When the function is called this parameter contains the maximum number of data bytes that can be written to the buffer.
 *                 The function returns the actual number of written data bytes in this parameter.
 *
 *  @return  E_OK: Returned next element\n
 *           E_NOT_OK: no further element found\n
 */
Std_ReturnType Dem_GetNextDisturbanceData(Dem_EventIdType* EventId, uint8* DestBuffer, uint8* BufSize);


/**
 *
 * Interface to lock the disturbance memory.
 *
 * @param [in] Lock: describes whether the disturbance memory is locked or unlocked
 * @return E_OK: Accessing any of the functions is possible
 * @return E_NOT_OK: Only read and clear functions are accessible. Accessing other functions are not possible since the memory is locked for any insertion of events.
 */
Std_ReturnType Dem_LockDisturbanceMemory(boolean Lock);


/**
 *
 * Interface to start reading the disturbance memory.
 *
 * @return  E_OK: Reading the disturbance memory was successful\n
 *          E_NOT_OK: Reading the disturbance memory was not successful\n
 */
Std_ReturnType Dem_ReadDisturbanceMemory(void);

/**@}*//* End of Doxygen subgroup DEM_DISTMEM */



/**
 * \addtogroup DEM_COMP    Component status information
 * Functions to report or retrieve information about a Dem component (dependency graph)
 * @{
 */

/**
 *
 * Interface to query whether Component's(Node's) ancestors(parents) are initialized. At startup Components may not be initialized.
 *
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param [in]   ComponentId                        identifier of the component
 * @param [out]  ComponentAreAncestorsInitialized    TRUE -  All ancestor components are initialized.
 *                                                   FALSE - Any ancestor component is not initialized.
 * @return  E_OK: getting "ComponentAreAncestorsInitialized" was successful
 *          E_NOT_OK: getting "ComponentAreAncestorsInitialized" was not successful
 */
Std_ReturnType Dem_GetComponentAreAncestorsInitialized(Dem_ComponentIdType ComponentId, boolean* ComponentAreAncestorsInitialized);


/** @AR
 *
 * Interface to query whether a Component(Node) is failed. A Component is marked as invalid/failed by monitoring functions.
 *
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param [in]   ComponentId            Identification of a DemComponent
 * @param [out]  ComponentFailed        TRUE - Component is failed
 *                                      FALSE - Component is not failed.
 * @return  E_OK: getting "ComponentFailed" was successful
 *          E_NOT_OK: getting "ComponentFailed" was not successful
 */
Std_ReturnType Dem_GetComponentFailed(Dem_ComponentIdType ComponentId, boolean* ComponentFailed);


/**
 *
 * Interface to query whether a Component(Node) is invalid/failed by itself. That means that monitoring functions at this Component did report failed.
 *
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param [in]   ComponentId              identifier of the component
 * @param [out]  ComponentFailedItself    TRUE - The component itself is failed.
 *                                        FALSE - The component is valid. No event did report failed at the component.
 * @return  E_OK: getting "ComponentFailedItself" was successful
 *          E_NOT_OK: getting "ComponentFailedItself" was not successful
 */
Std_ReturnType Dem_GetComponentFailedItself(Dem_ComponentIdType ComponentId, boolean* ComponentFailedItself);


/**
 *
 * Interface to query whether a Component(Node) is initialized. At startup Components(Nodes) may not be initialized.
 *
 * Don't use this function to query, whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param [in]   ComponentId              identifier of the component
 * @param [out]  ComponentInitialized     TRUE - Component is initialized
 *                                        FALSE - Component is not initialized
 * @return  E_OK: getting "ComponentInitialized" was successful
 *          E_NOT_OK: getting "ComponentInitialized" was not successful
 */
Std_ReturnType Dem_GetComponentInitialized(Dem_ComponentIdType ComponentId, boolean* ComponentInitialized);


/**
 *
 * Interface to query, whether a Component(Node) is restricted usable.
 * The function returns true, if the Component may restrictedly be used (Component is not failed & Component is initialized & Component is available,
 * but Component may be suspicious). If the function returns false, the Component may not be used (i.e. one of the 3 criterias
 * is not met).
 *
 * @param [in]   ComponentId                  identifier of the component
 * @param [out]  ComponentRestrictedUsable    TRUE - Component may restrictedly be used
 *                                            FALSE - Component may not be used
 * @return  E_OK: getting "ComponentRestrictedUsable" was successful
 *          E_NOT_OK: getting "ComponentRestrictedUsable" was not successful
 */
Std_ReturnType Dem_GetComponentRestrictedUsable(Dem_ComponentIdType ComponentId, boolean* ComponentRestrictedUsable);


/**
 *
 * Interface to get the suspicious status of the Component(Node).
 *
 * @param [in]   ComponentId          identifier of the component
 * @param [out]  ComponentSuspicious  TRUE - Component is suspicious
                                      FALSE - Component is not suspicious
 * @return  E_OK: getting "ComponentSuspicious" was successful
 *          E_NOT_OK: getting "ComponentSuspicious" was not successful
 */
Std_ReturnType Dem_GetComponentSuspicious(Dem_ComponentIdType ComponentId, boolean* ComponentSuspicious);


/**
 *
 * Interface to query whether a Component(Node) is suspicious itself. A Component may be marked as suspicious by monitoring functions. If a Component
 * is marked as failed, it isn't marked automatically as suspicious.
 *
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param [in]   ComponentId                  identifier of the component
 * @param [out]  ComponentSuspiciousItself    TRUE - The component is susipicous.
 *                                            FALSE - The component is valid. No event did report susipicous at the component.
 * @return  E_OK: getting "ComponentSuspiciousItself" was successful
 *          E_NOT_OK: getting "ComponentSuspiciousItself" was not successful
 */
Std_ReturnType Dem_GetComponentSuspiciousItself(Dem_ComponentIdType ComponentId, boolean* ComponentSuspiciousItself);


/**
 *
 * Interface to query, whether a Component(Node) is usable.
 * This function returns E_OK, if the Component may be used (Component is not failed & Component is not suspicious & Component is initialized & Component is available).
 * If the function returns E_NOT_OK the Component may not be used (i.e. one of the 4 criterias is not met).
 *
 * @param [in]   ComponentId          identifier of the component
 * @param [out]  ComponentUsable      TRUE - Component is usable
 *                                    FALSE - Component is not usable
 * @return  E_OK: getting "ComponentUsable" was successful
 *          E_NOT_OK: getting "ComponentUsable" was not successful
 */
Std_ReturnType Dem_GetComponentUsable(Dem_ComponentIdType ComponentId, boolean* ComponentUsable);


/**
 *
 * Checks whether a Component (=node) is failed and all failed are filtered
 *
 * If a node is marked as failedfiltered, it also checks, that all failed information is filtered.
 *
 * @param[in] NodeId specifies the id of the node to be checked.
 * @return TRUE : The node is FAILED and all FAILED are filtered by storage condition. \n
 *         FALSE: The node is NOT FAILED or any FAILED is not filtered.
 */
boolean Dem_NodeAreAllFailedFiltered(Dem_ComponentIdType NodeId);


#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

/**
 *
 * Checks whether one of the ancestor(parent) Components (=node) is available.
 * A node may be unavailable due to a variant code configuration or other conditions.
 *
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param[in] NodeId specifies the id of the node to be checked.
 * @return TRUE : All ancestor nodes are available \n
 *         FALSE: Any ancestor node is not available.
 * @see Dem_NodeIsAvailable
 */
boolean Dem_NodeAreAncestorsAvailable(Dem_ComponentIdType NodeId);


/**
 *
 * Checks whether one of a ancestor(parent) Component (=node) is failed.
 *
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param[in] NodeId specifies the id of the node to be checked.
 * @return TRUE : The any ancestor node is failed. \n
 *         FALSE: The node is valid. No event did report failed at an ancestor node.
 * @see Dem_GetComponentFailed()
 */
boolean Dem_NodeAreAncestorsFailed(Dem_ComponentIdType NodeId);


/**
 *
 * The function is defined as interface to query, whether a Component's (=node) parents are restricted usable. The function returns
 * true, if the nodes parents may restrictedly be used (parents are not failed & parents are initialized & parents
 * are available, but parents may be suspicious). If the function returns false, the node's parents may not be used
 * (i.e. one of the 3 criteria is not met).
 *
 * @param[in] NodeId specifies the id of the node to be checked.
 * @return TRUE : All ancestor nodes are restricted usable \n
 *         FALSE: Any ancestor node is not restricted usable.
 * @see Dem_GetComponentRestrictedUsable()
 */
boolean Dem_NodeAreAncestorsRestrictedUsable(Dem_ComponentIdType NodeId);


/**
 *
 * Checks whether one of the ancestor(parent) Component (=node) is suspicious.
 *
 * If a node is marked as failed, it isn't marked automatically as suspicious.
 * Don't use this function to query whether a Component can be used. Use Dem_GetComponentUsable() or Dem_GetComponentRestrictedUsable() instead.
 *
 * @param[in] NodeId specifies the id of the node to be checked.
 * @return TRUE : Any ancestor node is susipicous. \n
 *         FALSE: The node is valid. No event did report susipicous at any ancestor node.

 * @see Dem_GetComponentSuspicious()
 */
boolean Dem_NodeAreAncestorsSuspicious(Dem_ComponentIdType NodeId);


/**
 *
 * The function is defined as interface to query, whether a Component's (=node) parents are usable. The function returns true,
 * if the node parents may be used (parents are not failed & parents are not suspicious & parents are initialized
 * & parents are available). If the function returns false, the node's parents may not be used (i.e. one of the 4 criterias
 * is not met).
 *
 * @param[in] NodeId specifies the id of the node to be checked.
 * @return TRUE : All ancestor nodes are usable \n
 *         FALSE: Any ancestor node is not usable.
 * @see Dem_GetComponentUsable()
 */
boolean Dem_NodeAreAncestorsUsable(Dem_ComponentIdType NodeId);


/**
 *
 * This function returns whether a causal failure is present at a certain Component (=node). It returns
 * TRUE: if a monitoring assigned to this node has reported a causal failure (not preliminary causal).
 * FALSE: if none of the monitoring assigned to this node has reported a causal failure.
 *
 * Hint: For further description of "causal" refer to  function design.
 *
 * @param[in] NodeId specifies the id of the node to be checked.
 */
boolean Dem_NodeHasCausalFault(Dem_ComponentIdType NodeId);

#endif /* DEM_CFG_DEPENDENCY */


/**
 *
 * The function is defined as interface to the node processing. The node processing has to report whether the node/node
 * (system component) is initialized. The default value after power on is "node is initialized". If a node
 * (system component) is marked as not initialized, all depending nodes are also marked as not initialized.
 * The function may be called cyclically, but this is not necessary.
 * To set the status of one node (NodeId), the function has to be called by only one responsible component
 * (node processing of this NodeId).
 *
 * HINT: Be sure what you do before setting node as "not initialized".
 *
 * The minimum time slot between set and reset of the node status is one second.
 *
 * @param[in] NodeId specifies the id of the node/node to be checked.
 * @param[in] init  1 = node/system component is initialized \n
 *                  0 = node/system component is not initialized
 */
void Dem_NodeSetInitialized(Dem_ComponentIdType NodeId, boolean init);

/**@}*//* End of Doxygen subgroup DEM_COMP */



/**
 * \addtogroup DEM_TESTM    Test mode
 * Functions related to the test mode. Only available if DemRbTestModeSupported is set to True.
 * @{
 */

#if (DEM_CFG_TESTMODE_SUPPORT == DEM_CFG_TESTMODE_SUPPORT_ON)
/**
 *
 * Allows activation or de-activation of Test Mode Reporting.
 * If Test Mode reporting is active then Normal reporting will be disabled and vice versa.
 *
 * @param [in] TestModeStatus: Status to Enable (TRUE) or Disable (FALSE) Test Mode reporting
 */
void Dem_EnableTestMode(boolean TestModeStatus);


/**
 *
 * Reports errors to the DEM when Test Mode reporting is active.
 * The api is called by monitoring functions to set the status of BSW errors
 *
 * @param[in]  EventId          Identification of Event by ID.
 * @param[in]  EventStatus      Status of event to be set.
 *
 * Corresponding DIA Functions: Dem_SetEventStatusWithEnvData_TestMode, FUN_DIA_setDL_V
 */
void Dem_ReportErrorStatus_TestMode(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);


/**
 *
 * Set the status of BSW errors and additionally allow to specify environmental
 * data, which may be stored to memory within snapshot data when Test mode reporting is active.
 *
 * @param [in] EventId        the identifier of the calling event
 * @param [in] EventStatus    status of the calling event
 * @param [in] debug0         free defineable debug data
 * @param [in] debug1         free defineable debug data
 *
 * Corresponding DIA Functions: Dem_SetEventStatusWithEnvData_TestMode, FUN_DIA_setDL_V
 */
void Dem_ReportErrorStatusWithEnvData_TestMode(Dem_EventIdType EventId,
                                               Dem_EventStatusType EventStatus,
                                               Dem_DebugDataType debug0,
                                               Dem_DebugDataType debug1);


/**
 *
 * Set the status of an event for Test Mode Reporting.
 * If the Test Mode is active then only the event is set otherwise no action is performed
 *
 * @param [in] EventId the identifier of the calling event
 * @param [in] EventStatus status of the calling event
 *
 * @return  E_OK = Event Status set was successful \n
 *          E_NOT_OK = Event Status set was not successful
 *
 * @see Dem_EnableTestMode()
 */
Std_ReturnType Dem_SetEventStatus_TestMode(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);


/**
 *
 * Set the status of an event and additionally allow to specify environmental
 * data, which may be stored to memory within snapshot data when Test mode reporting is active.
 *
 * @param [in] EventId        the identifier of the calling event
 * @param [in] EventStatus    status of the calling event
 * @param [in] debug0         free defineable debug data
 * @param [in] debug1         free defineable debug data
 *
 * @return  E_OK = Event Status set was successful \n
 *          E_NOT_OK = Event Status set was not successful
 *
 * @see Dem_SetEventStatus_TestMode(), Dem_EnableTestMode()
 */
Std_ReturnType Dem_SetEventStatusWithEnvData_TestMode(Dem_EventIdType EventId,
                                                      Dem_EventStatusType EventStatus,
                                                      Dem_DebugDataType debug0,
                                                      Dem_DebugDataType debug1);

#endif /* DEM_CFG_TESTMODE_SUPPORT */



/**@}*//* End of Doxygen subgroup DEM_TESTM */



#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/**@}*//* End of Doxygen group DEM_H */



/**
 * \defgroup DEM_PRJ_TPL    DEM - Project-specific extension hooks
 * If configured, Dem will call these hooks to realize project-specific behaviour. In the
 * templates directory there are templates that may be adapted to start the implementation.
 */



/**
 * \defgroup DEM_ECUM    DEM - Interface for the ECU State Manager
 *
 * This interface is used by the ECU State Manager to initialise and shutdown the Dem.
 *
 * To use this interface include the header <b>Dem.h</b>
 * @{
 */
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
/**
 *
 * Post-build configuration to select the Alternative Debouncer parameter for CounterClass-Debouncer.
 */
extern const Dem_ConfigType Dem_ConfigAlternativeParameters;
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/** @AR
 *
 * Dem181: Initializes or reinitializes this module.
 * @see  Dem_Shutdown
 */
void Dem_Init(void);


/** @AR
 *
 * Dem179: Initializes the internal states necessary to process events reported by BSW-modules.
 * @param[in]  ConfigPtr
 */
void Dem_PreInit(const Dem_ConfigType* ConfigPtr);


/** @AR
 *
 * Dem182: Shuts down this module.
 * @see  Dem_Init
 */
void Dem_Shutdown(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/**@}*//* End of Doxygen group DEM_ECUM */



#endif /* DEM_H */
