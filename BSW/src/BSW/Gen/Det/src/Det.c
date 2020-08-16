

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Det.h"
#include "Rte_Det.h"
#include "Det_Cfg_SchM.h"
#include "Det_Prv.h"

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
#include "Dlt_Det.h"
#endif

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */
#define DET_START_SEC_RAM_CLEARED
#include "Det_MemMap.h"

boolean Det_Initialized_b;

#if (DET_CFG_ERRORBUFFER_ENABLED)
static uint16 Det_BufferIndex_u16;
Det_ErrorEntryBufferType Det_ErrorEntryBuffer[DET_CFG_ERRORBUFFERSIZE];
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED) */

#define DET_STOP_SEC_RAM_CLEARED
#include "Det_MemMap.h"

#define DET_START_SEC_ROM_CODE
#include "Det_MemMap.h"

/*
 **********************************************************************************************************************
 * Functions
 **********************************************************************************************************************
 */

/*
 **************************************************************************************************
 * Det_GetLastBufferIndex
 * Service to return the last used index of the Det Buffer.
 **************************************************************************************************
 */
#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetLastBufferIndex(Det_BufferIndexType* buffIdx)
{
    Std_ReturnType retval = E_NOT_OK;

    if (buffIdx == NULL_PTR)
    {
        /* No valid pointer */
        retval = DET_E_PARAM_POINTER;
    }
    else if (!(Det_Initialized_b))
    {
        /* Not initialized */
        retval = DET_E_UNAVAILABLE;
    }
    else if (Det_BufferIndex_u16 == 0)
    {
        /* No entry */
        retval = E_NOT_OK;
    }
    else
    {
        /* provide index of last buffer entry and return E_OK*/
        *buffIdx = Det_BufferIndex_u16 - 1;
        retval = E_OK;
    }
    return retval;
}
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED) */

/*
 **************************************************************************************************
 * Det_GetBufferEntry
 * Service to return the error entry stored in the buffer at position index.
 **************************************************************************************************
 */
#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetBufferEntry(Det_BufferIndexType buffIdx, Det_ErrorEntryBufferType* buffEntry)
{
    Std_ReturnType retval = E_NOT_OK;

    if (buffEntry == NULL_PTR)
    {
        /* No valid pointer */
        retval = DET_E_PARAM_POINTER;
    }
    else if ((!Det_Initialized_b))
    {
        /* Not initialized */
        retval = DET_E_UNAVAILABLE;
    }
    else if (Det_BufferIndex_u16 == 0)
    {
        /* No entry */
        retval = E_NOT_OK;
    }
    else if (buffIdx >= Det_BufferIndex_u16)
    {
        /* Invalid index*/
        retval = E_NOT_OK;
    }
    else
    {
        /* provide error entry information for given index and return E_OK*/
        *buffEntry = Det_ErrorEntryBuffer[buffIdx];
        retval = E_OK;
    }
    return retval;
}
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED) */

/*
 **************************************************************************************************
 * Det_Init
 * Service to initialize the Default Error Tracer.
 **************************************************************************************************
 */
void Det_Init(const Det_ConfigType* ConfigPtr)
{
    if (ConfigPtr != NULL_PTR)
    {
        /* Skip init execution */
        return;
    }
    /* Enter Interrupt Lock */
    SchM_Enter_Det_Monitoring()
    ;

#if (DET_CFG_ERRORBUFFER_ENABLED)
    DET_MEMSET(&Det_ErrorEntryBuffer[0], 0x00, sizeof(Det_ErrorEntryBuffer));
    Det_BufferIndex_u16 = 0;
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED) */
    Det_Initialized_b = TRUE;

    /* Exit Interrupt Lock */
    SchM_Exit_Det_Monitoring()
    ;
}

/*
 **************************************************************************************************
 * Det_Start
 * Service to start the Default Error Tracer.
 **************************************************************************************************
 */
void Det_Start(void)
{
#if (DET_CFG_ERRORBUFFER_ENABLED)
    /* Enter Interrupt Lock */
    SchM_Enter_Det_Monitoring();

    Det_BufferIndex_u16 = 0;

    /* Exit Interrupt Lock */
    SchM_Exit_Det_Monitoring();
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED) */
}

/*
 **************************************************************************************************
 * Det_GetVersionInfo
 * Returns the version information of this module.
 **************************************************************************************************
 */
#if (DET_CFG_VERSIONINFO_SUPPORTED)
void Det_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    if (versioninfo != NULL_PTR)
    {
        versioninfo->vendorID = DET_VENDOR_ID;
        versioninfo->moduleID = DET_MODULE_ID;
        versioninfo->sw_major_version = DET_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = DET_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = DET_SW_PATCH_VERSION;
    }
    else
    {
        /* throw the error DET_E_PARAM_POINTER */
        (void) Det_ReportError(DET_MODULE_ID, DET_INSTANCE_ID, DET_APIID_GETVERSIONINFO, DET_E_PARAM_POINTER);
    }
}
#endif

/*
 **************************************************************************************************
 * Det_ReportError
 * Service to report development errors.
 **************************************************************************************************
 */
/* MR12 RULE 8.3 VIOLATION: The names of parameters in this function declaration are different from the names in a previous declaration.
 * But this can be ignored, since the parameter names differ in RTE generated files */
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    /* Check if DET was initialized, otherwise exit direclty */
    if (!Det_Initialized_b)
    {
        DET_UNUSED_PARAM(ModuleId);
        DET_UNUSED_PARAM(InstanceId);
        DET_UNUSED_PARAM(ApiId);
        DET_UNUSED_PARAM(ErrorId);
    }
    else
    {
#if (DET_CFG_HOOKCOUNT > 0)
        DET_CFG_CALLERRORHOOKS(ModuleId, InstanceId, ApiId, ErrorId);
#endif /* #if (DET_CFG_HOOKCOUNT > 0) */

#if (DET_CFG_ERRORBUFFER_ENABLED)

        /* Enter Interrupt Lock */
        SchM_Enter_Det_Monitoring();

        /* Check if there are free place in Det_ErrorEntryBuffer, then enter the new Development error in the buffer*/
        if (Det_BufferIndex_u16 < (DET_CFG_ERRORBUFFERSIZE))
        {
            Det_ErrorEntryBuffer[Det_BufferIndex_u16].ModuleId = ModuleId;
            Det_ErrorEntryBuffer[Det_BufferIndex_u16].InstanceId = InstanceId;
            Det_ErrorEntryBuffer[Det_BufferIndex_u16].ApiId = ApiId;
            Det_ErrorEntryBuffer[Det_BufferIndex_u16].ErrorId = ErrorId;

            Det_BufferIndex_u16++;
        }
        /* Exit Interrupt Lock */
        SchM_Exit_Det_Monitoring();
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED) */

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
        Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
#endif /* #if (DET_CFG_FORWARDTODLT_SUPPORTED) */
    }
    return E_OK;
}

/*
 **************************************************************************************************
 * Det_ReportRuntimeError
 * Service to report runtime errors. If a callout has been configured then this callout shall
 * be called.
 **************************************************************************************************
 */
/* MR12 RULE 8.3 VIOLATION: The names of parameters in this function declaration are different from the names in a previous declaration.
 * But this can be ignored, since the parameter names differ in RTE generated files */
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
    /* Check if DET was initialized, otherwise exit direclty */
    if (!Det_Initialized_b)
    {
        DET_UNUSED_PARAM(ModuleId);
        DET_UNUSED_PARAM(InstanceId);
        DET_UNUSED_PARAM(ApiId);
        DET_UNUSED_PARAM(ErrorId);
    }
    else
    {
#if (DET_CFG_RUNTIMECALLOUT_SUPPORTED)
        DET_CFG_CALLRUNTIMECALLOUT(ModuleId, InstanceId, ApiId, ErrorId);
#endif

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
        Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, ErrorId);
#endif
    }
    return E_OK;
}

/*
 **************************************************************************************************
 * Det_ReportTransientFault
 * Service to report transient faults. If a callout has been configured then this callout shall
 * be called and the returned value of the callout shall be returned. Otherwise it returns
 * immediately with E_OK.
 **************************************************************************************************
 */
/* MR12 RULE 8.3 VIOLATION: The names of parameters in this function declaration are different from the names in a previous declaration.
 * But this can be ignored, since the parameter names differ in RTE generated files */
Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId)
{
    Std_ReturnType retval = E_OK;
    /* Check if DET was initialized, otherwise exit direclty */
    if (!Det_Initialized_b)
    {
        DET_UNUSED_PARAM(ModuleId);
        DET_UNUSED_PARAM(InstanceId);
        DET_UNUSED_PARAM(ApiId);
        DET_UNUSED_PARAM(FaultId);
    }
    else
    {
#if (DET_CFG_TRANSIENTCALLOUT_SUPPORTED)
        retval = DET_CFG_CALLTRANSIENTCALLOUT(ModuleId, InstanceId, ApiId, FaultId);
#endif

#if (DET_CFG_FORWARDTODLT_SUPPORTED)
        Dlt_DetForwardErrorTrace(ModuleId, InstanceId, ApiId, FaultId);
#endif
    }
    return retval;
}

#define DET_STOP_SEC_ROM_CODE
#include "Det_MemMap.h"

