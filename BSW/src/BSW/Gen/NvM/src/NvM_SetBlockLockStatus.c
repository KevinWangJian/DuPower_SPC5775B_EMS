

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

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

void NvM_SetBlockLockStatus(NvM_BlockIdType BlockId, boolean BlockLocked)
{
    // TRACE[NVM548] Service for setting the lock status of a permanent RAM block of an NVRAM block

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        // TRACE[NVM728] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_SET_BLOCK_LOCK_STATUS, NVM_E_NOT_INITIALIZED);
    }
    else if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_SET_BLOCK_LOCK_STATUS, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // TRACE[NVM731] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
    }
    else if ((NvM_Prv_stRequests_rAMwAM_au16[BlockId] != 0) || (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 == BlockId))
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2866] NvM_SetBlockLockStatus can be called for a block whose the only pending operation is a a maintenance operation.
#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
        if (!((NvM_Prv_stRequests_rAMwAM_au16[BlockId] == NVM_PRV_BLOCK_REQ_MAINTAIN) ||
              (
               (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK) &&
               (NvM_Prv_stRequests_rAMwAM_au16[BlockId] == 0) &&
               (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 == BlockId)
              )
             ))
#endif
        {
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
            NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
            // TRACE[NVM729] Report the DET error NVM_E_BLOCK_PENDING when NVRAM block identifier is already queued or currently in progress
            NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_SET_BLOCK_LOCK_STATUS, NVM_E_BLOCK_PENDING);
        }
    }
    else if ((NvM_Prv_BlockDescriptors_acst[BlockId].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_WRITE_ONCE) != 0u)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        // TRACE[NVM730] Report the DET error NVM_E_BLOCK_CONFIG when the NVRAM block is configured with NvMWriteBlockOnce = TRUE
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_SET_BLOCK_LOCK_STATUS, NVM_E_BLOCK_CONFIG);
    }
    else
    {
        // This is currently a stub only, it does nothing yet
        if (BlockLocked) { } // Avoid "unused parameter" warning
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
