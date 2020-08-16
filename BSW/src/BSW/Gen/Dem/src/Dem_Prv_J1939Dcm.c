


#include "Dem_J1939Dcm.h"

#include "Dem_Prv_J1939Dcm.h"

#include "Dem_Clear.h"
#include "Dem_Nvm.h"
#include "Dem_Dependencies.h"
#include "Dem_StorageCondition.h"
#include "Dem_DTCStatusByte.h"
#include "Dem_ISO14229Byte.h"
#include "Dem_Events.h"

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnSetFilterType Dem_J1939DcmSetDTCFilter(Dem_J1939DcmDTCStatusFilterType DTCStatusFilter, Dem_DTCKindType DTCKind,uint8 node,Dem_J1939DcmLampStatusType* LampStatus)
{
    DEM_UNUSED_PARAM(DTCStatusFilter);
    DEM_UNUSED_PARAM(DTCKind);
    DEM_UNUSED_PARAM(node);
    DEM_UNUSED_PARAM(LampStatus);

    return DEM_WRONG_FILTER;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnGetNumberOfFilteredDTCType Dem_J1939DcmGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC)
{
    DEM_UNUSED_PARAM(NumberOfFilteredDTC);

    return DEM_NUMBER_FAILED;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFilteredDTC(uint32* J1939DTC,uint8* OccurenceCounter)
{
    DEM_UNUSED_PARAM(J1939DTC);
    DEM_UNUSED_PARAM(OccurenceCounter);

    return DEM_FILTERED_NO_MATCHING_ELEMENT;
}

Dem_ReturnSetFilterType Dem_J1939DcmSetFreezeFrameFilter(Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind,uint8 node)
{
    DEM_UNUSED_PARAM(FreezeFrameKind);
    DEM_UNUSED_PARAM(node);

    return DEM_WRONG_FILTER;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFreezeFrame(uint32* J1939DTC,uint8* OccurenceCounter,uint8* DestBuffer,uint16* BufSize)
{
    DEM_UNUSED_PARAM(J1939DTC);
    DEM_UNUSED_PARAM(OccurenceCounter);
    DEM_UNUSED_PARAM(DestBuffer);
    DEM_UNUSED_PARAM(BufSize);

    return DEM_FILTERED_NO_MATCHING_ELEMENT;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextSPNInFreezeFrame(uint32* SPNSupported,uint8* SPNDataLength)
{
    DEM_UNUSED_PARAM(SPNSupported);
    DEM_UNUSED_PARAM(SPNDataLength);

    return DEM_FILTERED_NO_MATCHING_ELEMENT;
}

void Dem_J1939DcmFirstDTCwithLampStatus(uint8 node)
{
    DEM_UNUSED_PARAM(node);
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextDTCwithLampStatus(Dem_J1939DcmLampStatusType* LampStatus,uint32* J1939DTC,uint8* OccurenceCounter)
{
    DEM_UNUSED_PARAM(LampStatus);
    DEM_UNUSED_PARAM(J1939DTC);
    DEM_UNUSED_PARAM(OccurenceCounter);

    return DEM_FILTERED_NO_MATCHING_ELEMENT;
}

#if(DEM_CFG_OBD != DEM_CFG_OBD_OFF)

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnSetFilterType Dem_J1939DcmSetRatioFilter(uint16* IgnitionCycleCounter,uint16* OBDMonitoringConditionsEncountered,uint8 node)
{
    DEM_UNUSED_PARAM(IgnitionCycleCounter);
    DEM_UNUSED_PARAM(OBDMonitoringConditionsEncountered);
    DEM_UNUSED_PARAM(node);

    return DEM_WRONG_FILTER;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Dem_ReturnGetNextFilteredElementType Dem_J1939DcmGetNextFilteredRatio(uint16* SPN,uint16* Numerator,uint16* Denominator)
{
    DEM_UNUSED_PARAM(SPN);
    DEM_UNUSED_PARAM(Numerator);
    DEM_UNUSED_PARAM(Denominator);

    return DEM_FILTERED_NO_MATCHING_ELEMENT;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness1(Dem_J1939DcmDiagnosticReadiness1Type* DataValue,uint8 node)
{
    DEM_UNUSED_PARAM(DataValue);
    DEM_UNUSED_PARAM(node);

    return E_NOT_OK;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness2(Dem_J1939DcmDiagnosticReadiness2Type* DataValue,uint8 node)
{
    DEM_UNUSED_PARAM(DataValue);
    DEM_UNUSED_PARAM(node);

    return E_NOT_OK;
}

/* MR12 RULE 8.13 VIOLATION: The warning can be ignored since the interface is not completely implemented */
Std_ReturnType Dem_J1939DcmReadDiagnosticReadiness3(Dem_J1939DcmDiagnosticReadiness3Type* DataValue,uint8 node)
{
    DEM_UNUSED_PARAM(DataValue);
    DEM_UNUSED_PARAM(node);

    return E_NOT_OK;
}
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

Dem_ReturnClearDTCType Dem_J1939DcmClearDTCBody(Dem_J1939DcmSetClearFilterType DTCTypeFilter , uint8 node)
{
    Dem_DtcIdType dtcId;
    Dem_UdsStatusByteType status;

    /* Initialization */
    Dem_ClientClearMachine.IsClearInterrupted = FALSE;
    Dem_ClientClearMachine.NumberOfEventsProcessed = 0;

    /* Check whether the Clear is requested newly */
    if ((Dem_ClientClearMachine.IsNewClearRequest) || (!Dem_J1939DtcIdListIteratorIsValid(&(Dem_ClientClearMachine.DtcIt2))))
    {
        Dem_J1939DtcIdListIteratorNewFromJ1939NodeID(&(Dem_ClientClearMachine.DtcIt2), node);
    }

    while (Dem_J1939DtcIdListIteratorIsValid(&(Dem_ClientClearMachine.DtcIt2)))
    {
        dtcId = Dem_J1939DtcIdListIteratorCurrent(&(Dem_ClientClearMachine.DtcIt2));
        status = Dem_DtcStatusByteRetrieve(dtcId);

        if(DTCTypeFilter == DEM_J1939DTC_CLEAR_ALL)
        {
            if((Dem_ISO14229ByteIsTestFailed(status) && Dem_ISO14229ByteIsConfirmedDTC(status)) || (Dem_ISO14229ByteIsWarningIndicatorRequested(status)))
            {
                Dem_ClearSingleDTC(dtcId, DEM_DTC_ORIGIN_PRIMARY_MEMORY, &Dem_ClientClearMachine);
            }
        }
        else
        {
            if((!Dem_ISO14229ByteIsTestFailed(status)) && Dem_ISO14229ByteIsConfirmedDTC(status) && (!Dem_ISO14229ByteIsWarningIndicatorRequested(status)))
            {
                Dem_ClearSingleDTC(dtcId, DEM_DTC_ORIGIN_PRIMARY_MEMORY, &Dem_ClientClearMachine);
            }
        }
        if (!Dem_ClientClearMachine.IsClearInterrupted)
        {
            Dem_J1939DtcIdListIteratorNext(&(Dem_ClientClearMachine.DtcIt2));
        }
        else
        {
            return DEM_CLEAR_PENDING;
        }
    }

    if (!Dem_ClientClearMachine.IsClearInterrupted)
    {
        return DEM_CLEAR_OK;
    }
    return DEM_CLEAR_PENDING;
}

Dem_ReturnClearDTCType Dem_J1939DcmClearDTC(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node)
{
    uint8 ClientId = DEM_CLIENTID_J1939;

    /* return values are harmonized (same literal value) between Dem_ReturnClearDTCType and Std_ReturnType  */
    return (Dem_ReturnClearDTCType)Dem_J1939DcmClearDTC_4_3 (DTCTypeFilter, node, ClientId);
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

#endif

