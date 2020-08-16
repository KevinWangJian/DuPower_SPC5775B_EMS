

#include "Ea.h"

#if (EA_PRESENT == 1)

#include "Ea_Prv.h"

#if (EA_DEV_ERROR_DETECT != FALSE)
#include "Det.h"
#endif

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
/* *********************************************************************************************************************
 * Req:                 Ea_GetJobResult
 *
 * Service name:        MemIf_JobResultType Ea_GetJobResult( void )
 * Syntax:              0x06
 *
 * Service ID[hex]:     Synchronous
 * Sync/Async:          Non Reentrant
 * Reentrancy:          None
 * Parameters (in):     None
 * Parameters (inout):  None
 * Parameters (out):    None
 * Return value:        MemIf_JobResultType - MEMIF_JOB_OK:             The last job has been finished successfully.
 *                                            MEMIF_JOB_PENDING:        The last job is waiting for execution or
 *                                                                      currently being executed.
 *                                            MEMIF_JOB_CANCELED:       The last job has been canceled (which means
 *                                                                      it failed).
 *                                            MEMIF_JOB_FAILED:         The last job has not been finished
 *                                                                      successfully (it failed).
 *                                            MEMIF_BLOCK_INCONSISTENT: The requested block is inconsistent, it may
 *                                                                      contain corrupted data.
 *                                            MEMIF_BLOCK_INVALID:      The requested block has been invalidated, the
 *                                                                      requested read operation can not be performed.
 * Description:         Service to query the result of the last accepted job issued by the upper layer software.
 * ****************************************************************************************************************** */
FUNC(MemIf_JobResultType, EA_CODE) Ea_GetJobResult(void)
{
    VAR(MemIf_JobResultType,AUTOMATIC) xRetVal = Ea_JobResult;

    /* Because the global internal JobStatus-Variable contains the Status of the last initiated Ea Block, the following
     * requirements are automatically fullfilled!
     *
     * EA035: The function Ea_GetJobResult shall return the status of the last job requested by the NVRAM manager.
     *        MEMIF_JOB_OK:         if the last job has been finished successfully.
     *        MEMIF_JOB_PENDING:    if the requested job is still waiting for execution or is currently being executed.
     *        MEMIF_JOB_CANCELED:   if the last job has been canceled by the upper layer.
     *        MEMIF_JOB_FAILED:     if the last job has failed.
     *        MEMIF_BLOCK_INCONSISTENT if the requested block is found to be inconsistent.
     *        MEMIF_BLOCK_INVALID if the requested block has been invalidated by the upper layer.
     * Note:  Only those jobs which have been requested directly by the upper layer shall have influence on the job
     *         result returned by the function Ea_GetJobResult. I.e. jobs which are issued by the EA module itself in
     *         the course of internal management operations shall not alter the job result.
     */

    if (Ea_GlobModuleState_st == MEMIF_UNINIT)
    {
        /* [EA134]:
         * If development error detection for the module Ea is enabled: the function Ea_GetJobResult shall check that
         * the module has been initialized. If this check fails, the function Ea_GetJobResult shall raise the development
         * error EA_E_NOT_INITIALIZED and return MEMIF_JOB_FAILED to the caller without performing the requested function.
         * */
        if(Ea_Rb_CheckInit(EA_SID_GETJOBRESULT) != E_OK)
        {
            xRetVal = MEMIF_JOB_FAILED;
        }
    }

    return (xRetVal);
}
#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
/* #if (EA_PRESENT == 1) */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

