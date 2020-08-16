

#include "Dem_Client.h"
#include "Dem_ClientHandlingTypes.h"
#include "Dem_ClientBaseHandling.h"
#include "Dem_ClientRequestDispatcher.h"
#include "Dem_ClientClearMachine.h"
#include "Dem_EvMemApi.h"
#include "Dem_DTCGroup.h"
#include "Dem_DTCs.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

static void Dem_ClientRequestDispatcher_transferSelectionErrorToResult(Dem_ClientIdType ClientId, Dem_ClientRequestType request)
{
    Dem_ClientResultType_setResult(&Dem_Clients[ClientId].result, request,
            Dem_ClientSelectionType_getSelectionResult(Dem_Clients[ClientId].selection));
    Dem_ClientSelectionType_invalidateSelectionResult(&Dem_Client_getClient(ClientId)->selection);
}

static void Dem_ClientRequestDispatcher_calculateSelection (Dem_ClientIdType ClientId)
{
    if (Dem_ClientSelectionType_isSelectionPending(Dem_Client_getClient(ClientId)->selection))
    {
        Dem_DtcIdType dtcId = DEM_DTCID_INVALID;
        uint8 typeOfSelection = DEM_CLIENT_SELECTION_TYPE_INVALID;
        Std_ReturnType selectionResult;

        if (!Dem_EvMemIsDtcOriginValid(&Dem_Client_getClient(ClientId)->DTCOrigin))
        {
            selectionResult = DEM_WRONG_DTCORIGIN;
        }
        else
        {
            if (Dem_Client_getClient(ClientId)->DTC == DEM_DTC_GROUP_ALL_DTCS)
            {
                typeOfSelection = DEM_CLIENT_SELECTION_TYPE_ALL_DTCS;
                selectionResult = E_OK;
            }
            else
            {
                if ( Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION) == Dem_LibGetParamUI8(DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS) )
                {
                    DEM_DET(DEM_DET_APIID_CLEARDTC, DEM_E_WRONG_CONFIGURATION);
                    selectionResult = DEM_WRONG_DTC;
                }
                else
                {
                    dtcId = Dem_DtcGroupIdFromDtcGroupCode(Dem_Client_getClient(ClientId)->DTC);
                    if (dtcId != DEM_DTCGROUPID_INVALID)
                    {
                        typeOfSelection = DEM_CLIENT_SELECTION_TYPE_GROUP_DTC;
                        selectionResult = E_OK;
                    }
                    else
                    {
                        dtcId = Dem_DtcIdFromDtcCode(Dem_Client_getClient(ClientId)->DTC);
                        if ((!Dem_DtcIsSupported(dtcId)) || (Dem_Client_getClient(ClientId)->DTCFormat == DEM_DTC_FORMAT_OBD))
                        {
                            selectionResult = DEM_WRONG_DTC;
                        }
                        else
                        {
                            typeOfSelection = DEM_CLIENT_SELECTION_TYPE_SINGLE_DTC;
                            selectionResult = E_OK;
                        }
                    }
                }
            }
        }
        Dem_ClientSelectionType_setSelection(&Dem_Client_getClient(ClientId)->selection, dtcId, typeOfSelection, selectionResult);
    }
}

void Dem_ClientRequestDispatcher_main(void)
{
    uint8 clientId;
    Dem_ClientRequestType tempRequest;
    boolean execute;

    for (clientId = 1; clientId < DEM_CLIENTID_ARRAYLENGTH; clientId++)
    {
        tempRequest = Dem_Clients[clientId].request;

        if (Dem_ClientRequestType_isRequestInProgress(clientId))
        {
            if ((Dem_ClientRequestType_isCancelRequested(tempRequest))
                    && (!(Dem_ClientClearMachine_isProcessingClient(clientId))))
            {
                Dem_ClientResultType_confirmCancel(&Dem_Clients[clientId].result, tempRequest);
            }
            else
            {
                execute = TRUE;
#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)
                if (clientId != DEM_CLIENTID_J1939)
#endif
                {
                    Dem_ClientRequestDispatcher_calculateSelection(clientId);

                    if (Dem_ClientSelectionType_getSelectionResult(Dem_Clients[clientId].selection) != E_OK)
                    {
                        Dem_ClientRequestDispatcher_transferSelectionErrorToResult(clientId, tempRequest);
                        execute = FALSE;
                    }
                }
                if (execute)
                {
                    if (Dem_ClientRequestType_getMachineIndex(tempRequest)
                            == (Dem_ClientRequestType_getMachineIndex(DEM_CLIENT_REQUEST_CLEAR)))
                    {
                        if ((!(Dem_ClientClearMachine_isProcessingClient(clientId)))
                                && (Dem_ClientClearMachine_GetMachineActiveClient() == DEM_CLIENTID_INVALID))
                        {
                            Dem_ClientClearMachine_SetClientRequest(clientId, DEM_CLEAR_DTC_MACHINE_STATE_EXEC);
                        }
                        else
                        {
                            if (Dem_ClientClearMachine_GetMachineActiveClient() != clientId)
                            {
                                Dem_ClientResultType_setResult(&Dem_Client_getClient(clientId)->result, tempRequest,
                                DEM_CLEAR_BUSY);
                            }
                        }
                    }
                }
            }
        }
    }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
