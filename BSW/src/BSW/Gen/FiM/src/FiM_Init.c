

/**
 **************************************************************************************************
 * FiM_Init.c
 * Initialization functions  for Function Inhibition Manager
 * Design specification: AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 **************************************************************************************************
 */
#include "FiM_Init.h"
#include "FiM.h"
#include "FiM_Utils.h"
#include "FiM_Status.h"
#include "FiM_Monitor.h"

/**
 **************************************************************************************************
 * FiM global variables
 **************************************************************************************************
 */
/* Pointer to Global Config Structure */

#define FIM_START_SEC_RAM_INIT
#include "FiM_MemMap.h"
const FiM_ConfigType* FiM_ConfigParam_pcs = NULL_PTR;
#define FIM_STOP_SEC_RAM_INIT
#include "FiM_MemMap.h"

#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
/* Status initialization variable during Init and ReInit */
boolean FiM_StatusInitialized_b;
boolean FiM_DemInitStatus_b;
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

/**
 **************************************************************************************************
 * FiM_Init (public API)
 **************************************************************************************************
 */
#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

void FiM_Init(const FiM_ConfigType* FiMConfigPtr)
{
    if (!FiM_Priv_GetStatusInitialized())
    {
        if (FiMConfigPtr != NULL_PTR)
        {
            FiM_ConfigParam_pcs = FiMConfigPtr;
        }
        else
        {
            FiM_ConfigParam_pcs = &FIM_POSTBUILD_CONFIGSET_NAME;
        }

        FiM_Priv_SetStatusInitialized(FALSE);
        FiM_Priv_SetDemInitStatus(FALSE);

#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_OFF)
        FiM_Priv_MonitorInit();
#endif

        FiM_Priv_SetStatusInitialized(TRUE);
    }
    else
    {
        FIM_PRIV_DET_ERROR(FIM_INIT_ID, FIM_E_INITIALIZED_ALREADY);
    }
}

/**
 **************************************************************************************************
 * FiM_DemInit (public API)
 **************************************************************************************************
 */
void FiM_DemInit(void)
{
    if (FiM_Priv_GetStatusInitialized())
    {
        if (!FiM_Priv_IsDemInitCalled())
        {
            /* Setting the Re-Initialization requested flag to TRUE */
            FiM_Priv_SetDemInitStatus(TRUE);

            /* For the cyclic mode, the actual Re-initialization of the monitoring state machine is done as part of the FiM_MainFunction,
             * this is to ensure that the FiM_MainFunction and FiM_DemInit are not running in parallel
             */

            FiM_Priv_StatusInit();

        }
        else
        {
            FIM_PRIV_DET_ERROR(FIM_DEMINIT_ID, FIM_E_DEMINIT_CALLED_ALREADY);
        }
    }
    else
    {
        FIM_PRIV_DET_ERROR(FIM_DEMINIT_ID, FIM_E_NOT_INITIALIZED);
    }

}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

