

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "Rte_NvM.h"

#if (NVM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"    // TRACE[NVM556] NvM module shall include Det.h
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

void NvM_MainFunction(void)
{
    // TRACE[NVM464] Service for performing the processing of the NvM jobs
    // TRACE[NVM256] Same as NVM464
    // TRACE[NVM324] No assumption is made about the invocation timing relative to other BSW main processing functions

    // TRACE[NVM257] Check for proper initialization before doing any real job processing
    // Note: This is done in a strict way here, thereby trying to catch general RAM corruption e.g. by wild pointers
    if ((NvM_Prv_Main_st.isInitialized_rAM_b != TRUE) ||
        ((NvM_Prv_Main_st.Activity_rAMwM_en != NVM_PRV_ACTIVITY_NOT_INIT) &&
         (NvM_Prv_Main_st.Activity_rAMwM_en != NVM_PRV_ACTIVITY_IDLE) &&
         (NvM_Prv_Main_st.Activity_rAMwM_en != NVM_PRV_ACTIVITY_ARBITRATE) &&
         (NvM_Prv_Main_st.Activity_rAMwM_en != NVM_PRV_ACTIVITY_JOB_START) &&
         (NvM_Prv_Main_st.Activity_rAMwM_en != NVM_PRV_ACTIVITY_POLL_RESULT) &&
         (NvM_Prv_Main_st.Activity_rAMwM_en != NVM_PRV_ACTIVITY_RESULT_EVAL)))
    {
        // Disallow any further job processing
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_NOT_INIT;
    }

    if (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_NOT_INIT)
    {
        // NvM is not initialized
        // -> refuse to do anything, report error to Det if this functionality is enabled

        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3114] Set block ID to 0 if NvM service does not use any block ID
        NvM_Prv_SetBlockIdCausingLastDetError(0u);
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_MAIN_FUNCTION, NVM_E_NOT_INITIALIZED);
    }
    else
    {
        // Check whether we shall do request arbitration
        if ((NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_IDLE) ||
            (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_ARBITRATE))
        {
            // Perform request arbitration (this may change NvM_Prv_Main_st.Activity_rAMwM_en)
            NvM_Prv_MainFunctionArbitrate();
        }

        // Check whether we shall start a job
        if (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START)
        {
            // Start the job identified by NvM_Prv_Main_st.idActiveJob_rMwM_en (this may change NvM_Prv_Main_st.Activity_rAMwM_en)
            NvM_Prv_MainFunctionJobStart();
        }

        // Check whether we shall poll for MemIf jobs
        if (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_POLL_RESULT)
        {
            // Wait for the termination of a MemIf job (this may change NvM_Prv_Main_st.Activity_rAMwM_en)
            NvM_Prv_MainFunctionPollResult();
        }

        // Check whether we shall evaluate the result of an asynchronous operation
        if (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_RESULT_EVAL)
        {
            // Evaluate the result of an asynchronous operation (this may change NvM_Prv_Main_st.Activity_rAMwM_en;
            // might also turn a read job into a restore job which is then to be started)
            NvM_Prv_MainFunctionResultEval();
        }

        // TRACE[NVM349] If no further job processing is possible, immediately return
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
