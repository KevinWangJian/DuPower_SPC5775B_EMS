

#include "Dem_Client.h"
#include "Dem_ClientHandlingTypes.h"
#include "Dem_ClientBaseHandling.h"
#include "Dem_ClientClearMachine.h"
#include "Dem_ClientRequestDispatcher.h"
#include "Dem_Clear.h"
#include "Dem_Nvm.h"
#include "Dem_Lock.h"
#include "Dem_Cfg_EvMem.h"
#include "Dem_Cfg_ExtPrototypes.h"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

DEM_ARRAY_DEFINE (Dem_ClientType, Dem_Clients, DEM_CLIENTID_ARRAYLENGTH);

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

Dem_ClientType* Dem_Client_getClient (Dem_ClientIdType ClientId)
{
    return (&Dem_Clients[ClientId]);
}

/**************************************************************************************************/
/****************  Dem_SelectDTC ******************************************************************/

static void Dem_Client_SetParameters(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    Dem_Clients[ClientId].DTC       = DTC;
    Dem_Clients[ClientId].DTCFormat = DTCFormat;
    Dem_Clients[ClientId].DTCOrigin = DTCOrigin;
}

static void Dem_Client_SetClientState(Dem_ClientIdType ClientId, uint8 state)
{
    Dem_Clients[ClientId].client_state = state;
}

static uint8 Dem_Client_GetClientState(Dem_ClientIdType ClientId)
{
    return Dem_Clients[ClientId].client_state;
}

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
static void Dem_Client_SetJ1939Parameters(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node, uint8 ClientId)
{
    Dem_Clients[ClientId].J1939DTCTypeFilter    = DTCTypeFilter;
    Dem_Clients[ClientId].J1939node             = node;
}

static Std_ReturnType Dem_SelectJ1939Parameters(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node, uint8 ClientId)
{
    /* Set the Client Parameters */
    if (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_INIT)
    {
        if (!(Dem_ClientRequestType_isRequestInProgress(ClientId)))
        {
            Dem_Client_SetJ1939Parameters(DTCTypeFilter, node, ClientId);
            Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_PARAMETERS_SET);
            return E_OK;
        }
        else
        {
            return DEM_BUSY;
        }
    }
    else if (((Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_PARAMETERS_SET))
            && !(Dem_ClientRequestType_isRequestInProgress(ClientId)))
    {
        Dem_Client_SetJ1939Parameters(DTCTypeFilter, node, ClientId);
        Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_PARAMETERS_SET);
        return E_OK;
    }
    else if (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_REQUESTED_OPERATION)
    {
        Dem_ClientRequestType_cancelRequest(&Dem_Clients[ClientId].request);
        Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_INIT);
        return DEM_BUSY;
    }
    else
    {
        /* should never occur */
        DEM_ASSERT(Dem_LibGetParamBool(FALSE), DEM_DET_APIID_DEM_SELECTDTC, 0);
        return DEM_BUSY;
    }
}
#endif

Std_ReturnType Dem_SelectDTC(uint8 ClientId, uint32 DTC, Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
    if (!Dem_isClientIdValid(ClientId))
    {
        return DEM_WRONG_CLIENTID;
    }

    /* To Adapt to AR4.2 */
    if (DTCOrigin == DEM_DTC_ORIGIN_USERDEFINED_MEMORY)
    {
        DTCOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
    }

    /* Set the Client Parameters */
    if (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_INIT)
    {
        if (!(Dem_ClientRequestType_isRequestInProgress(ClientId)))
        {
            Dem_Client_SetParameters(ClientId, DTC, DTCFormat, DTCOrigin);
            Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_PARAMETERS_SET);
            return E_OK;
        }
        else
        {
            return DEM_BUSY;
        }
    }
    else if (((Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_PARAMETERS_SET))
            && !(Dem_ClientRequestType_isRequestInProgress(ClientId)))
    {
        Dem_Client_SetParameters(ClientId, DTC, DTCFormat, DTCOrigin);
        Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_PARAMETERS_SET);
        return E_OK;
    }
    else if (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_REQUESTED_OPERATION)
    {
        Dem_ClientRequestType_cancelRequest(&Dem_Clients[ClientId].request);
        Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_INIT);
        return DEM_BUSY;
    }
    else
    {
        /* should never occur */
        DEM_ASSERT(Dem_LibGetParamBool(FALSE), DEM_DET_APIID_DEM_SELECTDTC, 0);
        return DEM_BUSY;
    }
}

/**************************************************************************************************/
/****************  ClearDTC **********************************************************************/

Std_ReturnType Dem_ClearDTC_4_3(uint8 ClientId)
{
    if (!Dem_isClientIdValid(ClientId))
    {
        return DEM_WRONG_CLIENTID;
    }

    if (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_PARAMETERS_SET)
    {
        Dem_ClientRequestType_setRequest(&Dem_Clients[ClientId].request, DEM_CLIENT_REQUEST_CLEAR);
        Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_REQUESTED_OPERATION);

        return DEM_CLEAR_PENDING;
    }
    else if ((Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_REQUESTED_OPERATION)
            || (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_INIT))
    {
        if (!(Dem_ClientRequestType_isRequestInProgress(ClientId)))
        {
            Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_PARAMETERS_SET);
            return Dem_ClientResultType_getResult(Dem_Clients[ClientId].result);
        }
        else
        {
            return DEM_CLEAR_PENDING;
        }
    }
    else
    {
        /* should never occur */
        DEM_ASSERT(Dem_LibGetParamBool(FALSE), DEM_DET_APIID_CLEARDTC, 0);
        return DEM_CLEAR_FAILED;
    }
}

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)

static boolean Dem_J1939DcmIsDTCTypeFilterValid(Dem_J1939DcmSetClearFilterType DTCTypeFilter)
{
    return ((DTCTypeFilter == DEM_J1939DTC_CLEAR_ALL) || (DTCTypeFilter == DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE));
}

static boolean Dem_Client_AreJ1939ParametersAlreadyRequested(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node, uint8 ClientId)
{
    return ((Dem_Clients[ClientId].J1939DTCTypeFilter == DTCTypeFilter) && (Dem_Clients[ClientId].J1939node == node));
}

Std_ReturnType Dem_J1939DcmClearDTC_4_3(Dem_J1939DcmSetClearFilterType DTCTypeFilter, uint8 node, uint8 ClientId)
{
    Std_ReturnType returnSts = E_OK;

    if (!Dem_isClientIdValid(ClientId))
    {
        return DEM_WRONG_CLIENTID;
    }

    if (!Dem_J1939DcmIsDTCTypeFilterValid(DTCTypeFilter))
    {
        return DEM_CLEAR_FAILED;
    }

    if (!Dem_J1939DcmIsNodeIdValid(node))
    {
        return DEM_CLEAR_FAILED;
    }

    if (!Dem_Client_AreJ1939ParametersAlreadyRequested(DTCTypeFilter, node, ClientId))
    {
        returnSts = Dem_SelectJ1939Parameters(DTCTypeFilter, node, ClientId);
        if (returnSts != E_OK)
        {
            return returnSts;
        }
    }

    if (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_PARAMETERS_SET)
    {
        Dem_ClientRequestType_setRequest(&Dem_Clients[ClientId].request, DEM_CLIENT_REQUEST_CLEAR);
        Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_REQUESTED_OPERATION);

        return DEM_CLEAR_PENDING;
    }
    else if ((Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_REQUESTED_OPERATION)
            || (Dem_Client_GetClientState(ClientId) == DEM_CLIENT_STATE_INIT))
    {
        if (!(Dem_ClientRequestType_isRequestInProgress(ClientId)))
        {
            Dem_Client_SetClientState(ClientId, DEM_CLIENT_STATE_PARAMETERS_SET);
            return Dem_ClientResultType_getResult(Dem_Clients[ClientId].result);
        }
        else
        {
            return DEM_CLEAR_PENDING;
        }
    }
    else
    {
        /* should never occur */
        DEM_ASSERT(Dem_LibGetParamBool(FALSE), DEM_DET_APIID_DEM_J1939DcmClearDTC, 0);
        return DEM_CLEAR_FAILED;
    }
}

#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
