

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

Std_ReturnType NvM_Rb_AuxWriteBlock(NvM_BlockIdType BlockId, const void *NvM_SrcPtr)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2944] Service used from an auxiliary user to copy the data of the RAM block to its corresponding NV block
    // The following union is necessary to remove an otherwise unavoidable compiler warning due to a discarded const qualifier
    union
    {
        const void *pcv;
        void *pv;
    } adrRamBlock_un;
    Std_ReturnType stReturn_u8 = E_NOT_OK;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Variables used to report DET errors
    boolean flgDetError_b = FALSE;
    uint8 idDetError_u8 = NVM_PRV_NO_DET_ERROR;
#endif

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM619] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_NOT_INITIALIZED;
#endif
    }
    else if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_RB_AUX_WRITE_BLOCK,
                                     BlockId,
                                     NVM_PRV_AUX_ADMIN_BLOCK))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // TRACE[NVM624] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
    }
    else if (!NvM_Prv_IsSanitizedByReadAll(NvM_Prv_BlockDescriptors_acst[BlockId].stFlags_u16))
    {
        //TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the potentially incompatible blocks after layout changes
        //     should be sanitized by ReadAll at first, then the current single block request
        //     is allowed to be accepted and executed
    }
    else if (
             (
              (NvM_Prv_BlockDescriptors_acst[BlockId].BlockManagementType_en != NVM_BLOCK_DATASET) &&
              (NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_AUX_ADMIN_BLOCK] > 0)
             ) ||
             (
              (NvM_Prv_BlockDescriptors_acst[BlockId].BlockManagementType_en == NVM_BLOCK_DATASET) &&
              (NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_AUX_ADMIN_BLOCK] >= (NvM_Prv_BlockDescriptors_acst[BlockId].nrNvBlocks_u8 + NvM_Prv_BlockDescriptors_acst[BlockId].nrRomBlocks_u8))
             )
            )
    {
        // The currently set dataset index is out of range for this block
        // -> reject this request with E_NOT_OK and report this situation to Det if Det reporting is enabled
        // Note: in the standard API, dataset index limits are already checked in the SetDataIndex service,
        //       but this is not possible in the auxiliary interface because its SetDataIndex service has
        //       no BlockId parameter)
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_PARAM_BLOCK_DATA_IDX;
#endif
    }
	// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3032] Ignore blocks with length null
    else if (*NvM_Prv_BlockDescriptors_acst[BlockId].nrBlockBytes_pu16 == 0)
    {
        // Block length is Null
        // Block is pre-defined but not used
        // Job shall never start
        // return E_NOT_OK
    }
    else
    {
        // Parameters are valid
        // TRACE[NVM410] Trigger a write of the block data from RAM to NV memory
        // TRACE[NVM208] The actual write operation is not done here, just the request for doing it is queued
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2936] The actual write operation for the auxiliary user is not done here, just the request for doing it is queued
        adrRamBlock_un.pcv = NvM_SrcPtr;
        SchM_Enter_NvM_Main();

        // TRACE[NVM209] Check write protection status of this block before enqueuing this request
        // TRACE[NVM377] Check that the dataset index does not point to a ROM block if the NvM block is of type DATASET
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2937] Write protection shall be respected by an auxiliary user
        if (((NvM_Prv_stBlock_rAwAM_au8[BlockId] & NVM_BLOCK_STATE_WRITE_PROT) == 0u) &&
            ((NVM_BLOCK_DATASET != NvM_Prv_BlockDescriptors_acst[BlockId].BlockManagementType_en) ||
             (NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_AUX_ADMIN_BLOCK] < NvM_Prv_BlockDescriptors_acst[BlockId].nrNvBlocks_u8)))
        {
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2929] Use special auxiliary admin block
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2933] Only queue this request if no other auxiliary job is already requested or in progress
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2931] Triggering an auxiliary job on a block which is in progress but triggered by the block owner shall be possible
            if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] == 0) && (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 != NVM_PRV_AUX_ADMIN_BLOCK))
            {
                // No operation pending
                // -> now queue the write request and additionally set the write request flag of this block if we have a RAM block to write from
                if (adrRamBlock_un.pv != NULL_PTR)
                {
                    // Write block contents from the given source
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2933] Queue this request in an auxiliary entry queue
                    /* MR12 RULE 11.5 VIOLATION: The actual type of the RAM block varies from block to block (not under control of NvM) */
                    NvM_Prv_QueueAuxBlockRequest(NVM_SERVICE_ID_RB_AUX_WRITE_BLOCK, BlockId, (uint8 *) adrRamBlock_un.pv);

                    // TRACE[NVM185] Set single block request result to NVM_REQ_PENDING on successful enqueuing
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2929] Use special auxiliary admin block for the request result update
                    NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_AUX_ADMIN_BLOCK] = NVM_REQ_PENDING;

                    // Internally signal that this block has been requested to be written
                    NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_WRITE;

                    stReturn_u8 = E_OK;
                }

                else
                {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
                    // TRACE[NVM622] Report the DET error NVM_E_PARAM_ADDRESS when a NULL pointer is passed via the parameter NvM_SrcPtr
                    flgDetError_b = TRUE;
                    idDetError_u8 = NVM_E_PARAM_ADDRESS;
#endif
                }
            }

            else
            {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
                // TRACE[NVM620] Report the DET error NVM_E_BLOCK_PENDING when NVRAM block identifier is already queued or currently in progress
                flgDetError_b = TRUE;
                idDetError_u8 = NVM_E_BLOCK_PENDING;
#endif
            }
        }

        else
        {
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2818] Report an error by setting a block error flag if writing to a ROM block of an NvM block of type DATASET is attempted
            NvM_Rb_stBlockErrors_au8[BlockId] |= NVM_E_WRITE_PROTECTED;
            // Set write-protected error flag
            NvM_Rb_stBlockErrors_au8[NVM_PRV_MULTI_BLOCK] |= NVM_E_WRITE_PROTECTED;

            // TRACE[NVM377] If the dataset index points to a ROM block (in case the NvM block is of type DATASET) and a write is attempted, E_NOT_OK is returned
        }

        SchM_Exit_NvM_Main();
    }

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Calling foreign DET function is done out of the Schm lock
    if (flgDetError_b != FALSE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_AUX_ADMIN_BLOCK);
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_AUX_WRITE_BLOCK, idDetError_u8);
    }
#endif

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#endif
