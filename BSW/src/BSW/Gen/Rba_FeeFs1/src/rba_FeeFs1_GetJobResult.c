


/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR FEE
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "Fee.h"
#include "rba_FeeFs1_Prv.h"

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if(STD_ON == FEE_DEV_ERROR_DETECT)
#include "Det.h"
/* Version check deactivated due to incompatabality with CC-AS (AR3.1)
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
*/
#endif


#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_GetJobResult(): Return the job result of the last accepted job coming from NvM layer.
 *
 * This function returns the job result of the last job coming from NvM layer.
 *
 * \return   FEE job result
 * \retval   MEMIF_JOB_OK:       The last job has been finished successfully
 * \retval   MEMIF_JOB_PENDING:  The last job is still pending
 * \retval   MEMIF_JOB_CANCELED: The last job has been canceled
 * \retval   MEMIF_JOB_FAILED:   The last job failed
 * \retval   MEMIF_BLOCK_INCONSISTENT: The requested block is inconsistent
 *                                     and may contain corrupt data
 * \retval   MEMIF_BLOCK_INVALID: The requested block has been invalidated,
 *                                the requested read operation can not
 *                                be performed.
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(MemIf_JobResultType, FEE_CODE) Fee_GetJobResult(void)
{
    VAR(MemIf_JobResultType, AUTOMATIC) xRetVal = Fee_JobResult[FEE_NVM_JOB];   /* Function return */

    /* Check the FEE module status */
    if (Fee_GlobModuleState_st == MEMIF_UNINIT)
    {
        #if(STD_ON == FEE_DEV_ERROR_DETECT)
        /* Report error to DET */
        /* MR12 RULE 17.7 VIOLATION: Return value is not required */
        (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SID_GETJOBRESULT, FEE_E_UNINIT);
        #endif

        /* Set return value */
        xRetVal = MEMIF_JOB_FAILED;
    }

    return(xRetVal);
}

/**
 *********************************************************************
 * Fee_Rb_GetAdapterJobResult(): Return the job result of the last accepted job coming from Adapter layer (ex. DGS adapter).
 *
 * This function returns the job result of the last job coming from Adapter layer.
 * The AUTOSAR interface Fee_GetJobResult() could not be used by adapter layer,
 * as it is not possible for Adapter layer to know if the last job completed by FEE was NvM, adapter or internal job.
 *
 * \return   FEE job result
 * \retval   MEMIF_JOB_OK:       The last job has been finished successfully
 * \retval   MEMIF_JOB_PENDING:  The last job is still pending
 * \retval   MEMIF_JOB_CANCELED: The last job has been canceled
 * \retval   MEMIF_JOB_FAILED:   The last job failed
 * \retval   MEMIF_BLOCK_INCONSISTENT: The requested block is inconsistent
 *                                     and may contain corrupt data
 * \retval   MEMIF_BLOCK_INVALID: The requested block has been invalidated,
 *                                the requested read operation can not
 *                                be performed.
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(MemIf_JobResultType, FEE_CODE) Fee_Rb_GetAdapterJobResult(void)
{
    VAR(MemIf_JobResultType, AUTOMATIC) xRetVal = Fee_JobResult[FEE_ADAPTER_JOB];   /* Function return */


    /* Check the FEE module status */
    if (Fee_GlobModuleState_st == MEMIF_UNINIT)
    {
        #if(STD_ON == FEE_DEV_ERROR_DETECT)
        /* Report error to DET */
        /* MR12 RULE 17.7 VIOLATION: Return value is not required */
        (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SID_RB_ADAPTERGETJOBRESULT, FEE_E_UNINIT);
        #endif

        /* Set return value */
        xRetVal = MEMIF_JOB_FAILED;
    }

    return(xRetVal);
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_PRESENT == 1 */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
