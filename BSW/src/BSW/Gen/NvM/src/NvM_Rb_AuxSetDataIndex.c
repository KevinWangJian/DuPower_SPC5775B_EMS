

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "NvM_Cfg_SchM.h"

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

Std_ReturnType NvM_Rb_AuxSetDataIndex(uint8 DataIndex)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2941] Service used from an auxiliary user for setting the DataIndex of a dataset NVRAM block
    Std_ReturnType stReturn_u8 = E_NOT_OK;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Variables used to report DET errors
    boolean flgDetError_b = FALSE;
    uint8 idDetError_u8 = NVM_PRV_NO_DET_ERROR;
#endif

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM027] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_NOT_INITIALIZED;
#endif
    }

    else
    {
        // TRACE[NVM704] Prohibit administrative data block modifications while a single-block operation is pending or in progress
        SchM_Enter_NvM_Main();
        if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] == 0) && (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 != NVM_PRV_AUX_ADMIN_BLOCK))
        {
            NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_AUX_ADMIN_BLOCK] = DataIndex;
            stReturn_u8 = E_OK;
        }
        else
        {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
            // TRACE[NVM598] Report the DET error NVM_E_BLOCK_PENDING when NVRAM block identifier is already queued or currently in progress
            flgDetError_b = TRUE;
            idDetError_u8 = NVM_E_BLOCK_PENDING;
#endif
        }
        SchM_Exit_NvM_Main();
    }

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Calling foreign DET function is done out of the Schm lock
    if (flgDetError_b != FALSE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_AUX_ADMIN_BLOCK);
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_AUX_SET_DATA_INDEX, idDetError_u8);
    }
#endif

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#endif
