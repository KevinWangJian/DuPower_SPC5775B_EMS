

#ifndef DEM_J1939DCM_H
#define DEM_J1939DCM_H


#include "Dem_Types.h"

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)
/**
 * \defgroup DEM_J1939DCM    DEM - Interface for the J1939Dcm
 *
 * This interface may only be used by the J1939Dcm. Use by other components is prohibited because some of the functions
 * operate on global state and therefore need to be called in a defined order without interference.
 *
 * To use this interface include the header <b>Dem_J1939Dcm.h</b>
 * @{
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/**
 * \defgroup DEM_J1939DCM_DTC    Access DTCs and Status Information
 * @{
 */

/**
 *
 * The function sets the DTC filter for a specific node and returns the composite lamp status of the filtered DTCs.
 *
 * @param[in]   DTCStatusFilter  The following types are available:\n
 *                               DEM_J1939DTC_ACTIVE\n
 *                               DEM_J1939DTC_PREVIOUSLY_ACTIVE\n
 *                               DEM_J1939DTC_PENDING\n
 *                               DEM_J1939DTC_PERMANENT\n
 *                               DEM_J1939DTC_CURRENTLY_ACTIVE
 * @param[in]   DTCKind          Defines the functional group of DTCs to be reported (e.g. all DTC, OBD-relevant DTC)
 * @param[in]   node             Nm node Id
 * @param[out]  LampStatus       Receives the commulated lamp status.
 * @return  Status of the operation to (re-)set a DTC filter.
 */
Dem_ReturnSetFilterType Dem_J1939DcmSetDTCFilter(Dem_J1939DcmDTCStatusFilterType DTCStatusFilter,
                                                 Dem_DTCKindType DTCKind,
                                                 uint8 node,
                                                 Dem_J1939DcmLampStatusType* LampStatus);


/**
 *
 * The function gets the number of currently filtered DTCs set by the function Dem_J1939DcmSetDTCFilter.
 *
 * @param[out]  NumberOfFilteredDTC       The number of DTCs matching the defined status mask.
 * @return  Status of the operation to retrieve a number of DTC from the Dem.
 */
Dem_ReturnGetNumberOfFilteredDTCType Dem_J1939DcmGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC);


/**
 *
 * Gets the next filtered J1939 DTC.
 *
 * @param[out]   J1939DTC            Receives the J1939DTC value. If the return value of the function is other than DEM_FILTERED_OK this
 *                                  parameter does not contain valid data.
 * @param[out]  OccurenceCounter    This parameter receives the corresponding occurrence counter.
 *                                  If the return value of the function call is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @return  Status of the operation to retrieve a DTC from the Dem.
 */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFilteredDTC(uint32* J1939DTC, uint8* OccurenceCounter);


/**
 *
 * The function sets the filter to the first applicable DTC for the DM31 response for a specific node.
 *
 * @param[in] node                Nm node Id of requesting client
 */
void Dem_J1939DcmFirstDTCwithLampStatus(uint8 node);


/**
 *
 * Gets the next filtered J1939 DTC for DM31 including current LampStatus.
 *
 * @param[out]  LampStatus          Receives the lamp status returned by this function. If the return value of the function
 *                                  is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @param[out]  J1939DTC            Receives the J1939DTC value. If the return value of the function is other than DEM_FILTERED_OK this
 *                                  parameter does not contain valid data.
 * @param[out]  OccurenceCounter    This parameter receives the corresponding occurrence counter.
 *                                  If the return value of the function call is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @return  Status of the operation to retrieve a DTC from the Dem.
 */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextDTCwithLampStatus(Dem_J1939DcmLampStatusType* LampStatus,
                                                                          uint32* J1939DTC,
                                                                          uint8* OccurenceCounter);

/**@}*//* End of Doxygen subgroup DEM_J1939DCM_DTC */



/**
 * \defgroup DEM_J1939DCM_STORAGE    DTC storage
 * @{
 */

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
/**
 *
 * Clears active DTCs as well as previously active DTCs.
 *
 * @param[in]   DTCTypeFilter       The following types are available:\n
 *                                  DEM_J1939DTC_CLEAR_ALL\n
 *                                  DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE
 * @param[in]   node                Nm node Id
 * @return  Status of the operation of type Dem_Return-ClearDTCType.
 */
Dem_ReturnClearDTCType Dem_J1939DcmClearDTC(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node);
#endif /* DEM_CFG_J1939DCM_CLEAR_SUPPORT */


/**
 *
 * The function sets the FreezeFrame filter for a specific node.
 *
 * @param[in] FreezeFrameKind     The following types are available:\n
 *                                DEM_J1939DCM_FREEZEFRAME\n
 *                                DEM_J1939DCM_EXPANDED_FREEZEFRAME\n
 *                                DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME
 * @param[in] node                Nm node Id
 * @return  Status of the operation to (re-)set a FreezeFrame filter.
 */
Dem_ReturnSetFilterType Dem_J1939DcmSetFreezeFrameFilter(Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind, uint8 node);


/**
 *
 * Gets next freeze frame data. The function stores the data in the provided DestBuffer.
 *
 * @param[in,out]  DestBuffer       This parameter contains a byte pointer that points to the buffer, to which the freeze frame data record shall be written to.
 * @param[in,out]  BufSize          When the function is called this parameter contains the maximum number of data bytes that can be written
                                    to the buffer.The function returns the actual number of written data bytes in DestBuffer.
 * @param[out]    J1939DTC          Receives the J1939DTC value. If the return value of the function is other than DEM_FILTERED_OK this
 *                                  parameter does not contain valid data.
 * @param[out]    OccurenceCounter  This parameter receives the corresponding occurrence counter.
 *                                  If the return value of the function call is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @return  Status of the operation to retrieve freeze frame data by DTC.
 */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFreezeFrame(uint32* J1939DTC,
                                                                    uint8* OccurenceCounter,
                                                                    uint8* DestBuffer,
                                                                    uint16* BufSize);


/**
 *
 * Gets next SPN.
 *
 * @param[out]    SPNSupported   This parameter contains the next SPN in the ExpandedFreezeFrame.
 * @param[out]    SPNDataLength  This parameter contains the corresponding dataLength of the SPN.
 * @return  Status of the operation to retrieve freeze frame data by DTC.
 */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextSPNInFreezeFrame(uint32* SPNSupported, uint8* SPNDataLength);

/**@}*//* End of Doxygen subgroup DEM_J1939DCM_STORAGE */



#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)
/**
 * \defgroup DEM_J1939DCM_REPORT    Reporting
 * @{
 */

/**
 *
 * The function sets the Ratio filter for a specific node and returns the corresponding Ignition Cycle Counter and General Denominator.
 *
 * @param[in] node                                  Nm node Id of requesting client
 * @param[out] IgnitionCycleCounter                 Ignition Cycle Counter.
 * @param[out] OBDMonitoringConditionsEncountered   OBD Monitoring Conditions Encountered.
 * @return    Status of the operation to (re-)set a DTC filter.
 */
Dem_ReturnSetFilterType Dem_J1939DcmSetRatioFilter(uint16* IgnitionCycleCounter,
                                                   uint16* OBDMonitoringConditionsEncountered,
                                                   uint8 node);


/**
 *
 * Gets the next filtered Ratio.
 *
 * @param[out] SPN              Receives the SPN of the applicaple system monitor.
 *                              If the return value of the function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @param[out] Numerator        Receives the Numerator of the applicable system monitor.
 *                              If the return value of the function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @param[out] Denominator      Receives the Denominator of the applicable system monitor.
 *                              If the return value of the function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @return    0x00 DEM_FILTERED_OK Ratio available in out parameter.
              0x01 DEM_FILTERED_NO_FURTHER ELEMENT No further element available.
 */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFilteredRatio(uint16* SPN,
                                                                      uint16* Numerator,
                                                                      uint16* Denominator);


/**
 *
 * Service to report the value of Diagnostic Readiness 1 (DM05) computed by the Dem.
 *
 * @param[in] node           Nm node Id of requesting client.
 * @param[out] DataValue     Buffer of 8 bytes containing the contents of Diagnostic Readiness 1 (DM05) computed by the Dem.
 * @return                   E_OK: Operation was successful.
 *                           E_NOT_OK: Operation failed.
 */
Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness1(Dem_J1939DcmDiagnosticReadiness1Type* DataValue, uint8 node);


/**
 *
 * Service to report the value of Diagnostic Readiness 2 (DM21) computed by the Dem.
 *
 * @param[in] node           Nm node Id of requesting client.
 * @param[out] DataValue     Buffer of 8 bytes containing the contents of Diagnostic Readiness 2 (DM21) computed by the Dem.
 * @return                   E_OK: Operation was successful.
 *                           E_NOT_OK: Operation failed.
 */
Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness2(Dem_J1939DcmDiagnosticReadiness2Type* DataValue, uint8 node);


/**
 *
 * Service to report the value of Diagnostic Readiness 3 (DM26) computed by the Dem.
 *
 * @param[in] node           Nm node Id of requesting client.
 * @param[out] DataValue     Buffer of 8 bytes containing the contents of Diagnostic Readiness 3 (DM26) computed by the Dem.
 * @return                   E_OK: Operation was successful.
 *                           E_NOT_OK: Operation failed.
 */
Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness3(Dem_J1939DcmDiagnosticReadiness3Type* DataValue, uint8 node);

/**@}*//* End of Doxygen subgroup DEM_J1939DCM_REPORT */
#endif /* DEM_CFG_OBD */


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/**@}*//* End of Doxygen group DEM_J1939DCM */
#endif  /* DEM_CFG_J1939DCM */

#endif /* DEM_J1939DCM_H */
