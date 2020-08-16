

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
 * Type definitions
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Constants
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/
#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

/**
 * This function returns the type of the currently active block request.
 *
 * Typical use case for this function is to get the type of the block request for which a callback function
 * has been called. So it is appropriate to call this function only in a callback.
 *
 * \param[global in] NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b
 * Global variable to signal that a multiblock request is active.
 *
 * \param[global in] NvM_Prv_Main_st.isMultiBlockServiceSuspended_rMwM_b
 * Global variable to signal that a multiblock request is currently suspended.
 *
 * \param[global in] NvM_Prv_Main_st.Activity_rAMwM_en
 * Global variable which holds the processing state of the currently active job.
 *
 * \return
 * Type of the currently active block request.
 */
NvM_Rb_RequestType_ten NvM_Rb_GetRequestType(void)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3105] Service to get the type of the currently active request
    NvM_Rb_RequestType_ten requestType_en = NvM_Rb_RequestType_NA_e;

    // check whether a multi block request is currently active and not suspended,
    // in case of suspended multiblock request an immediate single block request is active
    if (NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b && !NvM_Prv_Main_st.isMultiBlockServiceSuspended_rMwM_b)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3061] Multi block request active
        requestType_en = NvM_Rb_RequestType_Multi_e;
    }
    // check whether a single block request (regrdless which priority) is active
    else if (
             (NVM_PRV_ACTIVITY_ARBITRATE == NvM_Prv_Main_st.Activity_rAMwM_en) ||
             (NVM_PRV_ACTIVITY_JOB_START == NvM_Prv_Main_st.Activity_rAMwM_en) ||
             (NVM_PRV_ACTIVITY_POLL_RESULT == NvM_Prv_Main_st.Activity_rAMwM_en) ||
             (NVM_PRV_ACTIVITY_RESULT_EVAL == NvM_Prv_Main_st.Activity_rAMwM_en)
            )
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3061] Single block request active
        requestType_en = NvM_Rb_RequestType_Single_e;
    }
    else
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3061] Type of active block request not available
        requestType_en = NvM_Rb_RequestType_NA_e;
    }

    return requestType_en;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
