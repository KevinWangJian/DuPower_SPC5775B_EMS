

/**
 **************************************************************************************************
 * FiM_Monitor.c
 * source for background monitor of Function Inhibition Manager
 * (only used with LARGE / RUNTIME optimal configuration
 **************************************************************************************************
 */

#include "FiM_Priv_Data.h"

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)

#include "Dem.h"
#include "FiM.h"
#include "Rte_FiM.h"
#include "FiM_Utils.h"
#include "FiM_Det.h"
#include "FiM_Status.h"
#include "Std_Types.h"
#include "FiM_Monitor.h"
#include "FiM_Init.h"
#include "FiM_Cfg_SchM.h"
#include "FiM_Cfg_Callback.h"

/**
 **************************************************************************************************
 * local defines
 **************************************************************************************************
 */

/**
 **************************************************************************************************
 * global variables
 **************************************************************************************************
 */

#define FIM_START_SEC_RAM_INIT
#include "FiM_MemMap.h"
/* Variable to store the State of the monitoring state machine */
static FiM_Priv_MonitorStateType FiM_Priv_MonitorState_e = FIM_PRIV_MONSTATE_INIT;
/* Variable to store the Current Monitoring FID */
#if (FIM_FIDPERMISSION_CALLBACK_SUPPORTED != FIM_FIDPERMISSION_CALLBACK_SUPPORTED_OFF)
static FiM_FunctionIdType FiM_Priv_CurrentMonitoringFId_uo = 1;
#endif
/* Variable to store the Current Monitoring Event Id */
static Dem_EventIdType FiM_Priv_CurrentMonitoringEventId_uo = 1;
/* Variable to store the Current Monitoring Component Id */
static Dem_ComponentIdType FiM_Priv_CurrentMonitoringComponentId_uo = 1;
#define FIM_STOP_SEC_RAM_INIT
#include "FiM_MemMap.h"

/* cyclic monitoring process is called in the FiM_MainFunction */

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

LOCAL_INLINE void FiM_Priv_MonitorProc_Init(void)
{
    FIM_PRIV_ENTERLOCK_MONITOR();

    /* Switch CURRENT and LAST Index of the two bit arrays */
    if (FiM_CurrentIdx == 0)
    {
        FiM_LastIdx = 0;
        FiM_CurrentIdx = 1;
    }
    else
    {
        FiM_LastIdx = 1;
        FiM_CurrentIdx = 0;
    }

    FIM_PRIV_EXITLOCK_MONITOR();

    /* Reset the CURRENT bit array to Zero */
    FIM_MEMSET(FiM_FIdStatusBitArray_au8[FiM_CurrentIdx], FIM_PRIV_ZERO,
            sizeof(FiM_FIdStatusBitArray_au8[FiM_CurrentIdx]));
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
    FIM_MEMSET(FiM_FIdStatusServ07BitArray_au8[FiM_CurrentIdx], FIM_PRIV_ZERO,
            sizeof(FiM_FIdStatusServ07BitArray_au8[FiM_CurrentIdx]));
#endif
    /* Initialize the values for state CHECK. */
    FiM_Priv_CurrentMonitoringEventId_uo = 1;
    FiM_Priv_CurrentMonitoringComponentId_uo = 1;

    /* Transit to next state CHECK. */
    FiM_Priv_MonitorState_e = FIM_PRIV_MONSTATE_CHECK;
}


LOCAL_INLINE void FiM_Priv_MonitorProc_CheckEvent(Dem_EventIdType eventId)
{
    uint32 idxFidOffset_u32;
    uint32 idxEnd_u32;
    FiM_FunctionIdType FId_uo;
    uint8 demExtendedEventStatus_u8;
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
    Dem_DTCKindType dtcKind = DEM_DTC_KIND_ALL_DTCS;
    uint8 inhMaskConfig_uo = 0;
#endif

    /* Ask for the event status */
    if (Dem_GetEventStatus(eventId, &demExtendedEventStatus_u8) == E_OK)
    {
        if (FiM_ConfigParam_pcs != NULL_PTR)
        {
            idxEnd_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[eventId + 1]);
            idxFidOffset_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[eventId]);

            /* loop through all FIds attached to the event and check configured inhibit mask */
            while (idxFidOffset_u32 < idxEnd_u32)
            {
                /* Get the Inhibited Fid from the inhibition source matrix */
                FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixptr[idxFidOffset_u32]);
                /* if new inhibit situation is a match: lock that particular Fid */
                if (FiM_Priv_IsInhibitionSet(demExtendedEventStatus_u8,
                        (FiM_ConfigParam_pcs->FiM_CfgInhibitMaskMatrixptr[idxFidOffset_u32])))
                {
                    /* Set the CURRENT bit array to 1 for fulfilled inhibitions */
                    FiM_Priv_SetInhStatus(FId_uo);
                }

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
                if (Dem_GetDtcKindOfEvent(eventId, &dtcKind) == E_OK)
                {
                    if (dtcKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
                    {
                        /* Calculate service$07 entry for event */
                        inhMaskConfig_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitMaskMatrixptr[idxFidOffset_u32]);

                        if ((FiM_Priv_IsInhMaskServ07Relevant(inhMaskConfig_uo))
                                && ((demExtendedEventStatus_u8 & FIM_PENDING_BITS_MASK) == FIM_PENDING_BITS_MASK))
                        {
                            /* if EVENT is visible in service$07 then increment counter for FId */
                            FiM_Priv_SetServ07InhStatus(FId_uo);
                        }
                    }
                }
#endif
                /* Increment the Fid Offset by 1*/
                idxFidOffset_u32++;
            }
        }
        else
        {
            FIM_PRIV_DET_ERROR(FIM_PRIV_MONITOR_ID, FIM_E_PARAM_POINTER);
        }
    }
}

#if (FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC != 0)
LOCAL_INLINE void FiM_Priv_MonitorProc_CheckComponent(Dem_ComponentIdType componentId)
{
    uint32 idxFidOffset_u32;
    uint32 idxEnd_u32;
    FiM_FunctionIdType FId_uo;
    boolean demComponentFailed_b;

    /* Ask for the component failed */
    if (Dem_GetComponentFailed(componentId, &demComponentFailed_b) == E_OK)
    {
        if (demComponentFailed_b)
        {
            if (FiM_ConfigParam_pcs != NULL_PTR)
            {
                idxEnd_u32 =
                (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[componentId + 1]);
                idxFidOffset_u32 =
                (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[componentId]);

                /* loop through all FIds attached to the component and update inhibitions */
                while (idxFidOffset_u32 < idxEnd_u32)
                {
                    /* Get the Inhibited Fid from the inhibition source matrix */
                    FId_uo =
                    (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixComponentptr[idxFidOffset_u32]);

                    /* Set the CURRENT bit array to 1 for fulfilled inhibitions */
                    FiM_Priv_SetInhStatus(FId_uo);

                    /* Increment the Fid Offset by 1*/
                    idxFidOffset_u32++;
                }
            }
            else
            {
                FIM_PRIV_DET_ERROR(FIM_PRIV_MONITOR_ID, FIM_E_PARAM_POINTER);
            }
        }
    }
}
#endif

LOCAL_INLINE void FiM_Priv_MonitorProc_Check(void)
{
    uint32 numberOfLinksToCheck = FIM_PRIV_LINKSPERMONITORCHECK;

    while (numberOfLinksToCheck > 0u)
    {
        numberOfLinksToCheck--;

        if (FiM_Priv_CurrentMonitoringEventId_uo <= FIM_CFG_NUMBEROFDEMEVENTIDS)
        {
            /* Not all event Ids queried, proceed ... */
            FiM_Priv_MonitorProc_CheckEvent(FiM_Priv_CurrentMonitoringEventId_uo);
            FiM_Priv_CurrentMonitoringEventId_uo++;
        }
#if (FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC != 0)
        else
        {
            if (FiM_Priv_CurrentMonitoringComponentId_uo <= FIM_CFG_NUMBEROFDEMCOMPONENTIDS)
            {
                /* Not all component Ids queried, proceed ... */
                FiM_Priv_MonitorProc_CheckComponent(FiM_Priv_CurrentMonitoringComponentId_uo);
                FiM_Priv_CurrentMonitoringComponentId_uo++;
            }
        }
#endif

        if ((FiM_Priv_CurrentMonitoringEventId_uo > FIM_CFG_NUMBEROFDEMEVENTIDS)
#if (FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC != 0)
        && (FiM_Priv_CurrentMonitoringComponentId_uo > FIM_CFG_NUMBEROFDEMCOMPONENTIDS)
#endif
        )
        {
#if(FIM_FIDPERMISSION_CALLBACK_SUPPORTED != FIM_FIDPERMISSION_CALLBACK_SUPPORTED_OFF)
            /* Init values for state CALLBACK. */
            FiM_Priv_CurrentMonitoringFId_uo = 1;
            /* Transit to next state CALLBACK. */
            FiM_Priv_MonitorState_e = FIM_PRIV_MONSTATE_CALLBACK;
#else
            /* Transit to next state INIT. */
            FiM_Priv_MonitorState_e = FIM_PRIV_MONSTATE_INIT;
#endif
            break;
        }

    } /* while (numberOfEvents)*/
}

#if(FIM_FIDPERMISSION_CALLBACK_SUPPORTED != FIM_FIDPERMISSION_CALLBACK_SUPPORTED_OFF)
LOCAL_INLINE void FiM_Priv_MonitorProc_Callback(void)
{
    FiM_FunctionIdType FId_uo;
    FiM_FunctionIdType Fid_BytePosition_u0;
    uint8 Fid_BitPosition_u8;
    uint8 Fid_BitMask_u8;
    boolean Fid_NewPermission;
    boolean Fid_OldPermission;

    uint16_least numberOfFIds_u16 = FIM_PRIV_FIDSPERMONITORCALLBACK;

    /* Start processing subset of FIDs */
    while (numberOfFIds_u16 > 0u)
    {
        numberOfFIds_u16--;
        /* Get the Current monitoring Fid into a LOcal variable */
        FId_uo = FiM_Priv_CurrentMonitoringFId_uo;
        /* Calculate the Fid Byte position */
        Fid_BytePosition_u0 = (FId_uo / 8);
        /* Calculate the Fid bit position */
        Fid_BitPosition_u8 = (uint8) (FId_uo % 8);
        /* Calculate the Bit mask */
        Fid_BitMask_u8 = (uint8) (1u << Fid_BitPosition_u8);

        /* Checking the new permission state of that Particular FID */
        if (((FiM_FIdStatusBitArray_au8[FiM_CurrentIdx][Fid_BytePosition_u0]) & Fid_BitMask_u8) == 0)
        {
            Fid_NewPermission = TRUE;
        }
        else
        {
            Fid_NewPermission = FALSE;
        }

        /* Checking the old permission status of that particular FID */
        if (((FiM_FIdStatusBitArray_au8[FiM_LastIdx][Fid_BytePosition_u0]) & Fid_BitMask_u8) == 0)
        {
            Fid_OldPermission = TRUE;
        }
        else
        {
            Fid_OldPermission = FALSE;
        }

        /* Compare the LAST and CURRENT bit array to detect the inhibition status */
        if (Fid_NewPermission != Fid_OldPermission)
        {
            /* Invoke the callback function for that particular Fid */
            FIM_USE_VAR(
                    FIM_FIDPERMISSION_ST_CH_CALLBACK_FUNCTION(FId_uo, Fid_OldPermission, Fid_NewPermission));
        }

        /* Increment the Current monitoring Fid by 1 */
        FiM_Priv_CurrentMonitoringFId_uo++;

        /* If all FIds are processed in state CALLBACK. */
        if (FiM_Priv_CurrentMonitoringFId_uo > FIM_CFG_NUMBEROFFIDS)
        {
            /* Transit to next state INIT. */
            FiM_Priv_MonitorState_e = FIM_PRIV_MONSTATE_INIT;

            break;
        }
    }
}
#endif

void FiM_Priv_MonitorProc(void)
{
    switch (FiM_Priv_MonitorState_e)
    {
        case FIM_PRIV_MONSTATE_INIT:
            FiM_Priv_MonitorProc_Init();
            break;

        case FIM_PRIV_MONSTATE_CHECK:
            FiM_Priv_MonitorProc_Check();
            break;

#if(FIM_FIDPERMISSION_CALLBACK_SUPPORTED != FIM_FIDPERMISSION_CALLBACK_SUPPORTED_OFF)
        case FIM_PRIV_MONSTATE_CALLBACK:
            FiM_Priv_MonitorProc_Callback();
            break;
#endif
        default:
            // detect development errors / plausibility checks
            FIM_PRIV_DET_ERROR(FIM_PRIV_MONITOR_ID, FIM_E_MONITORSTATE_INVALID);
            /* Transit to next state INIT */
            FiM_Priv_MonitorState_e = FIM_PRIV_MONSTATE_INIT;
            break;
    }
}

/* functions are only required by test cases */
#ifdef FIM_UNIT_TEST_SUITE
/* returns the state of the monitoring state machine */
FiM_Priv_MonitorStateType FiM_Priv_MonitorGetState(void)
{
    return FiM_Priv_MonitorState_e;
}

/* set the state of the monitoring state machine */
void FiM_Priv_MonitorSetState(FiM_Priv_MonitorStateType newState)
{
    FiM_Priv_MonitorState_e = newState;
}
#endif

/* initialize the monitoring state machine only during FiM_Init */
void FiM_Priv_MonitorInit(void)
{
    /* Protection locks are not required as this function is called only during Init */
    FiM_Priv_MonitorState_e = FIM_PRIV_MONSTATE_INIT;
    FiM_LastIdx = 0;
    FiM_CurrentIdx = 1;
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif /* FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF */

