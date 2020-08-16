

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "Rte_NvM.h"

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

void NvM_Prv_MainFunctionPollResult(void)
{
    // Get the result of the job identified by idActiveJob_rMwM_en

    // TRACE[NVM346] Check the status of the currently active MemIf job
    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MemIf_GetJobResult(NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8);
    if (NvM_Prv_Main_st.stActiveJobResult_rMwM_en != MEMIF_JOB_PENDING)
    {
        // MemIf job has ended -> switch to result evaluation
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_RESULT_EVAL;
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

    /*<BASDKey>
 **********************************************************************************************************************
 * $History__:$
 **********************************************************************************************************************
 </BASDKey>*/
