

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "Rte_NvM.h"

#if (NVM_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"    // TRACE[NVM556] NvM module shall include Det.h
// TRACE[NVM089] Check version compatibility of included header files
# if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
#  error "AUTOSAR major version undefined or mismatched"
# endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/

#if (NVM_RB_AUX_INTERFACE == STD_ON)

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

Std_ReturnType NvM_Rb_AuxGetDataIndex(uint8 *DataIndexPtr)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2940] Service used from an auxiliary user to get the currently set DataIndex of a dataset NVRAM block
    Std_ReturnType stReturn_u8 = E_NOT_OK;

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_AUX_ADMIN_BLOCK);
        // TRACE[NVM602] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_AUX_GET_DATA_INDEX, NVM_E_NOT_INITIALIZED);
    }

    // Check provided parameter
    else if(DataIndexPtr == NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_AUX_ADMIN_BLOCK);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        // TRACE[NVM605] Report the DET error NVM_E_PARAM_DATA when a NULL pointer is passed via the parameter DataIndexPtr
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_AUX_GET_DATA_INDEX, NVM_E_PARAM_DATA);
    }

    else
    {
        // Parameters are valid
        // TRACE[NVM021] Get the current data index of the selected block if its management type is NVM_BLOCK_DATASET
        // No SchM lock can and should be done here to allow calling this function from NvM callbacks without deadlocks
        *DataIndexPtr = NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_AUX_ADMIN_BLOCK];
        stReturn_u8 = E_OK;
    }

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#endif
