

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

void NvM_CancelWriteAll(void)
{
    // TRACE[NVM458] Service to cancel a running NvM_WriteAll request
    // TRACE[NVM019] Terminates NvM_WriteAll in a way that data consistency is not compromised

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(NVM_PRV_MULTI_BLOCK);
        // TRACE[NVM637] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_CANCEL_WRITE_ALL, NVM_E_NOT_INITIALIZED);
    }
    else
    {
        // TRACE[NVM420] This cancellation request is not queued
        // TRACE[NVM233] Check whether a WriteAll operation is currently in progress, otherwise do nothing
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2868] NvM_CancelWriteAll cancels the maintenance phase as well.
        SchM_Enter_NvM_Main();
        if (((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL) != 0u) ||
            (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_WRITE_ALL)
#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
            || ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_MAINTAIN) != 0u)
            || (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK)
#endif
           )
        {
            // WriteAll/Maintenance operation is pending or currently in progress
            uint16 idBlock_u16;
            // The auxiliary interface does not support multi-block operations at all, hence it is sufficient to iterate over all "regular" block IDs only
            for (idBlock_u16 = NVM_CFG_FIRST_USED_BLOCK; idBlock_u16 < NVM_CFG_NR_BLOCKS; idBlock_u16++)
            {
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3033] Ignore blocks with length null
                if (*NvM_Prv_BlockDescriptors_acst[idBlock_u16].nrBlockBytes_pu16 > 0)
                {
                    // TRACE[NVM019] Only delete the write all request of blocks for which no MemIf operation is currently ongoing
                    if ((NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] & (uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL) != 0u)
                    {
                        // TRACE[NVM238] Signal write cancelation by resetting the write request bits (-> non-preemptive cancelation)
                        NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL));

                        // Signal that WriteAll is cancelled.
                        // Note: WriteAll is cancelled if the writing of at least one block was cancelled
                        //       except the internal block NvM_WriteMon
#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)
                        if (NvMConf_NvMBlockDescriptor_NvM_WriteMon != idBlock_u16)
                        {
#endif
                            NvM_Prv_Main_st.isWriteAllCanceled_rMwAM_b = TRUE;
#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)
                        }
#endif

                        // TRACE[NVM238] The currently active job shall not be canceled
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2880] If a block is currently PENDING due
                        //                                               to a queued/running single block operation,
                        //                                               the request result shouldn't be set to CANCELED
                        // Note: If a single block request is pending, then the NVM_REQ_PENDING state must originate
                        //       from this single block request because:
                        //       - Single block requests are not accepted by NvM for blocks which are already busy
                        //         with WriteAll (NVM385), so this single block request must have been issued before WriteAll
                        //       - Enqueueing single block requests always sets NVM_REQ_PENDING (NVM185) and
                        //         the single block request is not cleared, so it must be the origin for the NVM_REQ_PENDING state
                        if (((idBlock_u16 == NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16) ||
                             (((NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] & (uint16)NVM_PRV_BLOCK_REQ_ANY_SINGLE) != 0u) &&
                              (NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] == NVM_REQ_PENDING)))
                            )
                        {
                            // Do not set the request result to CANCELED, otherwise a user waiting
                            // for the single block operation to finish gets CANCELED before getting the real result.
                        }
                        else
                        {
                            // TRACE[NVM470] Set job result to NVM_REQ_CANCELED if successfully canceled
                            NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_CANCELED;
                        }
                    }

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
                    if ((NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] & (uint16)NVM_PRV_BLOCK_REQ_MAINTAIN) != 0u)
                    {
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2868] Signal write cancelation by resetting the maintenance request bits (-> non-preemptive cancelation)
                        NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_MAINTAIN));
                        // The maintenance operation is invisible to an NvM user. Therfore, NVM_REQ_CANCELED is not set here.
                    }
#endif
                }
            }
            // TRACE[NVM232] Immediately return, don't wait for the successful completion of the cancel operation
        }
        SchM_Exit_NvM_Main();
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
