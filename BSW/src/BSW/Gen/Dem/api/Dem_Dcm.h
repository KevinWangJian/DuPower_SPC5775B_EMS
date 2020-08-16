

#ifndef DEM_DCM_H
#define DEM_DCM_H


#include "Dem_Types.h"
#include "Dcm_Types.h"

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
#include "rba_DemObdBasic_Dcm.h"
#endif

/**
 * \defgroup DEM_DCM    DEM - Interface for the Dcm
 *
 * This interface may only be used by the Dcm. Use by other components is prohibited because some of the functions
 * operate on global state and therefore need to be called in a defined order without interference.
 *
 * To use this interface include the header <b>Dem_Dcm.h</b>
 * @{
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/**
 * \defgroup DEM_DCM_DTC    Access DTCs and Status Information
 * @{
 */

/**
 *
 * Dem230: Gets the supported DTC formats of the ECU. The supported formats
 *         are configured via DemTypeOfDTCSupported.
 * @return Returns the configured DTC translation format. A combination of
 *         different DTC formats is not possible.
 *
 * @note  The only supported DTC translation format is currently ISO14229-1
 */
Dem_DTCTranslationFormatType Dem_GetTranslationType(void);


/**
 *
 * Dem213: Gets the DTC Status availability mask.
 *
 * @param[out]  DTCStatusMask   The value DTCStatusMask indicates the supported DTC
 *                              status bits from the Dem. All supported information
 *                              is indicated by setting the corresponding status bit
 *                              to 1. See ISO14229-1.
 * @return  E_OK: get of DTC status mask was successful\n
 *          E_NOT_OK: get of DTC status mask failed
 */
Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8* DTCStatusMask);


/**
 *
 * Dem198: Gets the DTC of an event.
 *
 * @param[in]  DTC  For this DTC its status is requested
 * @param[in]  DTCKind  This parameter defines the requested DTC, either only
 *                      OBD-relevant DTCs or all DTCs
 * @param[in]  DTCOrigin  If the Dem supports more than one event memory this parameter
 *                        is used to select the source memory the DTCs shall be read from.
 * @param[out]  DTCStatus  This parameter receives the status information of the requested
 *                         DTC. If the return value of the function call is other than
 *                         DEM_STATUS_OK this parameter does not contain valid data.
 *                         0x00...0xFF match DTCStatusMask as defined in ISO14229-1.
 * @return  Status of the operation of type Dem_ReturnGetStatusOfDTCType.\n
 */
Dem_ReturnGetStatusOfDTCType Dem_GetStatusOfDTC(uint32 DTC, Dem_DTCKindType DTCKind, Dem_DTCOriginType DTCOrigin, uint8* DTCStatus);


/**
 *
 * Dem232: Gets the severity of the requested DTC.
 *
 * @param[in]  DTC  The Severity assigned to this DTC should be returned.
 * @param[out]  DTCSeverity  This parameter contains the DTCSeverityMask according to ISO14229-1.
 * @return  Status of the operation of type Dem_ReturnGetSeverityOfDTCType.
 */
Dem_ReturnGetSeverityOfDTCType Dem_GetSeverityOfDTC(uint32 DTC, Dem_DTCSeverityType* DTCSeverity);


/**
 *
 * Dem594: Gets the functional unit of the requested DTC.
 *
 * @param[in]  DTC  Diagnostic Trouble Code.
 * @param[out]  DTCFunctionalUnit  Functional unit value of this DTC.
 * @return  Status of the operation of type Dem_ReturnGetFunctionalUnitOfDTCType.
 */
Dem_ReturnGetFunctionalUnitOfDTCType Dem_GetFunctionalUnitOfDTC(uint32 DTC, uint8* DTCFunctionalUnit);


/**
 *
 * Dem208: The function Dem_SetDTCFilter (refer to chapter 8.3.4.1.1) shall set the filter mask
 *         attributes to be used for the sub-sequent calls of Dem_GetNumberOfFilteredDTC(),
 *         Dem_GetNextFilteredDTC(), Dem_GetNextFilteredDTCAndFDC(), as well as
 *         Dem_GetNextFilteredDTCAndSeverity().
 *
 * @param[in]  DTCStatusMask  According ISO14229-1 StatusOfDTC Values:\n
 *                            0x00: Report all supported DTCs\n
 *                            0x01...0xFF: Match DTCStatusMask as defined in ISO14229-1
 * @param[in]  DTCKind  Defines the functional group of DTCs to be reported
 *                      (e.g. all DTC, OBD-relevant DTC)
 * @param[in]  DTCFormat  Defines the output-format of the requested DTC values for the sub-sequent API calls.
 * @param[in]  DTCOrigin  If the Dem supports more than one event memory this parameter
 *                        is used to select the source memory the DTCs shall be read from.
 * @param[in]  FilterWithSeverity  This flag defines whether severity information (ref. to
 *                                 parameter below) shall be used for filtering. This is to
 *                                 allow for coexistence of DTCs with and without severity information.
 * @param[in]  DTCSeverityMask  This parameter contains the DTCSeverityMask according to ISO14229-1
 *                              (see for example Service 0x19, subfunction 0x08)
 * @param[in]  FilterForFaultDetectionCounter  This flag defines whether the fault detection counter
 *                                             information shall be used for filtering. This is to
 *                                             allow for coexistence of DTCs with and without fault
 *                                             detection counter information. If fault detection counter
 *                                             information is filter criteria, only those DTCs with a
 *                                             fault detection counter value between 1 and 0x7E shall
 *                                             be reported. Remark: If the event does not use the
 *                                             debouncing inside Dem, then the Dem must request this
 *                                             information via GetFaultDetectionCounter.
 * @return  Status of the operation to (re-)set a DTC filter.
 */
Dem_ReturnSetFilterType Dem_SetDTCFilter(uint8 DTCStatusMask,
                                         Dem_DTCKindType DTCKind,
                                         Dem_DTCFormatType DTCFormat,
                                         Dem_DTCOriginType DTCOrigin,
                                         Dem_FilterWithSeverityType FilterWithSeverity,
                                         Dem_DTCSeverityType DTCSeverityMask,
                                         Dem_FilterForFDCType FilterForFaultDetectionCounter);


/**
 *
 * Dem214: Gets the number of a filtered DTC.
 *
 * @param[out]  NumberOfFilteredDTC  The number of DTCs matching the defined status mask.
 * @return  Status of the operation to retrieve a number of DTC from the Dem.
 * @see Dem_SetDTCFilter()
 */
Dem_ReturnGetNumberOfFilteredDTCType Dem_GetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC);


/**
 *
 * Dem215: Gets the next filtered DTC.
 *
 * @param[out]  DTC  Receives the DTC value returned by the function. If the return value of the
 *                   function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @param[out]  DTCStatus  This parameter receives the status information of the requested DTC. It
 *                         follows the format as defined in ISO14229-1 If the return value of the function
 *                         call is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @return  Status of the operation to retrieve a DTC from the Dem.
 * @see Dem_SetDTCFilter()
 */
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTC(uint32* DTC, uint8* DTCStatus);


/**
 *
 * Dem227: Gets the current DTC and its associated Fault Detection Counter (FDC) from the Dem. The interface has an
 *         asynchronous behavior, because the FDC might be received asynchronously from a SW-C, too.
 *
 * @param[out]  DTC : Receives the DTC value returned by the function. If the return value of the function is
 *                    other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @param[out]  DTCFaultDetectionCounter : This parameter receives the Fault Detection Counter information of the
 *                    requested DTC. If the return value of the function call is other than DEM_FILTERED_OK this
 *                    parameter does not contain valid data.
 * @return  Dem_ReturnGetNextFilteredDTCType : Status of the operation to retrieve a DTC from the Dem.
 * @see Dem_SetDTCFilter()
 */
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTCAndFDC(uint32* DTC, sint8* DTCFaultDetectionCounter);


/**
 *
 * Dem281: Gets the current DTC and its Severity from the Dem.
 *
 * @param[out]  DTC  Receives the DTC value returned by the function. If the return value of the function
 *                   is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @param[out]  DTCStatus  Receives the status value returned by the function. If the return value
 *                         of the function is other than DEM_FILTERED_OK this parameter does not
 *                         contain valid data.
 * @param[out]  Dem_DTCSeverityType  Receives the severity value returned by the function. If the
 *                                   return value of the function is other than DEM_FILTERED_OK this
 *                                   parameter does not contain valid data.
 * @param[out]  DTCFunctionalUnit  Receives the functional unit value returned by the function. If
 *                                 the return value of the function is other than DEM_FILTERED_OK
 *                                 this parameter does not contain valid data.
 * @return  Status of the operation to retrieve a DTC from the Dem.
 * @see Dem_SetDTCFilter()
 */
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredDTCAndSeverity(uint32* DTC,
                                                                   uint8* DTCStatus,
                                                                   Dem_DTCSeverityType* DTCSeverity,
                                                                   uint8* DTCFunctionalUnit);


/**
 *
 * Dem209: Sets a freeze frame record filter.
 *
 * @param[in]  DTCFormat  Defines the output-format of the requested DTC values for the sub-sequent API calls.
 * @param[out] NumberOfFilteredRecords Number of freeze frame records currently stored in the event memory.
 * @return     Dem_ReturnSetFilterType: Status of the operation to (re-)set a freeze frame record filter
 *
 * @note
 * DEM supports only DTCKind 'DEM_DTC_KIND_ALL_DTCS'.\n
 * In case of PENDING the caller needs to repeat the service with identical parameters.\n
 * This service is only allowed if the DCM task and the DEM task do not preempt each other
 */
Dem_ReturnSetFilterType Dem_SetFreezeFrameRecordFilter(Dem_DTCFormatType DTCFormat, uint16* NumberOfFilteredRecords);


/**
 *
 * Dem215: Gets the current DTC and its associated snapshot record numbers from the Dem.
 *
 * @param[out]  DTC              Receives the DTC value returned by the function.
 *                                If the return value of the function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @param[out]  RecordNumber        Freeze frame record number of the reported DTC (relative addressing).
 *                                If the return value of the function is other than DEM_FILTERED_OK this parameter does not contain valid data.
 * @return      Dem_ReturnGetNextFilteredDTCType: Status of the operation to retrieve the next filtered DTC and freeze frame record number
 *
 * @note
 * DEM supports only DTCKind 'DEM_DTC_KIND_ALL_DTCS'.\n
 * In case of PENDING the caller needs to repeat the service with identical parameters.\n
 * This service is only allowed if the DCM task and the DEM task do not preempt each other
 */
Dem_ReturnGetNextFilteredDTCType Dem_GetNextFilteredRecord(uint32* DTC, uint8* RecordNumber);


#if (DEM_CFG_EVMEMGENERIC_SUPPORTED != FALSE)
/**
 *
 * Dem218: Gets the DTC by occurrence time. There is no explicit parameter for the DTC-origin as the origin always is DEM_DTC_ORIGIN_PRIMARY_MEMORY.
 *
 * @param[in]     DTCRequest     This parameter defines the request type of the DTC.
 * @param[in]     DTCKind        This parameter defines the requested DTC. (only all DTCs is supported)
 * @param[out]    DTC            Receives the DTC value returned by the function.
 *                               If the return value of the function is other than DEM_OCCURR_OK this parameter does not contain valid data.
 * @return        Status of the operation of type Dem_ReturnGetDTCByOccurrenceTimeType.
 */
Dem_ReturnGetDTCByOccurrenceTimeType Dem_GetDTCByOccurrenceTime(Dem_DTCRequestType DTCRequest, Dem_DTCKindType DTCKind, uint32* DTC);
#endif /* DEM_CFG_EVMEMGENERIC_SUPPORTED */

/**@}*//* End of Doxygen subgroup DEM_DCM_DTC */



/**
 * \defgroup DEM_DCM_EVMEM    Access extended data records and FreezeFrame data
 * @{
 */

/**
 *
 * Dem233: Disables the event memory update of a specific DTC (only one at one time).
 *
 * @param[in]   DTC             Selects the DTC in UDS format, for which DTC record update shall be disabled.
 * @param[in]   DTCOrigin       If the Dem supports more than one event memory, this parameter is used to select the source memory for which DTC record update shall be disabled.
 * @return      Dem_ReturnDisableDTCRecordUpdateType: Status of the operation to disable the event memory update of a specific DTC\n
 *
 * @note
 * DEM is not locking any DTC record.\n
 * Parameters of this function are not used or checked.\n
 * Instead a copy of the DTC record is taken for further processing on when calling API functions like Dem_GetFreezeFrameDataByDTC!
 */
Dem_ReturnDisableDTCRecordUpdateType Dem_DisableDTCRecordUpdate(uint32 DTC, Dem_DTCOriginType DTCOrigin);


/**
 *
 * Dem234: Enables the DTC record update
 *
 * @return       E_OK = Operation was successfull \n
 *               E_NOT_OK = Operation failed
 */
Std_ReturnType Dem_EnableDTCRecordUpdate(void);


/**
 *
 * Dem236: Gets freeze frame data by DTC. The function stores the data in the provided DestBuffer
 *
 * @param[in]       DTC             This is the DTC the freeze frame is assigned to.
 * @param[in]       DTCKind         This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs.
 * @param[in]       DTCOrigin       If the Dem supports more than one event memory, this parameter is used to select.
 *                               the source memory the DTCs shall be read from.
 * @param[in]       RecordNumber    This parameter is a unique identifier for a freeze frame record as defined in ISO 15031-5 and ISO 14229-1.
 *                               This record number is unique per DTC (relative addressing)
 *                               The value 0xFF is not allowed. The value 0x00 indicates the DTC-specific OBD freeze frame.\n
 * @param[out]      DestBuffer      This parameter contains a byte pointer that points to the buffer, to which the freeze frame data record shall be written to.\n
 *                               The format is: {RecordNumber, NumOfDIDs, DID[1], data[1], ..., DID[N], data[N]}
 * @param[in,out] BufSize           When the function is called this parameter contains the maximum number of data bytes that can be written to the buffer.\n
 *                               The function returns the actual number of written data bytes in this parameter
 * @return        Dem_ReturnGetFreezeFrameDataByDTCType: Status of the operation to retrieve freeze frame data by DTC
 *
 * @note
 * DEM supports only DTCKind 'DEM_DTC_KIND_ALL_DTCS'.\n
 * In case of PENDING the caller needs to repeat the service with identical parameters.
 *
 * Reading Freeze Frames is done by creating a copy of the event memory.Hence Dem_DisableDTCRecordUpdate must be called
 * before Dem_GetFreezeFrameDataByDTC is used to query stored Freeze Frames.Calling Dem_EnableDTCRecordUpdate frees
 * the event memory copy finally.
 */

Dem_ReturnGetFreezeFrameDataByDTCType Dem_GetFreezeFrameDataByDTC(uint32            DTC,
                                                                  Dem_DTCKindType   DTCKind,
                                                                  Dem_DTCOriginType DTCOrigin,
                                                                  uint8             RecordNumber,
                                                                  uint8*            DestBuffer,
                                                                  uint16*           BufSize
                                                                  );


/**
 *
 * Dem238: Gets the size of freeze frame data by DTC.
 *
 * @param[in]   DTC                 This is the DTC the freeze frame is assigned to.
 * @param[in]   DTCKind             This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 * @param[in]   DTCOrigin           If the Dem supports more than one event memory, this parameter is used to select
 *                                  the source memory the DTCs shall be read from.
 * @param[in]   RecordNumber        This parameter is a unique identifier for a freeze frame record as defined in ISO 15031-5 and ISO 14229-1.\n
 *                                  This record number is unique per DTC (relative addressing).\n
 *                                  The value 0xFF is explicitly allowed to request the overall size.
 * @param[out]  SizeOfFreezeFrame   Number of bytes in the requested freeze frame record.
 * @return      Dem_ReturnGetSizeOfFreezeFrameByDTCType: Status of the operation to retrieve the size of freeze frame data.
 *
 * @note
 * DEM supports only DTCKind 'DEM_DTC_KIND_ALL_DTCS'.\n
 * In case of PENDING the caller needs to repeat the service with identical parameters.
 */
Dem_ReturnGetSizeOfFreezeFrameByDTCType Dem_GetSizeOfFreezeFrameByDTC(uint32              DTC,
                                                                      Dem_DTCKindType     DTCKind,
                                                                      Dem_DTCOriginType   DTCOrigin,
                                                                      uint8               RecordNumber,
                                                                      uint16*             SizeOfFreezeFrame
                                                                      );


/**
 *
 * Dem239: Gets extended data by DTC. The function stores the data in the provided DestBuffer.
 *
 * @param[in]       DTC                    This is the DTC the 'Extended Data Record' is assigned to.
 * @param[in]   DTCKind                This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs.
 * @param[in]       DTCOrigin              If the Dem supports more than one event memory, this parameter is used to select
 *                                     the source memory the DTCs shall be read from.
 * @param[in]       ExtendedDataNumber  Identification/Number of requested extended data record.
 *                                     The values 0xFE and 0xFF are not allowed. Valid values are from 0x01 to 0xEF.
 * @param[out]      DestBuffer             This parameter contains a byte pointer that points to the buffer, to which the extended data record shall be written.\n
 *                                     The format is raw hexadecimal values and contains no header-information.
 * @param[in,out]   BufSize                When the function is called this parameter contains the maximum number of data bytes that can be written to the buffer.\n
 *                                     The function returns the actual number of written data bytes in this parameter.
 * @return      Dem_ReturnGetExtendedDataRecordByDTCType : Status of the operation to retrieve extended data by DTC
 *
 * @note
 * DEM supports only DTCKind 'DEM_DTC_KIND_ALL_DTCS'.\n
 * In case of PENDING the caller needs to repeat the service with identical parameters.
 *
 * Reading Extended Data is done by creating a copy of the event memory. Hence Dem_DisableDTCRecordUpdate must be called
 * before Dem_GetExtendedDataRecordByDTC is used to query stored Extended Data Records. Calling Dem_EnableDTCRecordUpdate
 * frees the event memory copy finally.
 */
Dem_ReturnGetExtendedDataRecordByDTCType Dem_GetExtendedDataRecordByDTC(uint32              DTC,
                                                                        Dem_DTCKindType     DTCKind,
                                                                        Dem_DTCOriginType   DTCOrigin,
                                                                        uint8               ExtendedDataNumber,
                                                                        uint8*              DestBuffer,
                                                                        uint16*             BufSize
                                                                        );


/**
 *
 * Dem240: Gets the size of extended data by DTC.
 *
 * @param[in]   DTC                            This is the DTC the 'Extended Data Record' is assigned to.
 * @param[in]   DTCKind                        This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 * @param[in]   DTCOrigin                      If the Dem supports more than one event memory, this parameter is used to select
 *                                        the source memory the DTCs shall be read from.
 * @param[in]   ExtendedDataNumber          Identification/Number of requested extended data record. Valid values are from 0x01 to 0xEF.
 * @param[out]  SizeOfExtendedDataRecord    Pointer to Size of the requested data record.
 * @return      Dem_ReturnGetSizeOfExtendedDataRecordByDTCType : Status of the operation to retrieve the size of extended data.
 *
 * @note
 * DEM supports only DTCKind 'DEM_DTC_KIND_ALL_DTCS'.\n
 * In case of PENDING the caller needs to repeat the service with identical parameters.
 */
Dem_ReturnGetSizeOfExtendedDataRecordByDTCType Dem_GetSizeOfExtendedDataRecordByDTC(uint32             DTC,
                                                                                    Dem_DTCKindType    DTCKind,
                                                                                    Dem_DTCOriginType  DTCOrigin,
                                                                                    uint8              ExtendedDataNumber,
                                                                                    uint16*            SizeOfExtendedDataRecord
                                                                                    );

/**@}*//* End of Doxygen subgroup DEM_DCM_EVMEM */



/**
 * \defgroup DEM_DCM_STORAGE    DTC storage
 * @{
 */

/**
 *
 * Clears single DTCs as well as groups of DTCs.
 *
 * @param DTC           Defines the DTC in respective format, that shall be cleared from the event memory.
 *                      If the DTC fits to a DTC group number, all DTCs of the group shall be cleared.
 * @param DTCFormat     Defines the input-format of the provided DTC value.
 * @param DTCOrigin     If the Dem supports more than one event memory this parameter is used to select
 *                      the source memory the DTCs shall be read from.
 *
 * @return  Dem_ReturnClearDTCType: Returns the result of the parameter check when performing a clear command with same parameters (refer to Dem_DcmClearDTC).
 *          Only the following return values will be used:\n
 *          - DEM_CLEAR_OK - DTC successfully  cleared
 *          - DEM_CLEAR_WRONG_DTC - DTC value not existing (in this format)
 *          - DEM_CLEAR_WRONG_DTCORIGIN - Wrong DTC origin
 *          - DEM_CLEAR_FAILED - In case of general errors with clear parameters
 */
Dem_ReturnClearDTCType Dem_DcmCheckClearParameter(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);


#if (DEM_CFG_CHECKAPICONSISTENCY == TRUE)
/**
 *
 * Clears single DTCs as well as groups of DTCs.
 *
 * @param DTC           Defines the DTC in respective format, that shall be cleared from the event memory.
 *                      If the DTC fits to a DTC group number, all DTCs of the group shall be cleared.
 * @param DTCFormat     Defines the input-format of the provided DTC value.
 * @param DTCOrigin     If the Dem supports more than one event memory this parameter is used to select
 *                      the source memory the DTCs shall be read from.
 *
 * @return  Dem_ReturnClearDTCType: Status of the operation of type Dem_ReturnClearDTCType.
 */
Dem_ReturnClearDTCType Dem_ClearDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);
#endif /* DEM_CFG_CHECKAPICONSISTENCY */


/**
 *
 * Dem242: Disables the DTC setting for a DTC group.
 *
 * @param[in]  DTCGroup  Defines the group of DTC that shall be disabled to store in event memory.
 * @param[in]  DTCKind  This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 * @return  DEM_CONTROL_DTC_SETTING_OK: DTC setting control successful
 * @return  DEM_CONTROL_DTC_SETTING_N_OK: DTC setting control not successful
 * @return  DEM_CONTROL_DTC_WRONG_DTCGROUP: DTC setting control not successful because group of DTC was wrong
 */
Dem_ReturnControlDTCSettingType Dem_DisableDTCSetting(Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind);


/**
 *
 * Dem243: Enables the DTC setting for a DTC group.
 *
 * @param[in]  DTCGroup  Defines the group of DTC that shall be enabled to store in event memory.
 * @param[in]  DTCKind  This parameter defines the requested DTC, either only OBD-relevant DTCs or all DTCs
 * @return  DEM_CONTROL_DTC_SETTING_OK: DTC setting control successful
 * @return  DEM_CONTROL_DTC_SETTING_N_OK: DTC setting control not successful
 * @return  DEM_CONTROL_DTC_WRONG_DTCGROUP: DTC setting control not successful because group of DTC was wrong
 */
Dem_ReturnControlDTCSettingType Dem_EnableDTCSetting(Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind);

/**@}*//* End of Doxygen subgroup DEM_DCM_STORAGE */



/**
 *
 * Dem560 : Cancel pending operation started from Dcm.
 */
void Dem_DcmCancelOperation(void);


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/**@}*//* End of Doxygen group DEM_DCM */

#endif /* DEM_DCM_H */
