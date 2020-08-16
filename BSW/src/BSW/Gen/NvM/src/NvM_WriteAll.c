

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

#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
# include "BswM_NvM.h"
// TRACE[NVM089] Check version compatibility of included header files
# if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
#  error "AUTOSAR major version undefined or mismatched"
# endif
# if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || ((BSWM_AR_RELEASE_MINOR_VERSION != 0) && (BSWM_AR_RELEASE_MINOR_VERSION != 2)))
#  error "AUTOSAR minor version undefined or mismatched"
# endif
#endif

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

#ifdef NVM_CFG_API_WRITE_ALL
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2917] Declaration of the overloading function shall be done here, not in a header file
    /* MR12 RULE 8.5 VIOLATION: Not using a header file for this declaration is a customer requirement */
    extern void NVM_CFG_API_WRITE_ALL(void);

    void NvM_WriteAll(void)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2920] Call the overloading function
        NVM_CFG_API_WRITE_ALL();
    }

    void NvM_Rb_WriteAllBase(void)
#else
    void NvM_WriteAll(void)
#endif
{
    // TRACE[NVM461] Initiates a multi block write request
    // TRACE[NVM018] This service writes the contents of all permanent RAM blocks to their NV counterparts

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_MULTI_BLOCK);
        // TRACE[NVM647] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_WRITE_ALL, NVM_E_NOT_INITIALIZED);
    }
    else
    {
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        boolean flgNotifyBswM_b = FALSE;
#endif

        // TRACE[NVM380] The "queue" for multiblock requests has only one entry so only one multiblock operation is allowed
        SchM_Enter_NvM_Main();

        if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] == 0u) && (NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b == FALSE))
        {
            NvM_BlockIdType idBlock_u16;

            // TRACE[NVM185] Set multi block request result to NVM_REQ_PENDING on successful enqueuing
            // TRACE[NVM549] Same as NVM185, but specific to NvM_WriteAll
            NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_MULTI_BLOCK] = NVM_REQ_PENDING;

#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, notify BswM about the state change of the multiblock operation.
            // Calling foreign BswM function is done out of the Schm lock
            flgNotifyBswM_b = TRUE;
#endif

            // Iterate through all used blocks to find the blocks which can and shall be written
            // The auxiliary interface does not support multi-block operations at all, hence it is sufficient to iterate over all "regular" block IDs only
            for (idBlock_u16 = NVM_CFG_FIRST_USED_BLOCK; idBlock_u16 < NVM_CFG_NR_BLOCKS; idBlock_u16++)
            {
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3033] Ignore blocks with length null
                if (*NvM_Prv_BlockDescriptors_acst[idBlock_u16].nrBlockBytes_pu16 > 0)
                {
                    // The following conditions must be fulfilled for writing a block during WriteAll:
                    // TRACE[NVM252] Only write blocks which are selected for WriteAll
                    // Only write blocks configured with a permanent RAM block or with explicit sync. This is already checked in configuration scripts.
                    // TRACE[NVM432] Only write blocks which are not write protected
                    // TRACE[NVM433] Same as NVM432
                    // TRACE[NVM377] Check that the dataset index does not point to a ROM block if the NvM block is of type DATASET
                    // TRACE[NVM682] Only write blocks where the corresponding RAM block is valid and changed
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2978]
                    // Write blocks if the flag for triggering the multi write is enabled
              /*      if (((NvM_Prv_BlockDescriptors_acst[idBlock_u16].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL) != 0u) &&
                        ((NvM_Prv_stBlock_rAwAM_au8[idBlock_u16] & NVM_BLOCK_STATE_WRITE_PROT) == 0u) &&
                        ((NVM_BLOCK_DATASET != NvM_Prv_BlockDescriptors_acst[idBlock_u16].BlockManagementType_en) ||
                         (NvM_Prv_idxDataSet_rAMwA_au8[idBlock_u16] < NvM_Prv_BlockDescriptors_acst[idBlock_u16].nrNvBlocks_u8)) &&
                        (((NvM_Prv_stBlock_rAwAM_au8[idBlock_u16] & NVM_BLOCK_STATE_RAM_MASK) == NVM_BLOCK_STATE_RAM_VALID_CHANGED)
#if (NVM_RB_SET_WRITEALL_TRIGGER_API == STD_ON)
                     || ((NvM_Prv_stBlock_rAwAM_au8[idBlock_u16] & NVM_RB_BLOCK_STATE_MASK_TRG_WRITEALL) != 0u)
#endif
#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)
                     // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3140] The NvM shall configure the NVRAM block NvM_WriteMon
                     //                                               to be part of NvM_ReadAll and NvM_WriteAll.
                     || (NvMConf_NvMBlockDescriptor_NvM_WriteMon == idBlock_u16)
#endif
                        ))
                    	*/
                    if((NvM_Prv_BlockDescriptors_acst[idBlock_u16].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL) != 0u)
                    {
                        // TRACE[NVM185] Set single block request result to NVM_REQ_PENDING on successful enqueuing
                        // TRACE[NVM549] Same as NVM185, but specific to NvM_WriteAll
                        // This is done right away to allow an immediate NvM_GetErrorStatus call returning a meaningful result
                        NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_PENDING;

                        // Internally signal that this block has been requested to be written
                        NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] |= (uint16) NVM_PRV_BLOCK_REQ_WRITE_ALL;

#if (NVM_RB_SET_WRITEALL_TRIGGER_API == STD_ON)
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2980]
                        // Set the flag back to the init state after triggering the WriteAll
                        NvM_Prv_stBlock_rAwAM_au8[idBlock_u16] &= (uint8) ~NVM_RB_BLOCK_STATE_MASK_TRG_WRITEALL;
#endif
                    }
                    else
                    {
                        // TRACE[NVM434] Skip write protected blocks without any error notification
                        // TRACE[NVM377] Behave similarly to write protected blocks if the block is of type DATASET and the dataset-index points to a ROM-block
                        // TRACE[NVM375] Writing to an NV block of a block of type DATASET is not possible if the block is write protected
                        // TRACE[NVM298] Set job result to NVM_REQ_BLOCK_SKIPPED if not written
                        // This is done right away to allow an immediate NvM_GetErrorStatus call returning a meaningful result
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2879] If a block is currently PENDING due to a queued/running single block operation, the request result shouldn't be set to SKIPPED
                        if (NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] != NVM_REQ_PENDING)
                        {
                            NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_BLOCK_SKIPPED;
                        }
                    }

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
                    if (NVM_BLOCK_REDUNDANT == NvM_Prv_BlockDescriptors_acst[idBlock_u16].BlockManagementType_en)
                    {
                        // TRACE[NVM474] A corrupted NV block of a redundant NVM block is to be recovered from the intact NV block during the execution of WriteAll
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2860] A redundant block is maintained even if it is not suitable for WriteAll
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2869] A redundant block is to be maintained even if it is write-protected
                        // -> Internally signal that this block has been requested to be maintained
                        NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] |= (uint16) NVM_PRV_BLOCK_REQ_MAINTAIN;

                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2862] The request result of a redundant block which is not suitable for WriteAll is not set to PENDING although its is going to be maintained.
                    }
#endif
                }
            }

            // TRACE[NVM254] The actual write operation is not done here, just the request for doing it is signaled
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_WRITE_ALL;

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2861] The maintenance operation is to be performed even if, at the time when NvM_WriteAll is invoked, no blocks are suitable for WriteAll.
            // -> Signal that a maintenance phase has to be performed
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_MAINTAIN;
#endif
        }

        SchM_Exit_NvM_Main();

        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, notify BswM about the state change of the multiblock operation.
        // Calling foreign BswM function is done out of the Schm lock
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        if (flgNotifyBswM_b != FALSE)
        {
            BswM_NvM_CurrentJobMode(NVM_SERVICE_ID_WRITE_ALL, NVM_REQ_PENDING);
        }
#endif

    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
