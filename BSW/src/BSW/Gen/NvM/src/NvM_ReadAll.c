

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

#ifdef NVM_CFG_API_READ_ALL
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2917] Declaration of the overloading function shall be done here, not in a header file
    /* MR12 RULE 8.5 VIOLATION: Not using a header file for this declaration is a customer requirement */
    extern void NVM_CFG_API_READ_ALL(void);

    void NvM_ReadAll(void)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2920] Call the overloading function
        NVM_CFG_API_READ_ALL();
    }

    void NvM_Rb_ReadAllBase(void)
#else
    void NvM_ReadAll(void)
#endif
{
    // TRACE[NVM460] Initiates a multi block read request
    // TRACE[NVM356] This service reads the contents of all applicable permanent RAM blocks from their NV counterparts

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_MULTI_BLOCK);
        // TRACE[NVM646] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_READ_ALL, NVM_E_NOT_INITIALIZED);
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

            // TRACE[NVM185] Set request result to NVM_REQ_PENDING on successful enqueuing
            // TRACE[NVM667] Same as NVM185, but specific to NvM_ReadAll
            NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_MULTI_BLOCK] = NVM_REQ_PENDING;

#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, notify BswM about the state change of the multiblock operation.
            // Calling foreign BswM function is done out of the Schm lock
            flgNotifyBswM_b = TRUE;
#endif

            // Iterate through all used blocks to find the blocks which can and shall be read
            // TRACE[NVM073] In case of dynamic configuration, start with a read operation for block 1
            // TRACE[NVM248] Otherwise, block 1 is not read during NvM_ReadAll
            // TRACE[NVM669] Block ID 1 is reserved for the config ID
            // The auxiliary interface does not support multi-block operations at all, hence it is sufficient to iterate over all "regular" block IDs only
            for (idBlock_u16 = NVM_CFG_FIRST_USED_BLOCK; idBlock_u16 < NVM_CFG_NR_BLOCKS; idBlock_u16++)
            {
				// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3033] Ignore blocks with length null
                if (*NvM_Prv_BlockDescriptors_acst[idBlock_u16].nrBlockBytes_pu16 > 0)
                {
                    // The following conditions must be fulfilled for reading a block during ReadAll:
                    // TRACE[NVM118] Only read blocks which are selected for ReadAll.
                    // Only read blocks configured with a permanent RAM block or with explicit sync. This is already checked in configuration scripts.
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2802] Request the reading of the block only if the NvM RAM block status bit is not set to VALID.
                    // CAUTION: After successfull Read, Write or Restore jobs, if NvM_ReadAll is invoked, the block will be skipped. This is the same if NvMSetRAMBlockStatus was successfully invoked before NvM_ReadAll invocation
                    if (((NvM_Prv_BlockDescriptors_acst[idBlock_u16].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL) != 0u) &&
                        ((NvM_Prv_stBlock_rAwAM_au8[idBlock_u16] & NVM_BLOCK_STATE_RAM_VALID) == 0u))
                    {
                        // TRACE[NVM185] Set single block request result to NVM_REQ_PENDING on successful enqueuing
                        // This is done right away to allow an immediate NvM_GetErrorStatus call returning a meaningful result
                        // Note: In case of dynamic configuration, this might be revised to NVM_REQ_BLOCK_SKIPPED depending
                        // on the config ID comparison result
                        NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_PENDING;

                        // Internally signal that this block has been requested to be read
                        NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] |= (uint16) NVM_PRV_BLOCK_REQ_READ_ALL;
                    }
                    else
                    {
                        // TRACE[NVM287] Set job result to NVM_REQ_BLOCK_SKIPPED if not read
                        // This is done right away to allow an immediate NvM_GetErrorStatus call returning a meaningful result
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2879] If a block is currently PENDING due to a queued/running single block operation, the request result shouldn't be set to SKIPPED
                        if (NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] != NVM_REQ_PENDING)
                        {
                            NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_BLOCK_SKIPPED;
                        }
                    }
                }
            }
            // TRACE[NVM243] The actual read operation is not done here, just the request for doing it is signaled
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_READ_ALL;

            //TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the "NvM_Prv_isReadAllInitiated_b" will be set TRUE
            //     only if ReadAll is initiated, then the blocks are free for the other requests
#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON))
            NvM_Prv_isReadAllInitiated_b = TRUE;
#endif
        }
        SchM_Exit_NvM_Main();

        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, notify BswM about the state change of the multiblock operation.
        // Calling foreign BswM function is done out of the Schm lock
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        if (flgNotifyBswM_b != FALSE)
        {
            BswM_NvM_CurrentJobMode(NVM_SERVICE_ID_READ_ALL, NVM_REQ_PENDING);
        }
#endif

    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
