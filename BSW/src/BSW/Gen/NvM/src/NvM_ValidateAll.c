

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "NvM.h"

#include "NvM_Cfg_SchM.h"

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
 */
#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

/**
 * This function initiates a multiblock validation request.
 *
 * A multiblock validation request will be initiated only if NvM has been initialized and no other multiblock request
 * is active. Furthermore this request will be initiated only for NVRAM-blocks which are valid
 * (citation from AR "not INVALID") and configured for auto validation.
 *
 * To signal a successful initiation this function sets the request result to pending state for each NVRAM-block and
 * sets the bit which globally represents the ValidateAll request in administrative-block of each NVRAM-block.
 *
 * \param[global in] NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b
 * Global variable to signal that a multiblock request is active.
 *
 * \param[global in] NvM_Prv_BlockDescriptors_acst[idBlock_uo].stFlags_u16
 * Global constant array with different configuration properties for each NVRAM-block.
 *
 * \param[global in] NvM_Prv_stBlock_rAwAM_au8
 * Global array of bit-fields which represents the current state of each NVRAM-block
 * (s. description of this variable).
 *
 * \param[global in,out] NvM_Prv_stRequests_rAMwAM_au16
 * Global array of bit-fields which represents all requests pending on each NVRAM-block.
 * (s. description of this variable).
 *
 * \param[global out] NvM_Prv_stRequestResult_rAwAM_au8
 * Global array with results of last request for each NVRAM-block.
 *
 */
void NvM_ValidateAll(void)
{
    // TRACE[NVM855] Initiates a multi block validation request

    if (NvM_Prv_IsNvmInitialized(NVM_SERVICE_ID_VALIDATE_ALL, NVM_PRV_MULTI_BLOCK))
    {
        SchM_Enter_NvM_Main();

        // TRACE[NVM380] The "queue" for multiblock requests has only one entry
        //               so only one multiblock operation is allowed
        if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] == 0u) &&
            (NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b == FALSE))
        {
            NvM_BlockIdType idBlock_uo;

            // TRACE[NVM185] Set multi block request result to NVM_REQ_PENDING on successful enqueuing
            // TRACE[NVM861] Same as NVM185, but specific to NvM_ValidateAll
            NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_MULTI_BLOCK] = NVM_REQ_PENDING;
            // The position of request flag setting is different from other requests
            // because it does not matter
            // TRACE[NVM858] The actual autovalidation operation is not done here,
            //               just the request for doing it is signaled
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] |= (uint16)NVM_PRV_BLOCK_REQ_VALIDATE_ALL;

            // Iterate through all used blocks to find the blocks which can and shall be validated
            for (idBlock_uo = NVM_CFG_FIRST_USED_BLOCK; idBlock_uo < NVM_CFG_NR_BLOCKS; ++idBlock_uo)
            {
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3033] Ignore blocks with length null
                if (*NvM_Prv_BlockDescriptors_acst[idBlock_uo].nrBlockBytes_pu16 > 0)
                {
                    // TRACE[NVM856] Only validate blocks which are selected for ValidateAll
                    // TRACE[NVM860] Similar as NVM856
                    if (((NvM_Prv_BlockDescriptors_acst[idBlock_uo].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_USE_AUTO_VALIDATION) != 0u) &&
                        ((NvM_Prv_stBlock_rAwAM_au8[idBlock_uo] & NVM_BLOCK_STATE_RAM_VALID) != 0u))
                    {
                        //  TRACE[NVM861] Set the result for each proceeding block to NVM_REQ_PENDING
                        NvM_Prv_stRequestResult_rAwAM_au8[idBlock_uo] = NVM_REQ_PENDING;
                        // Internally signal that this block has been requested to be validated
                        NvM_Prv_stRequests_rAMwAM_au16[idBlock_uo] |= (uint16)NVM_PRV_BLOCK_REQ_VALIDATE_ALL;
                    }
                }
            }
        }

            SchM_Exit_NvM_Main();
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
