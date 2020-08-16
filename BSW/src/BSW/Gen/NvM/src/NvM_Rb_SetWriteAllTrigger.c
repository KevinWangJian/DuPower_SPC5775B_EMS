

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

#if (NVM_RB_SET_WRITEALL_TRIGGER_API == STD_ON)

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

/**
 *********************************************************************
 * NvM_Rb_SetWriteAllTrigger(NvM_BlockIdType BlockId, boolean WriteAllTrigger):
 * Service for triggering a multi-block write without any check.
 * That means from the user point of view, it would be possible to trigger a NvM_WriteAll
 * without caring about:
 *  - the state of the RAM block
 *  - the single job queue
 *  - the current state of the latest job which has been triggered
 *
 * Possible values for WriteAllTrigger:
 * TRUE: This function trigger the NvM_WriteAll for the selected BlockID
 * FALSE:This function will not trigger NvM_WriteAll
 *       Alternative triggers such as a VALID/CHANGED RAM block state are not reset
 *
 * \param    BlockId:         Id of the corresponding block
 * \param    WriteAllTrigger: Enable/Disable the trigger
 * \return   Function result
 * \retval   E_OK:      request was accepted
 * \retval   E_NOT_OK:  request was not accepted
 *********************************************************************
 */
Std_ReturnType NvM_Rb_SetWriteAllTrigger(NvM_BlockIdType BlockId, boolean WriteAllTrigger)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2977] Service for triggering a multi-block write job
    Std_ReturnType stReturn_u8 = E_NOT_OK;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Variables used to report DET errors
    boolean flgDetError_b = FALSE;
    uint8 idDetError_u8 = NVM_PRV_NO_DET_ERROR;
#endif

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized (similar to NVM643)
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_NOT_INITIALIZED;
#endif
    }
    else if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_RB_SET_WRITEALL_TRIGGER, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range (similar to NVM645)
    }
    else
    {
        // -> check whether the selected block has an associated RAM block
        if (*NvM_Prv_BlockDescriptors_acst[BlockId].adrRamBlock_ppv != NULL_PTR)
        {
            SchM_Enter_NvM_Main();
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2979]
            // Trigger NvM_WriteAll if this the user called this function
            if (WriteAllTrigger)
            {
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2977]
                // Set the flag for the storage of NvM Data during writeall
                NvM_Prv_stBlock_rAwAM_au8[BlockId] |= NVM_RB_BLOCK_STATE_MASK_TRG_WRITEALL;
            }
            else
            {
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2977]
                // Reset the flag for the storage of NvM Data during writeall
                NvM_Prv_stBlock_rAwAM_au8[BlockId] &= (uint8) ~NVM_RB_BLOCK_STATE_MASK_TRG_WRITEALL;
            }
            stReturn_u8 = E_OK;
            SchM_Exit_NvM_Main();
        }
        else
        {
            // If no permanent RAM block has been configured for the block, this function has no effect (similar to NVM240)
        }
    }

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Calling foreign DET function is done out of the Schm lock
    if (flgDetError_b != FALSE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_SET_WRITEALL_TRIGGER, idDetError_u8);
    }
#endif

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
#endif
