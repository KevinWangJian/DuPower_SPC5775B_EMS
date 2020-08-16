


#ifndef DEM_TYPES_H
#define DEM_TYPES_H


#include "Std_Types.h"
#include "Dem_Cfg.h"

/* FC_VariationPoint_START */
#if( DEM_BFM_ENABLED == DEM_BFM_ON )
#include "rba_DemBfm_Types.h"
#endif
/* FC_VariationPoint_END */

#include "Dem_Cfg_Version.h"
#include "Rte_Dem_Type.h"

#if (DEM_CFG_OBD == DEM_CFG_OBD_ON)
#include "rba_DemObdBasic_Types.h"
#endif

/* internal definitions: implementation */
#define DEM_INLINE LOCAL_INLINE
#define DEM_UNUSED_PARAM(P)   ((void)(P))

/* component specific extension to the Std_ReturnType */
#define DEM_E_NO_DTC_AVAILABLE      2
#ifndef E_NO_DTC_AVAILABLE
#define E_NO_DTC_AVAILABLE      DEM_E_NO_DTC_AVAILABLE
#endif

#if (E_NO_DTC_AVAILABLE != DEM_E_NO_DTC_AVAILABLE)
#error E_NO_DTC_AVAILABLE not defined correctly
#endif

#define DEM_E_NO_FDC_AVAILABLE      3
#ifndef E_NO_FDC_AVAILABLE
#define E_NO_FDC_AVAILABLE      DEM_E_NO_FDC_AVAILABLE
#endif

#if (E_NO_FDC_AVAILABLE != DEM_E_NO_FDC_AVAILABLE)
#error E_NO_FDC_AVAILABLE not defined correctly
#endif

typedef uint8  Dem_ComponentIdType;
typedef uint8 Dem_DTCGroupIdType;
typedef uint16 Dem_DtcIdType;
typedef uint8 Dem_J1939NodeIdType;

typedef uint8 Dem_ClientIdType;

typedef uint32 Dem_DtcCodeType;

/* Make the Dem_ConfigType opaque by forward declaring it */
typedef struct Dem_ConfigType Dem_ConfigType;

typedef boolean Dem_boolean_least;

typedef uint8 Dem_EventCategoryType;

typedef struct {
    uint16_least evMemId;
    uint16_least locIterator;
} Dem_ReadEventsFromMemoryType;

/**
 * @ingroup DEM_H
 *
 * Used to return the status of reading events from event memory (\ref Dem_ReadEventsFromMemory/ \ref Dem_GetNextEventFromMemory).\n
 * \n
 * DEM_READEVENT_OK\n
 * DEM_READEVENT_NO_MATCHING\n
 * DEM_READEVENT_WRONG_ORIGIN
 */
typedef uint8 Dem_ReadEventType;
#define DEM_READEVENT_OK                     0x00
#define DEM_READEVENT_NO_MATCHING_ELEMENT    0x01
#define DEM_READEVENT_WRONG_ORIGIN           0x02


typedef uint8 Dem_ReturnControlDTCSettingType;
#define DEM_CONTROL_DTC_SETTING_OK		0x00
#define DEM_CONTROL_DTC_SETTING_N_OK	0x01
#define DEM_CONTROL_DTC_WRONG_DTCGROUP	0x02

#ifndef DEM_EVENT_STATUS_INACTIVE
#define  DEM_EVENT_STATUS_INACTIVE        0x50
#endif

#ifndef DEM_EVENT_STATUS_INVALIDREPORT
#define  DEM_EVENT_STATUS_INVALIDREPORT   0xFF
#endif

/**
 * @ingroup DEM_H
 *
 * Used to return the status of @ref Dem_GetExtendedDataRecordByDTC.\n
 * \n
 * DEM_RECORD_OK\n
 * DEM_RECORD_WRONG_DTC\n
 * DEM_RECORD_WRONG_DTCORIGIN\n
 * DEM_RECORD_WRONG_DTCKIND\n
 * DEM_RECORD_WRONG_NUMBER\n
 * DEM_RECORD_WRONG_BUFFERSIZE\n
 * DEM_RECORD_PENDING
 */
typedef uint8 Dem_ReturnGetExtendedDataRecordByDTCType;
#define DEM_RECORD_OK                            0x00
#define DEM_RECORD_WRONG_DTC                     0x01
#define DEM_RECORD_WRONG_DTCORIGIN               0x02
#define DEM_RECORD_WRONG_DTCKIND                 0x03
#define DEM_RECORD_WRONG_NUMBER                  0x04
#define DEM_RECORD_WRONG_BUFFERSIZE              0x05
#define DEM_RECORD_PENDING                       0x06


/**
 * @ingroup DEM_H
 *
 * Used to return the status of Used to return the status of @ref Dem_GetSizeOfExtendedDataRecordByDTC.\n
 * \n
 * DEM_GET_SIZEOFEDRBYDTC_OK\n
 * DEM_GET_SIZEOFEDRBYDTC_W_DTC\n
 * DEM_GET_SIZEOFEDRBYDTC_W_DTCOR\n
 * DEM_GET_SIZEOFEDRBYDTC_W_DTCKI\n
 * DEM_GET_SIZEOFEDRBYDTC_W_RNUM\n
 * DEM_GET_SIZEOFEDRBYDTC_PENDING
 */
typedef uint8 Dem_ReturnGetSizeOfExtendedDataRecordByDTCType;

#define DEM_GET_SIZEOFEDRBYDTC_OK                0x00
#define DEM_GET_SIZEOFEDRBYDTC_W_DTC             0x01
#define DEM_GET_SIZEOFEDRBYDTC_W_DTCOR           0x02
#define DEM_GET_SIZEOFEDRBYDTC_W_DTCKI           0x03
#define DEM_GET_SIZEOFEDRBYDTC_W_RNUM            0x04
#define DEM_GET_SIZEOFEDRBYDTC_PENDING           0x05


/**
 * @ingroup DEM_H
 *
 * Used to return the status of @ref Dem_GetFreezeFrameDataByDTC.\n
 * \n
 * DEM_GET_FFDATABYDTC_OK\n
 * DEM_GET_FFDATABYDTC_WRONG_DTC\n
 * DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN\n
 * DEM_GET_FFDATABYDTC_WRONG_DTCKIND\n
 * DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE\n
 * DEM_GET_FFDATABYDTC_PENDING
 */
typedef uint8 Dem_ReturnGetFreezeFrameDataByDTCType;
#define DEM_GET_FFDATABYDTC_OK                   0x00
#define DEM_GET_FFDATABYDTC_WRONG_DTC            0x01
#define DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN      0x02
#define DEM_GET_FFDATABYDTC_WRONG_DTCKIND        0x03
#define DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER   0x04
#define DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE     0x05
#define DEM_GET_FFDATABYDTC_PENDING              0x06


/**
 * @ingroup DEM_H
 *
 * Used to return the status of @ref Dem_GetSizeOfFreezeFrameByDTC.\n
 * \n
 * DEM_GET_SIZEOFFF_OK\n
 * DEM_GET_SIZEOFFF_WRONG_DTC\n
 * DEM_GET_SIZEOFFF_WRONG_DTCOR\n
 * DEM_GET_SIZEOFFF_WRONG_DTCKIND\n
 * DEM_GET_SIZEOFFF_WRONG_RNUM\n
 * DEM_GET_SIZEOFFF_PENDING
 */
typedef uint8 Dem_ReturnGetSizeOfFreezeFrameByDTCType;
#define DEM_GET_SIZEOFFF_OK                      0x00
#define DEM_GET_SIZEOFFF_WRONG_DTC               0x01
#define DEM_GET_SIZEOFFF_WRONG_DTCOR             0x02
#define DEM_GET_SIZEOFFF_WRONG_DTCKIND           0x03
#define DEM_GET_SIZEOFFF_WRONG_RNUM              0x04
#define DEM_GET_SIZEOFFF_PENDING                 0x05


/**
 * @ingroup DEM_H
 *
 * Used to return the status of (re-)setting a specific filter.\n
 * \n
 * DEM_FILTER_ACCEPTED\n
 * DEM_WRONG_FILTER
 */
typedef uint8 Dem_ReturnSetFilterType;
#define DEM_FILTER_ACCEPTED                      0x00
#define DEM_WRONG_FILTER                         0x01


/**
 * @ingroup DEM_H
 * DEM_FILTER_WITH_SEVERITY_YES\n
 * DEM_FILTER_WITH_SEVERITY_NO
 */
typedef uint8 Dem_FilterWithSeverityType;
#define DEM_FILTER_WITH_SEVERITY_YES             0x00
#define DEM_FILTER_WITH_SEVERITY_NO              0x01


/**
 * @ingroup DEM_H
 * Defines the type of a DTCSeverityMask according to ISO14229-1.\n
 * \n
 * DEM_SEVERITY_NO_SEVERITY\n
 * DEM_SEVERITY_MAINTENANCE_ONLY\n
 * DEM_SEVERITY_CHECK_AT_NEXT_HALT\n
 * DEM_SEVERITY_CHECK_IMMEDIATELY
 */
typedef uint8 Dem_DTCSeverityType;
#define DEM_SEVERITY_NO_SEVERITY                 0x00u
#define DEM_SEVERITY_MAINTENANCE_ONLY            0x20u
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT          0x40u
#define DEM_SEVERITY_CHECK_IMMEDIATELY           0x80u


/**
 * @ingroup DEM_H
 * DEM_FILTER_FOR_FDC_YES\n
 * DEM_FILTER_FOR_FDC_NO
 */
typedef uint8 Dem_FilterForFDCType;
#define DEM_FILTER_FOR_FDC_YES                   0x00
#define DEM_FILTER_FOR_FDC_NO                    0x01



/**
 * @ingroup DEM_H
 *
 * Used to return the status of @ref Dem_GetStatusOfDTC.\n
 * \n
 * DEM_STATUS_OK\n
 * DEM_STATUS_WRONG_DTC\n
 * DEM_STATUS_WRONG_DTCORIGIN\n
 * DEM_STATUS_WRONG_DTCKIND\n
 * DEM_STATUS_FAILED
 */
typedef uint8 Dem_ReturnGetStatusOfDTCType;
#define DEM_STATUS_OK                       0x00
#define DEM_STATUS_WRONG_DTC                0x01
#define DEM_STATUS_WRONG_DTCORIGIN          0x02
#define DEM_STATUS_WRONG_DTCKIND            0x03
#define DEM_STATUS_FAILED                   0x04


/**
 * @ingroup DEM_H
 * Selects a group of DTCs. Currently only ALL_DTCS is accepted.\n
 * \n
 * DEM_DTC_GROUP_EMISSION_REL_DTCS\n
 * DEM_DTC_GROUP_ALL_DTCS
 */
typedef uint32 Dem_DTCGroupType;
#define DEM_DTC_GROUP_EMISSION_REL_DTCS     0x00000000u
#define DEM_DTC_GROUP_ALL_DTCS              0xFFFFFFu

/**
 * @ingroup DEM_H
 * Used to return the status of @ref Dem_GetNumberOfFilteredDTC.\n
 * \n
 * DEM_NUMBER_OK\n
 * DEM_NUMBER_FAILED\n
 * DEM_NUMBER_PENDING
 */
typedef uint8 Dem_ReturnGetNumberOfFilteredDTCType;
#define DEM_NUMBER_OK                     0x00
#define DEM_NUMBER_FAILED                 0x01
#define DEM_NUMBER_PENDING                0x02


/**
 * @ingroup DEM_H
 * DTC translation format as defined in ISO14229-1 Service 0x19 returned by @ref Dem_GetTranslationType.\
 * \n
 * DEM_DTC_TRANSLATION_ISO15031_6\n
 * DEM_DTC_TRANSLATION_ISO14229_1\n
 * DEM_DTC_TRANSLATION_SAEJ1939_73\n
 * DEM_DTC_TRANSLATION_ISO11992_4\n
 * DEM_DTC_TRANSLATION_J2012DA_FORMAT_04
 */
typedef uint8 Dem_DTCTranslationFormatType;
#define DEM_DTC_TRANSLATION_ISO15031_6          0x00
#define DEM_DTC_TRANSLATION_ISO14229_1          0x01
#define DEM_DTC_TRANSLATION_SAEJ1939_73         0x02
#define DEM_DTC_TRANSLATION_ISO11992_4          0x03
#define DEM_DTC_TRANSLATION_J2012DA_FORMAT_04   0x04


/**
 * @ingroup DEM_H
 * Used to return the status of @ref Dem_GetSeverityOfDTC.\n
 * \n
 * DEM_GET_SEVERITYOFDTC_OK\n
 * DEM_GET_SEVERITYOFDTC_WRONG_DTC\n
 * DEM_GET_SEVERITYOFDTC_WRONG_DTCORIGIN\n
 * DEM_GET_SEVERITYOFDTC_NOSEVERITY
 */
typedef uint8 Dem_ReturnGetSeverityOfDTCType;
#define DEM_GET_SEVERITYOFDTC_OK               0x00
#define DEM_GET_SEVERITYOFDTC_WRONG_DTC        0x01
#define DEM_GET_SEVERITYOFDTC_WRONG_DTCORIGIN  0x02
#define DEM_GET_SEVERITYOFDTC_NOSEVERITY       0x03

/**
 * @ingroup DEM_H
 * Used to return the status of @ref Dem_GetFunctionalUnitOfDTC.\n
 * \n
 * DEM_GET_FUNCTIONALUNITOFDTC_OK\n
 * DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC
 */
typedef uint8 Dem_ReturnGetFunctionalUnitOfDTCType;
#define DEM_GET_FUNCTIONALUNITOFDTC_OK          0x00
#define DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC   0x01

/**
 * @ingroup DEM_H
 * Used to define the request type of the DTC in @ref Dem_GetDTCByOccurrenceTime.\n
 * \n
 * DEM_FIRST_FAILED_DTC\n
 * DEM_MOST_RECENT_FAILED_DTC\n
 * DEM_FIRST_DET_CONFIRMED_DTC\n
 * DEM_MOST_REC_DET_CONFIRMED_DTC
 */
typedef uint8 Dem_DTCRequestType;
#define DEM_FIRST_FAILED_DTC            0x01
#define DEM_MOST_RECENT_FAILED_DTC      0x02
#define DEM_FIRST_DET_CONFIRMED_DTC     0x03
#define DEM_MOST_REC_DET_CONFIRMED_DTC  0x04


/**
 * @ingroup DEM_H
 * Used to return the status of @ref Dem_GetFreezeFrameDataByRecord.\n
 * \n
 * DEM_GET_FFBYRECORD_OK\n
 * DEM_GET_FFBYRECORD_WRONG_RECORD\n
 * DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD\n
 * DEM_GET_FFBYRECORD_WRONG_BUFFERSIZE
 */
typedef uint8 Dem_ReturnGetFreezeFrameDataByRecordType;
#define DEM_GET_FFBYRECORD_OK                    0x00
#define DEM_GET_FFBYRECORD_WRONG_RECORD          0x01
#define DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD     0x02
#define DEM_GET_FFBYRECORD_WRONG_BUFFERSIZE      0x03

/**
 * @ingroup DEM_H
 * Used to return the status of @ref Dem_GetDTCByOccurrenceTime.\n
 * \n
 * DEM_OCCURR_OK\n
 * DEM_OCCURR_WRONG_DTCKIND\n
 * DEM_OCCURR_FAILED
 */
typedef uint8 Dem_ReturnGetDTCByOccurrenceTimeType;
#define DEM_OCCURR_OK                     0x00
#define DEM_OCCURR_WRONG_DTCKIND          0x01
#define DEM_OCCURR_FAILED                 0x02


typedef uint8 Dem_EraseAllStatusType;
#define DEM_ERASE_ALL_STATUS_NOREQUEST              0x00
#define DEM_ERASE_ALL_STATUS_PENDING                0x02
#define DEM_ERASE_ALL_STATUS_HASHID_WRITE_PENDING   0x04
#define DEM_ERASE_ALL_STATUS_FAILED                 0x08
#define DEM_ERASE_ALL_STATUS_SUCCESS                0x10

typedef uint8 Dem_EraseAllRequestType;
#define DEM_ERASE_ALL_REQUEST_NONE       0x00
#define DEM_ERASE_ALL_REQUEST_ALL        0x01

typedef uint8 Dem_HashIdCheckResultType;
#define DEM_HASH_ID_CHECK_DISABLED                  0x00
#define DEM_HASH_ID_CHECK_NOT_POSSIBLE              0x01
#define DEM_HASH_ID_NO_CHANGE                       0x02
#define DEM_HASH_ID_MISMATCH                        0x04


#if (DEM_CFG_DEBUGDATA == DEM_CFG_DEBUGDATA_32BIT)
typedef uint32 Dem_DebugDataType;
#else
typedef uint8 Dem_DebugDataType;
#endif


/**
 * @ingroup DEM_H
 *
 * This data-type defines the 'kind' of a requested DTC, either only OBD-relevant DTCs or all DTC\n
 * \n
 * DEM_DTC_KIND_ALL_DTCS\n
 * DEM_DTC_KIND_EMISSION_REL_DTCS
 */
typedef uint8  Dem_DTCKindType;
#define DEM_DTC_KIND_ALL_DTCS                  0x01u
#define DEM_DTC_KIND_EMISSION_REL_DTCS         0x02u

/**
 * @ingroup DEM_H
 *
 * Used to return the status of Dem_DisableDTCRecordUpdate.\n
 * \n
 * DEM_DISABLE_DTCRECUP_OK\n
 * DEM_DISABLE_DTCRECUP_WRONG_DTC\n
 * DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN\n
 * DEM_DISABLE_DTCRECUP_PENDING\n
 */

typedef uint8 Dem_ReturnDisableDTCRecordUpdateType;
#define DEM_DISABLE_DTCRECUP_OK                0x00
#define DEM_DISABLE_DTCRECUP_WRONG_DTC         0x01
#define DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN   0x02
#define DEM_DISABLE_DTCRECUP_PENDING           0x03


typedef uint8 Dem_TriggerType;
#define DEM_TRIGGER_NONE                0x00u
#define DEM_TRIGGER_ON_TEST_FAILED      0x01u
#define DEM_TRIGGER_ON_PENDING          0x02u
#define DEM_TRIGGER_ON_CONFIRMED        0x04u
#define DEM_TRIGGER_ON_FDC_THRESHOLD    0x08u
#define DEM_TRIGGER_ON_PASSED           0x10u
#define DEM_TRIGGER_ON_MIRROR           0x20u

/**
 * @ingroup DEM_H
 *
 * Used to return the status of the @ref Dem_GetNextFiltered interfaces.\n
 * \n
 * DEM_FILTERED_OK\n
 * DEM_FILTERED_NO_MATCHING_DTC\n
 * DEM_FILTERED_WRONG_DTCKIND\n
 * DEM_FILTERED_PENDING
 */
typedef uint8 Dem_ReturnGetNextFilteredDTCType;
#define DEM_FILTERED_NO_MATCHING_DTC        0x01
#define DEM_FILTERED_WRONG_DTCKIND          0x02

/** The below defines are common for the types : Dem_ReturnGetNextFilteredDTCType(AR4.0) and Dem_ReturnGetNextFilteredElementType(AR4.2) */
#define DEM_FILTERED_OK                     0x00
#define DEM_FILTERED_PENDING                0x03

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)
/**
 * @ingroup DEM_H
 *
 * Used to return the status of Dem_DcmGetNextFilteredXxx and Dem_J1939DcmGetNextFilteredXxx..\n
 * \n
 * DEM_FILTERED_OK\n
 * DEM_FILTERED_NO_MATCHING_ELEMENT\n
 * DEM_FILTERED_PENDING\n
 * DEM_FILTERED_BUFFER_TOO_SMALL
 */
typedef uint8 Dem_ReturnGetNextFilteredElementType;
#define DEM_FILTERED_NO_MATCHING_ELEMENT    0x01
#define DEM_FILTERED_BUFFER_TOO_SMALL       0x04

/**
 * @ingroup DEM_H
 * The type to distinguish which DTCs gets cleared.\n
 * \n
 * DEM_J1939DTC_CLEAR_ALL\n
 * DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE
 */
typedef uint8 Dem_J1939DcmSetClearFilterType;
#define DEM_J1939DTC_CLEAR_ALL                    0x00
#define DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE      0x01

/**
 * @ingroup DEM_H
 * The type to distinguish which DTCs should be filtered.\n
 * \n
 * DEM_J1939DTC_ACTIVE\n
 * DEM_J1939DTC_PREVIOUSLY_ACTIVE\n
 * DEM_J1939DTC_PENDING\n
 * DEM_J1939DTC_PERMANENT\n
 * DEM_J1939DTC_CURRENTLY_ACTIVE
 */
typedef uint8 Dem_J1939DcmDTCStatusFilterType;
#define DEM_J1939DTC_ACTIVE              0x00
#define DEM_J1939DTC_PREVIOUSLY_ACTIVE   0x01
#define DEM_J1939DTC_PENDING             0x02
#define DEM_J1939DTC_PERMANENT           0x03
#define DEM_J1939DTC_CURRENTLY_ACTIVE    0x04

/**
 * @ingroup DEM_H
 * The type to distinguish which DTCs gets cleared.\n
 * \n
 * DEM_J1939DCM_FREEZEFRAME\n
 * DEM_J1939DCM_EXPANDED_FREEZEFRAME\n
 * DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME
 */
typedef uint8 Dem_J1939DcmSetFreezeFrameFilterType;
#define DEM_J1939DCM_FREEZEFRAME                    0x00
#define DEM_J1939DCM_EXPANDED_FREEZEFRAME           0x01
#define DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME   0x02

/**
 * @ingroup DEM_H
 * Used to receive the commulated lamp status.\n
 * \n
 * bits 8-7     Malfunction Indicator Lamp Status\n
 * bits 6-5     Red Stop Lamp Status\n
 * bits 4-3     Amber Warning Lamp Status\n
 * bits 2-1     Protect Lamp Status\n
 * bits 8-7     Flash Malfunction Indicator Lamp\n
 * bits 6-5     Flash Red Stop Lamp\n
 * bits 4-3     Flash Amber Warning Lamp\n
 * bits 2-1     Flash Protect Lamp
 */
typedef uint16 Dem_J1939DcmLampStatusType;

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)

/* Dummy structure to provide the types*/

/**
 * @ingroup DEM_H
 * This structure represents all data elemets of the DM05 message. The
 * encoding shall be done acording SAE J1939-73\n
 */
typedef struct
{
   uint8  ActiveTroubleCodes;
   uint8  PreviouslyActiveDiagnosticTroubleCodes;
   uint8  OBDCompliance;
   uint8  ContinuouslyMonitoredSystemsSupport_Status;
   uint16 NonContinuouslyMonitoredSystemsSupport;
   uint16 NonContinuouslyMonitoredSystemsStatus;
} Dem_J1939DcmDiagnosticReadiness1Type;

/**
 * @ingroup DEM_H
 * This structure represents all data elemets of the DM21 message. The
 * encoding shall be done acording SAE J1939-73\n
 */
typedef struct
{
   uint16  DistanceTraveledWhileMILisActivated;
   uint16  DistanceSinceDTCsCleared;
   uint16  MinutesRunbyEngineWhileMILisActivated;
   uint16  TimeSinceDiagnosticTroubleCodesCleared;
} Dem_J1939DcmDiagnosticReadiness2Type;

/**
 * @ingroup DEM_H
 * This structure represents all data elemets of the DM26 message. The
 * encoding shall be done acording SAE J1939-73\n
 */
typedef struct
{
   uint16 TimeSinceEngineStart;
   uint8  NumberofWarmupsSinceDTCsCleared;
   uint8  ContinuouslyMonitoredSystemsEnableCompletedStatus;
   uint16 NonContinuouslyMonitoredSystemsEnableStatus;
   uint16 NonContinuouslyMonitoredSystems;
} Dem_J1939DcmDiagnosticReadiness3Type;

#endif
#endif

#endif

