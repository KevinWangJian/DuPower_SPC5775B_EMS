

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

void NvM_Rb_FirstInitAll(void)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2826] Service to trigger a multi block (re-) initialization operation

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_MULTI_BLOCK);
        // Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        // (similar to what is requested by NVM647 in the context of NvM_WriteAll)
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_FIRST_INIT_ALL, NVM_E_NOT_INITIALIZED);
    }
    else
    {
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        boolean flgNotifyBswM_b = FALSE;
#endif

        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2829] Use the same single entry "queue" as used for ReadAll/WriteAll
        SchM_Enter_NvM_Main();
        if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] == 0u) && (NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b == FALSE))
        {
            NvM_BlockIdType idBlock_u16;

            // TRACE[NVM185] Set multi block request result to NVM_REQ_PENDING on successful enqueuing
            NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_MULTI_BLOCK] = NVM_REQ_PENDING;

#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, notify BswM about the state change of the multiblock operation.
            // Calling foreign BswM function is done out of the Schm lock
            flgNotifyBswM_b = TRUE;
#endif

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2830] Iterate over all used blocks to find the blocks which can and shall be initialized
            for (idBlock_u16 = NVM_CFG_FIRST_USED_BLOCK; idBlock_u16 < NVM_CFG_NR_BLOCKS; idBlock_u16++)
            {
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3033] Ignore blocks with length null
                if (*NvM_Prv_BlockDescriptors_acst[idBlock_u16].nrBlockBytes_pu16 > 0)
                {
                    // The following conditions must be fulfilled for initializing a block during FirstInitAll:
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2830] Only initialize blocks which are selected for FirstInitAll
                    // Further conditions are already checked in the configuration scripts
                    if ((NvM_Prv_BlockDescriptors_acst[idBlock_u16].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_FIRST_INIT_ALL) != 0u)
                    {
                        // TRACE[NVM185] Set single block request result to NVM_REQ_PENDING on successful enqueuing
                        // This is done right away to allow an immediate NvM_GetErrorStatus call returning a meaningful result
                        NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_PENDING;

                        // Internally signal that this block has been requested to be written
                        NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] |= (uint16) NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL;
                    }
                    else
                    {
                        // Set job result to NVM_REQ_BLOCK_SKIPPED if not initialized
                        // This is done right away to allow an immediate NvM_GetErrorStatus call returning a meaningful result
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2879] If a block is currently PENDING due to a queued/running single block operation, the request result shouldn't be set to SKIPPED
                        if (NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] != NVM_REQ_PENDING)
                        {
                            NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_BLOCK_SKIPPED;
                        }
                    }
                }
            }
            // The actual initialization operation is not done here, just the request for doing it is signaled
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL;
        }
        SchM_Exit_NvM_Main();

        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, notify BswM about the state change of the multiblock operation.
        // Calling foreign BswM function is done out of the Schm lock
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        if (flgNotifyBswM_b != FALSE)
        {
            BswM_NvM_CurrentJobMode(NVM_SERVICE_ID_RB_FIRST_INIT_ALL, NVM_REQ_PENDING);
        }
#endif

    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
