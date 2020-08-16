

/**
 **************************************************************************************************
 * FiM_Permission.c
 * API for getting FId permission for Function Inhibition Manager
 * Design specification: AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 **************************************************************************************************
 */
#include "FiM_Init.h"
#include "FiM.h"
#include "FiM_Det.h"
#include "FiM_Status.h"
#include "Rte_FiM.h"

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"
/**
 **************************************************************************************************
 * FiM_GetFunctionPermission API (public API)
 **************************************************************************************************
 */
/* MR12 RULE 8.3 VIOLATION: Parameter identifier FID is replaced by Rte_PDAV when using Rte*/
Std_ReturnType FiM_GetFunctionPermission(FiM_FunctionIdType FID, boolean* Permission)
{
    Std_ReturnType retVal = E_NOT_OK;

    boolean isFimInitialized = FiM_Priv_GetStatusInitialized();
    boolean isDemInitialized = FiM_Priv_IsDemInitCalled();
    if ((isFimInitialized) && (isDemInitialized) && (FID > 0) && (FID <= FIM_CFG_NUMBEROFFIDS)
            && (Permission != NULL_PTR))
    {
        *Permission = FiM_Priv_FIdGetPermission(FID);
        retVal = E_OK;
    }
    else
    {
        if (!FiM_Priv_GetStatusInitialized())
        {
            FIM_PRIV_DET_ERROR(FIM_GETFUNCTIONPERMISSION_ID, FIM_E_NOT_INITIALIZED);
        }
        if (!FiM_Priv_IsDemInitCalled())
        {
            FIM_PRIV_DET_ERROR(FIM_GETFUNCTIONPERMISSION_ID, FIM_E_DEMINIT_NOT_CALLED);
        }
        if ((FID > FIM_CFG_NUMBEROFFIDS) || (FID == 0))
        {
            FIM_PRIV_DET_ERROR(FIM_GETFUNCTIONPERMISSION_ID, FIM_E_FID_OUT_OF_RANGE);
        }
        if (Permission == NULL_PTR)
        {
            FIM_PRIV_DET_ERROR(FIM_GETFUNCTIONPERMISSION_ID, FIM_E_PARAM_POINTER);
        }
    }

    return retVal;
}

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
// ---------------------------------------------------------------------------------------------------------------------
// FiM_GetMode07Visibility API (public API)
// ---------------------------------------------------------------------------------------------------------------------
// TO read the service$07 visibility counter for the FID
Std_ReturnType FiM_GetService07Visibility(FiM_FunctionIdType FID, boolean* Visibility)
{
    Std_ReturnType retVal = E_NOT_OK;

    boolean isFimInitialized = FiM_Priv_GetStatusInitialized();
    boolean isDemInitialized = FiM_Priv_IsDemInitCalled();
    if (isFimInitialized && (isDemInitialized)
            && ((FID > 0) && (FID <= FIM_CFG_NUMBEROFFIDS) && (Visibility != NULL_PTR)))
    {
        *Visibility = FALSE;
        retVal = E_OK;

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)
        if (FiM_FIdServ07StatusCounter_auo[FID] > 0)
        {
            *Visibility = TRUE;
        }
#else
        if (((FiM_FIdStatusServ07BitArray_au8[FiM_LastIdx][(FID / 8)]) & ((uint8) (1u << (uint8) (FID % 8)))) > 0u)
        {
            *Visibility = TRUE;
        }
#endif
    }

    return retVal;
}

#endif

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

