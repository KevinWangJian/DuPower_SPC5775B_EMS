

/**
 **************************************************************************************************
 * FiM_Init.h
 * Initialization header for Function Inhibition Manager
 * Design specification: AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 **************************************************************************************************
 */
#ifndef FIM_INIT_H
#define FIM_INIT_H

#include "FiM_Priv_Data.h"
#include "FiM_Det.h"

/**
 **************************************************************************************************
 * global variables
 **************************************************************************************************
 */
#define FIM_START_SEC_RAM_CLEARED
#include "FiM_MemMap.h"
extern boolean FiM_StatusInitialized_b;
extern boolean FiM_DemInitStatus_b;
#define FIM_STOP_SEC_RAM_CLEARED
#include "FiM_MemMap.h"

#define FIM_START_SEC_RAM_INIT
#include "FiM_MemMap.h"
extern const FiM_ConfigType* FiM_ConfigParam_pcs;
#define FIM_STOP_SEC_RAM_INIT
#include "FiM_MemMap.h"
/**
 **************************************************************************************************
 * private inline functions
 **************************************************************************************************
 */

/* set the initialization status variable */

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

LOCAL_INLINE void FiM_Priv_SetStatusInitialized(boolean status)
{
    FiM_StatusInitialized_b = status;
}

/* return the initialization status variable */
LOCAL_INLINE boolean FiM_Priv_GetStatusInitialized(void)
{
    return FiM_StatusInitialized_b;
}

/* set the re-initialization status variable */
LOCAL_INLINE void FiM_Priv_SetDemInitStatus(boolean status)
{
    FiM_DemInitStatus_b = status;
}

/* return the re-initialization status variable */
LOCAL_INLINE boolean FiM_Priv_IsDemInitCalled(void)
{
    return FiM_DemInitStatus_b;
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif /* include protection */

