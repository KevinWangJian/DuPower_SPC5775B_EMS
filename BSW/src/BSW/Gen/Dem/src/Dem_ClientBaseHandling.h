

#ifndef DEM_CLIENTBASEHANDLING_H
#define DEM_CLIENTBASEHANDLING_H

#include "Dem_ClientHandlingTypes.h"
#include "Dem_Client.h"
#include "Dem_Lib.h"


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/**************************************************************************************************/
/*********  MASKS : Dem_ClientRequestType, Dem_ClientResultType & Dem_ClientSelectionType *********/

#define DEM_CLIENT_TYPE_MASK     0xFFu

/**************************************************************************************************/
/****************  MASKS : Dem_ClientRequestType & Dem_ClientResultType ***************************/

#define DEM_CLIENT_REQUEST_RESULT_IDMASK       0xFF00u

/**************************************************************************************************/
/****************  Dem_ClientResultType  **********************************************************/

DEM_INLINE void Dem_ClientResultType_setResult(volatile Dem_ClientResultType *result, Dem_ClientRequestType request, Std_ReturnType newResult)
{
    Dem_ClientResultType tempResult;

    DEM_STATIC_ASSERT(((DEM_SIZEOF_TYPE(Dem_ClientResultType)) >= 2u), DEM_CLIENTRSULTTYPE_SHALL_BE_UINT16);

    tempResult = (request & DEM_CLIENT_REQUEST_RESULT_IDMASK);
    tempResult |= newResult;
    *result = tempResult;
}

DEM_INLINE Std_ReturnType Dem_ClientResultType_getResult(Dem_ClientResultType result)
{
    return ((Std_ReturnType)(result & DEM_CLIENT_TYPE_MASK));
}

DEM_INLINE void Dem_ClientResultType_confirmCancel(volatile Dem_ClientResultType *result, Dem_ClientRequestType request)
{
    Dem_ClientResultType tempResult;

    DEM_STATIC_ASSERT(((DEM_SIZEOF_TYPE(Dem_ClientResultType)) >= 2u), DEM_CLIENTRSULTTYPE_SHALL_BE_UINT16);

    tempResult = (request & DEM_CLIENT_REQUEST_RESULT_IDMASK);
    tempResult |= DEM_FAILED;
    *result = tempResult;
}

/**************************************************************************************************/
/****************  Dem_ClientRequestType  *********************************************************/

#define DEM_CLIENT_REQUEST_TYPE_CANCEL_MASK     0x01u

DEM_INLINE boolean Dem_ClientRequestType_isRequestInProgress(Dem_ClientIdType clientId)
{
    return ((Dem_Clients[clientId].request & DEM_CLIENT_REQUEST_RESULT_IDMASK)
            != (Dem_Clients[clientId].result & DEM_CLIENT_REQUEST_RESULT_IDMASK));
}

DEM_INLINE void Dem_ClientRequestType_setRequest(volatile Dem_ClientRequestType *request, uint8 newRequest)
{
    Dem_ClientRequestType tempRequest;

    DEM_STATIC_ASSERT(((DEM_SIZEOF_TYPE(Dem_ClientRequestType) >= 2u)), DEM_CLIENTREQUESTTYPE_SHALL_BE_UINT16);

    tempRequest = *request;
    tempRequest += 0x0100u;
    tempRequest = (tempRequest & DEM_CLIENT_REQUEST_RESULT_IDMASK) | newRequest;
    *request = tempRequest;
}

DEM_INLINE void Dem_ClientRequestType_cancelRequest(volatile Dem_ClientRequestType *request)
{
    Dem_ClientRequestType tempRequest;

    DEM_STATIC_ASSERT(((DEM_SIZEOF_TYPE(Dem_ClientRequestType) >= 2u)), DEM_CLIENTREQUESTTYPE_SHALL_BE_UINT16);

    tempRequest = *request;
    tempRequest += 0x0101u;
    *request = tempRequest;
}

DEM_INLINE uint8 Dem_ClientRequestType_getMachineIndex(Dem_ClientRequestType request)
{
    uint8 machineIndex;
    machineIndex = (((uint8)(request & DEM_CLIENT_TYPE_MASK)) >> 1u);
    return machineIndex;
}

DEM_INLINE boolean Dem_ClientRequestType_isCancelRequested(Dem_ClientRequestType request)
{
    return ((request & DEM_CLIENT_REQUEST_TYPE_CANCEL_MASK) == 1u);
}

/**************************************************************************************************/
/****************  Dem_ClientSelectionType  *******************************************************/

#define DEM_CLIENT_SELECTION_DTCINDEXMASK                0xFFFFu
#define DEM_CLIENT_INVALIDATE_SELECTION_IDMASK           0x00FFFFFFu
#define DEM_CLIENT_SELECTION_TYPE_BITPOS_SELECTION_TYPE  16u
#define DEM_CLIENT_SELECTION_TYPE_BITPOS_RESULT          24u

DEM_INLINE uint16 Dem_ClientSelectionType_getSelectionDtcIndex (Dem_ClientSelectionType selection)
{
    return ((uint16)(selection & DEM_CLIENT_SELECTION_DTCINDEXMASK));
}

DEM_INLINE void Dem_ClientSelectionType_setSelection (Dem_ClientSelectionType *selection, uint16 dtcId, uint8 typeOfSelection, Std_ReturnType selectionResult)
{
    Dem_ClientSelectionType tempSelection;

    DEM_STATIC_ASSERT(((DEM_SIZEOF_TYPE(Dem_ClientSelectionType) >= 4u)), DEM_CLIENTSELECTIONTYPE_SHALL_BE_UINT32);

    tempSelection = (((uint32)dtcId) | (((uint32)typeOfSelection) << DEM_CLIENT_SELECTION_TYPE_BITPOS_SELECTION_TYPE) | (((uint32)selectionResult) << DEM_CLIENT_SELECTION_TYPE_BITPOS_RESULT));
    *selection = tempSelection;
}

DEM_INLINE boolean Dem_ClientSelectionType_isSelectionSingleDTC (Dem_ClientSelectionType selection)
{
    uint8 tempSelectionType;
    tempSelectionType = (uint8)((selection >> DEM_CLIENT_SELECTION_TYPE_BITPOS_SELECTION_TYPE) & DEM_CLIENT_TYPE_MASK);

    return (tempSelectionType == DEM_CLIENT_SELECTION_TYPE_SINGLE_DTC);
}

DEM_INLINE boolean Dem_ClientSelectionType_isSelectionDTCGroupAll (Dem_ClientSelectionType selection)
{
    uint8 tempSelectionType;
    tempSelectionType = (uint8)((selection >> DEM_CLIENT_SELECTION_TYPE_BITPOS_SELECTION_TYPE) & DEM_CLIENT_TYPE_MASK);

    return (tempSelectionType == DEM_CLIENT_SELECTION_TYPE_ALL_DTCS);
}

DEM_INLINE boolean Dem_ClientSelectionType_isSelectionDTCGroup (Dem_ClientSelectionType selection)
{
    uint8 tempSelectionType;
    tempSelectionType = (uint8)((selection >> DEM_CLIENT_SELECTION_TYPE_BITPOS_SELECTION_TYPE) & DEM_CLIENT_TYPE_MASK);

    return (tempSelectionType == DEM_CLIENT_SELECTION_TYPE_GROUP_DTC);
}

DEM_INLINE boolean Dem_ClientSelectionType_isSelectionPending (Dem_ClientSelectionType selection)
{
    uint8 tempSelectionResult;
    tempSelectionResult = (uint8)((selection >> DEM_CLIENT_SELECTION_TYPE_BITPOS_RESULT) & DEM_CLIENT_TYPE_MASK);

    return (tempSelectionResult == DEM_PENDING);
}

DEM_INLINE void Dem_ClientSelectionType_invalidateSelectionResult (Dem_ClientSelectionType *selection)
{
    Std_ReturnType tempresult = DEM_PENDING;
    Dem_ClientSelectionType tempSelection;

    DEM_STATIC_ASSERT(((DEM_SIZEOF_TYPE(Dem_ClientSelectionType) >= 4u)), DEM_CLIENTSELECTIONTYPE_SHALL_BE_UINT32);

    tempSelection = (*selection & DEM_CLIENT_INVALIDATE_SELECTION_IDMASK);
    tempSelection |= (((uint32)tempresult) << DEM_CLIENT_SELECTION_TYPE_BITPOS_RESULT);
    *selection = tempSelection;
}

DEM_INLINE Std_ReturnType Dem_ClientSelectionType_getSelectionResult (Dem_ClientSelectionType selection)
{
    return ((Std_ReturnType)((selection >> DEM_CLIENT_SELECTION_TYPE_BITPOS_RESULT) & DEM_CLIENT_TYPE_MASK));
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif
