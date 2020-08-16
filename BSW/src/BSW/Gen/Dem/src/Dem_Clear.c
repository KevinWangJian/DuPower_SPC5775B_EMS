

#include "Dem_Dcm.h"
#include "Rte_Dem.h"

#include "Dem_Clear.h"

#include "Dem_ClientBaseHandling.h"
#include "Dem_ClientClearMachine.h"
#include "Dem_ClientRequestDispatcher.h"
#include "Dem_Events.h"
#include "Dem_EventRecheck.h"
#include "Dem_StorageCondition.h"
#include "Dem_EvMem.h"
#include "Dem_DTCs.h"
#include "Dem_DTCGroup.h"
#include "Dem_DTCStatusByte.h"
#include "Dem_Obd.h"
#include "Dem_EventStatus.h"
#include "Dem_EvMemGen.h"
#include "Dem_Cfg_ExtPrototypes.h"
#include "Dem_Prv_J1939Dcm.h"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
static Std_ReturnType Dem_ClearResult = DEM_CLEAR_PENDING;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

static Std_ReturnType Dem_ClearDTCBody(Dem_ClientSelectionType Selection, Dem_DTCOriginType DTCOrigin)
{
#if(DEM_CFG_CLEAR_DTC_LIMITATION == DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS)
    Dem_DtcIdType dtcId;
    Dem_DTCGroupIdType DTCGroupId;
#endif

    /* Initialization */
    Dem_ClientClearMachine.IsClearInterrupted = FALSE;
    Dem_ClientClearMachine.NumberOfEventsProcessed = 0;

    if (Dem_ClientSelectionType_isSelectionDTCGroupAll(Selection))
    { /* clear all DTCs */

        Dem_ClearAllDTCs(DTCOrigin, &Dem_ClientClearMachine);

        if (!Dem_ClientClearMachine.IsClearInterrupted)
        {
            Dem_EvMemGenClearDtcByOccurrenceTime(DTCOrigin);
            Dem_EvMemGenClearOverflow(DTCOrigin);
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
            rba_DemObdBasic_Clear(DTCOrigin);
#endif
            return DEM_CLEAR_OK;
        }
        return DEM_CLEAR_PENDING;
    }

#if(DEM_CFG_CLEAR_DTC_LIMITATION == DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS)

    if (Dem_ClientSelectionType_isSelectionDTCGroup(Selection))
    {
        DTCGroupId = (uint8)Dem_ClientSelectionType_getSelectionDtcIndex (Selection);
        /* Clear All DTCs which belongs to DTCGroup */
        Dem_DtcsClearDtcInGroup(DTCGroupId, DTCOrigin, &Dem_ClientClearMachine);
        if (!Dem_ClientClearMachine.IsClearInterrupted)
        {
            return DEM_CLEAR_OK;
        }
        return DEM_CLEAR_PENDING;
    }
    else if (Dem_ClientSelectionType_isSelectionSingleDTC(Selection))
    { /* clear single DTC */
        dtcId = Dem_ClientSelectionType_getSelectionDtcIndex (Selection);

        Dem_ClearSingleDTC(dtcId, DTCOrigin, &Dem_ClientClearMachine);

        if (!Dem_ClientClearMachine.IsClearInterrupted)
        {
            return DEM_CLEAR_OK;
        }
        return DEM_CLEAR_PENDING;
    }
    else
    {
        return DEM_CLEAR_WRONG_DTC; /** Ideally the code shall not reach here */
    }

#else
    return DEM_CLEAR_FAILED;
#endif
}

void Dem_ClearMainFunction(void)
{
    Dem_ClientRequestType tempRequest;
    Dem_ClientIdType tempClientId;

    if (Dem_ClientClearMachine_GetMachineState() != DEM_CLEAR_DTC_MACHINE_STATE_IDLE)
    {
        tempClientId = Dem_ClientClearMachine_GetMachineActiveClient();
        tempRequest = Dem_Client_getClient(tempClientId)->request;
        /* process state machine */
        if (!Dem_ClientRequestType_isCancelRequested(tempRequest))
        {
            if (Dem_ClientClearMachine_GetMachineState() == DEM_CLEAR_DTC_MACHINE_STATE_EXEC)
            {
#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
                if (tempClientId == DEM_CLIENTID_J1939)
                {
                    Dem_ClearResult = Dem_J1939DcmClearDTCBody(Dem_Client_getClient(tempClientId)->J1939DTCTypeFilter,
                            Dem_Client_getClient(tempClientId)->J1939node);
                }
                else
#endif
                {
                    if (Dem_ClientClearMachine.IsNewClearRequest)
                    {
                        /* Callback function to notify when ClearDTC is triggered */
#if(DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED == DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED_ON )

                        DEM_CFG_CLEAR_DTC_START_NOTIFICATION_CALLBACK_ALLOWEDFNC(Dem_Client_getClient(tempClientId)->DTC,
                                Dem_Client_getClient(tempClientId)->DTCFormat, Dem_Client_getClient(tempClientId)->DTCOrigin);
#endif
                    }

                    Dem_ClearResult = Dem_ClearDTCBody(Dem_Client_getClient(tempClientId)->selection,
                            Dem_Client_getClient(tempClientId)->DTCOrigin);
                }

                Dem_ClientClearMachine.IsNewClearRequest = FALSE;

                if (Dem_ClearResult != DEM_CLEAR_PENDING)
                {
                    Dem_ClientClearMachine_SetClientRequest(tempClientId, DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM);
                }
            }
            /* Step 2 - Sync to NVM-Storage (optional) */
            if (Dem_ClientClearMachine_GetMachineState() == DEM_CLEAR_DTC_MACHINE_STATE_WAITINGFORNVM)
            {
                /* Remark:
                 * Synchronization with NVM and delivering of error information requires that the NVM block status NVM_REQ_INTEGRITY_FAILED
                 * is not mapped to DEM_NVM_FAILED in the wrapper function Dem_NvmGetStatus. */
                if (((DEM_CFG_CLEAR_DTC_BEHAVIOR == DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH)
                        && (Dem_ClearResult == DEM_CLEAR_OK) && Dem_NvMIsClearPending())
#if (DEM_CFG_TRIGGERMONITORINITBEFORECLEAROK == TRUE)
                        || Dem_EvtIsAnyInitMonitoringRequestedClear()
#endif
                        )
                {
                    /* Do not change state --> NVM storage pending */
                }
                else
                {
                    if ((DEM_CFG_CLEAR_DTC_BEHAVIOR == DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH)
                            && (Dem_NvMIsClearFailed()))
                    {
                        Dem_ClearResult = DEM_CLEAR_MEMORY_ERROR;
                    }

                    if (!Dem_ClientClearMachine_isProcessingClient(DEM_CLIENTID_J1939))
                    {
                        /* Callback function to notify when ClearDTC is finished */
#if(DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED == DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED_ON )

                        DEM_CFG_CLEAR_DTC_FINISH_NOTIFICATION_CALLBACK_ALLOWEDFNC(
                                Dem_Client_getClient(tempClientId)->DTC, Dem_Client_getClient(tempClientId)->DTCFormat,
                                Dem_Client_getClient(tempClientId)->DTCOrigin);
#endif
                    }
                    Dem_ClientResultType_setResult(&Dem_Client_getClient(tempClientId)->result, tempRequest,
                            Dem_ClearResult);
                    Dem_ClientClearMachine_SetClientRequest(tempClientId, DEM_CLEAR_DTC_MACHINE_STATE_IDLE);
                }
            }
        }
        else
        {
            Dem_ClientResultType_confirmCancel(&Dem_Client_getClient(tempClientId)->result, tempRequest);
            Dem_ClientClearMachine_SetClientRequest(tempClientId, DEM_CLEAR_DTC_MACHINE_STATE_IDLE);
        }
    }
}

Dem_ReturnClearDTCType Dem_DcmCheckClearParameter (uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    Dem_DtcIdType dtcId;
    Dem_DTCGroupIdType DTCGroupId;

    if (!Dem_EvMemIsDtcOriginValid(&DTCOrigin))
    {
        return DEM_CLEAR_WRONG_DTCORIGIN;
    }


    if (   (DTCFormat != DEM_DTC_FORMAT_UDS)
        /* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
         && (DTCFormat != DEM_DTC_FORMAT_OBD)
#endif
         /* FC_VariationPoint_END */
        )
    {
        return DEM_CLEAR_WRONG_DTC;
    }

    if (DTC == DEM_DTC_GROUP_ALL_DTCS)
    {
        return DEM_CLEAR_OK;
    }
    else
    {

        if ( Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION) == Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS) )
        {
            DEM_DET(DEM_DET_APIID_CLEARDTC, DEM_E_WRONG_CONFIGURATION);
            return DEM_CLEAR_WRONG_DTC;
        }
        else
        {
            DTCGroupId = Dem_DtcGroupIdFromDtcGroupCode(DTC);
            if (DTCGroupId != DEM_DTCGROUPID_INVALID)
            {
                return DEM_CLEAR_OK;
            }
            else
            { /* clear single DTC */
                dtcId = Dem_DtcIdFromDtcCode(DTC);
                if ((!Dem_DtcIsSupported(dtcId)) || (DTCFormat == DEM_DTC_FORMAT_OBD))
                {
                    /* clear single OBD DTC is not allowed according to SAE-1979! */
                    return DEM_CLEAR_WRONG_DTC;
                }
                return DEM_CLEAR_OK;
            }
        }
    }
}

static boolean Dem_Client_AreParametersAlreadyRequested(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    /* To Adapt to AR4.2 */
    if (DTCOrigin == DEM_DTC_ORIGIN_USERDEFINED_MEMORY)
    {
        DTCOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
    }

    return ((Dem_Clients[ClientId].DTC == DTC) && (Dem_Clients[ClientId].DTCFormat == DTCFormat) && (Dem_Clients[ClientId].DTCOrigin == DTCOrigin));
}

Dem_ReturnClearDTCType Dem_ClearDTC(uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    Dem_ReturnClearDTCType returnSts = E_OK;
    uint8 ClientId = DEM_CLIENTID_DCM;

	DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_CLEARDTC,DEM_CLEAR_FAILED);

    if (!Dem_Client_AreParametersAlreadyRequested(ClientId, DTC, DTCFormat, DTCOrigin))
    {
        /* return values are harmonized (same literal value) between Dem_ReturnClearDTCType and Std_ReturnType  */
        returnSts = (Dem_ReturnClearDTCType) Dem_SelectDTC(ClientId, DTC, DTCFormat, DTCOrigin);
    }

    if (returnSts == E_OK)
    {
        /* return values are harmonized (same literal value) between Dem_ReturnClearDTCType and Std_ReturnType  */
        returnSts = (Dem_ReturnClearDTCType)Dem_ClearDTC_4_3(ClientId);
    }

    return returnSts;
}

static void Dem_InvalidateSelectDTCParams(void)
{
    Dem_ClientIdType clientId;
    for (clientId = 1; clientId < DEM_CLIENTID_ARRAYLENGTH; clientId++)
    {
        (void) Dem_SelectDTC(clientId, DEM_INVALID_DTC, DEM_INVALID_DTC_FORMAT, DEM_INVALID_DTC_ORIGIN_MEMORY);
    }
}

void Dem_ClearDtcInit(void)
{
    Dem_InvalidateSelectDTCParams();
    Dem_ClientSelectionType_invalidateSelectionResult(&Dem_Client_getClient(DEM_CLIENTID_DCM)->selection);
}

boolean Dem_ClearIsInProgress (void)
{
    return (Dem_ClientClearMachine.machine_state == DEM_CLEAR_DTC_MACHINE_STATE_EXEC);
}

void Dem_DcmCancelOperation (void)
{
    Dem_InvalidateSelectDTCParams();
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

