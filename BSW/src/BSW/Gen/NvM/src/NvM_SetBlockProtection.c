

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

/* MR12 RULE 8.3 VIOLATION: The parameter identifiers in Rte's generated declaration of this depend on Rte vendor */
Std_ReturnType NvM_SetBlockProtection(NvM_BlockIdType BlockId, boolean ProtectionEnabled)
{
    // TRACE[NVM450] Service for setting/resetting the write protection for a NV block
    Std_ReturnType stReturn_u8 = E_NOT_OK;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Variables used to report DET errors
    boolean flgDetError_b = FALSE;
    uint8 idDetError_u8 = NVM_PRV_NO_DET_ERROR;
#endif

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM606] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_NOT_INITIALIZED;
#endif
    }
    else if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_SET_BLOCK_PROTECTION, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // TRACE[NVM609] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
    }
    // TRACE[NVM325] Allow changing the write protection state if NvMWriteBlockOnce is false
    // TRACE[NVM577] Disallow changing the write protection state if NvMWriteBlockOnce is true
    // TRACE[NVM398] Disallow disabling the write protection if NvMWriteBlockOnce is true
    else if ((NvM_Prv_BlockDescriptors_acst[BlockId].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_WRITE_ONCE) != 0u)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM608] Report the DET error NVM_E_BLOCK_CONFIG when the NVRAM block is configured with NvMWriteBlockOnce = TRUE
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_BLOCK_CONFIG;
#endif
    }
    else
    {
        // TRACE[NVM016] Set the write protection flag in the administrative block according to the ProtectionEnabled parameter
        // TRACE[NVM704] Prohibit administrative data block modifications while a single-block operation is pending or in progress
        // Note: The condition below also intentionally locks out those modifications if a multi-block operation
        //       is currently busy with the selected block (just for safety reasons)
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2866] NvM_SetBlockProtection can be called for a block whose the only pending operation is a a maintenance operation.
        SchM_Enter_NvM_Main();
        if (((NvM_Prv_stRequests_rAMwAM_au16[BlockId] == 0) && (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 != BlockId))
#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
            || (NvM_Prv_stRequests_rAMwAM_au16[BlockId] == NVM_PRV_BLOCK_REQ_MAINTAIN)
            || (
                (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK) &&
                (NvM_Prv_stRequests_rAMwAM_au16[BlockId] == 0) &&
                (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 == BlockId)
               )
#endif
           )
        {
            if (ProtectionEnabled)
            {
                NvM_Prv_stBlock_rAwAM_au8[BlockId] |= NVM_BLOCK_STATE_WRITE_PROT;
            }
            else
            {
                // TRACE[NVM578] Allow to disable the write protection state
                NvM_Prv_stBlock_rAwAM_au8[BlockId] &= (uint8) ~(NVM_BLOCK_STATE_WRITE_PROT);
            }
            stReturn_u8 = E_OK;
        }
        else
        {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
            // TRACE[NVM607] Report the DET error NVM_E_BLOCK_PENDING when NVRAM block identifier is already queued or currently in progress
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
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_SET_BLOCK_PROTECTION, idDetError_u8);
    }
#endif

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
