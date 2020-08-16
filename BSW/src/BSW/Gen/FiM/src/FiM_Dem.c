

/**
 **************************************************************************************************
 * FiM_Dem.c
 * Interface functions to Dem for Function Inhibition Manager, i.e. FiM_DemTriggerOnEventStatus()
 * Design specification: AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 **************************************************************************************************
 */

#include "FiM_Init.h"
#include "FiM.h"
#include "Dem.h"
#include "FiM_Det.h"
#include "FiM_Status.h"
#include "FiM_Monitor.h"
#include "FiM_Cfg_SchM.h"

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

static boolean FiM_Dem_IsInitialized(void)
{
    boolean retVal = FALSE;
    if (FiM_Priv_GetStatusInitialized())
    {
        /* Check whether the Re-initialization is completed */
        if (FiM_Priv_IsDemInitCalled())
        {
            retVal = TRUE;
        }
        else /* FiM is not yet Re-initialized */
        {
            FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_DEMINIT_NOT_CALLED);
        }
    }
    else /* detect development errors / plausibility checks */
    {
        FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_NOT_INITIALIZED);
    }
    return retVal;
}

/**
 **************************************************************************************************
 * FiM_Dem_TriggerOnEventStatus (public API)
 **************************************************************************************************
 */
void FiM_DemTriggerOnEventStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType EventStatusOld,
        Dem_UdsStatusByteType EventStatusNew)
{
    uint32 idxFidOffset_u32 = 0;
    uint32 idxEnd_u32 = 0;
    FiM_FunctionIdType FId_uo = 0;
    FiM_InhibitionMaskType inhMaskConfig_uo = 0;
    boolean inhMaskChanged_b = FALSE;
    boolean inhMaskSet_b = FALSE;
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
    boolean serv07MaskChanged_b = FALSE;
    Dem_DTCKindType dtcKind = DEM_DTC_KIND_ALL_DTCS;
#endif

    if (FiM_Dem_IsInitialized())
    {
        if ((EventId <= FIM_CFG_NUMBEROFDEMEVENTIDS) && (EventId > 0))
        {
            inhMaskChanged_b = (((EventStatusOld & FIM_INHIBITION_BITS_MASK)
                    ^ (EventStatusNew & FIM_INHIBITION_BITS_MASK)) != 0u);

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
            if (Dem_GetDtcKindOfEvent(EventId, &dtcKind) == E_OK)
            {
                if (dtcKind == DEM_DTC_KIND_EMISSION_REL_DTCS)
                {
                    /* Calculation of service$07 visibility entry*/
                    serv07MaskChanged_b = (((EventStatusOld & FIM_PENDING_BITS_MASK)
                            ^ (EventStatusNew & FIM_PENDING_BITS_MASK)) != 0u);
                }
            }
#endif

            /* Did the inhibition relevant bits change at all? */
            if ((inhMaskChanged_b)
#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
                    || (serv07MaskChanged_b)
#endif
                    )
            {
                if (FiM_ConfigParam_pcs != NULL_PTR)
                {
                    idxEnd_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[EventId + 1]);
                    idxFidOffset_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetEventptr[EventId]);

                    /* loop through all FIds attached to the event */
                    while (idxFidOffset_u32 < idxEnd_u32)
                    {
                        FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixptr[idxFidOffset_u32]);
                        inhMaskConfig_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitMaskMatrixptr[idxFidOffset_u32]);

                        /* did the inhibition bits of the configured mask change? */
                        if (inhMaskChanged_b)
                        {
                            if ((FiM_Priv_IsInhibitionChanged(EventStatusNew, EventStatusOld, inhMaskConfig_uo,
                                    &inhMaskSet_b)))
                            {
                                if (inhMaskSet_b)
                                {
                                    /* if FAILED, increment counter and lock FId */
                                    FiM_Priv_FIdCountInc(FId_uo);
                                }
                                else
                                {
                                    /* if NOT FAILED, decrement counter and check whether lock can be released */
                                    FiM_Priv_FIdCountDec(FId_uo);
                                }
                            }
                        }

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
                        if (serv07MaskChanged_b)
                        {
                            if (FiM_Priv_IsInhMaskServ07Relevant(inhMaskConfig_uo))
                            {
                                /* Calculate service$07 entry for event */
                                if ((EventStatusNew & FIM_PENDING_BITS_MASK) == FIM_PENDING_BITS_MASK)
                                {
                                    /* if EVENT is visible in service$07 then increment counter for FId */
                                    FiM_Priv_FIdServ07CountInc(FId_uo);
                                }
                                else
                                {
                                    /* if EVENT is visible in service$07 then decrement counter for FId */
                                    FiM_Priv_FIdServ07CountDec(FId_uo);
                                }
                            }
                        }
#endif
                        idxFidOffset_u32++;
                    }
                }
                else
                {
                    FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_PARAM_POINTER);
                }
            }
        }
        /* detect development errors / plausibility checks */
        else
        {
            FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_EVENTID_OUT_OF_RANGE);
        }
    }
}

/**
 **************************************************************************************************
 * FiM_DemTriggerOnComponentStatus (public API)
 **************************************************************************************************
 */
void FiM_DemTriggerOnComponentStatus(Dem_ComponentIdType ComponentId, boolean ComponentFailedStatus)
{
#if (FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC == 0)
    FIM_USE_VAR(ComponentId);
    FIM_USE_VAR(ComponentFailedStatus);
#else
    uint32 idxFidOffset_u32 = 0;
    uint32 idxEnd_u32 = 0;
    FiM_FunctionIdType FId_uo = 0;

    if (FiM_Dem_IsInitialized())
    {
        if ((ComponentId <= FIM_CFG_NUMBEROFDEMCOMPONENTIDS) && (ComponentId > 0))
        {
            if (FiM_ConfigParam_pcs != NULL_PTR)
            {
                idxEnd_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[ComponentId + 1]);
                idxFidOffset_u32 = (FiM_ConfigParam_pcs->FiM_Cfg_NumOffsetComponentptr[ComponentId]);

                /* loop through all FIds attached to the component */
                while (idxFidOffset_u32 < idxEnd_u32)
                {
                    FId_uo = (FiM_ConfigParam_pcs->FiM_CfgInhibitSourceMatrixComponentptr[idxFidOffset_u32]);

                    if (ComponentFailedStatus)
                    {
                        /* if FAILED, increment counter and lock FId */
                        FiM_Priv_FIdCountInc(FId_uo);
                    }
                    else
                    {
                        /* if NOT FAILED, decrement counter and check whether lock can be released */
                        FiM_Priv_FIdCountDec(FId_uo);
                    }

                    idxFidOffset_u32++;
                }
            }
            else
            {
                FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_PARAM_POINTER);
            }
        }
        /* detect development errors / plausibility checks */
        else
        {
            FIM_PRIV_DET_ERROR(FIM_DEMTRIGGERONEVENTSTATUS_ID, FIM_E_COMPONENTID_OUT_OF_RANGE);
        }
    }
#endif
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif

