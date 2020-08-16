


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

#if(FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_GetStatus(): Return module status
 *
 * The function returns the FEE module state synchronously.
 *
 * \param    none
 * MEMIF_UNINIT        :  FEE is uninitialized
 * MEMIF_IDLE          :  FEE is currently idle
 * MEMIF_BUSY          :  FEE is currently busy in executing order
 * MEMIF_BUSY_INTERNAL :  FEE is currently busy with an internal
 *                        management operation (e.g. reorganization
 *                        or an adapter job)
 * \retval
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(MemIf_StatusType, FEE_CODE) Fee_GetStatus(void)
{
    /* Return the FEE module status */
    return(Fee_GlobModuleState_st);
}

/**
 *********************************************************************
 * Fee_UpdateStatus() Function to calculate the current module state
 *
 * This function calculates the current module state, based on the
 * Fee_Rb_WorkingState_en and the Fee_Rb_WorkingStateBackUp_en.
 * There are a few easy rules, how the global module state
 * (Fee_GlobModuleState_st) has to be calculated:
 * 1. if the module is not initialzed, do not modify the state
 * 2. if the working state is IDLE, the Module state is also IDLE
 * 3. if the working state is different from IDLE, it is necessary
 *    to check if the active order is from NvM (in this case the module
 *    state is busy) or if it is a internal or adapter job, in this
 *    case the globale module state is BUSY_INTERNAL
 * 4. if working state is ERASE or HARD_REORG it is necessary to check
 *    if current order is from NVM or internal/Adapter. In case of a
 *    active NvM-Order, the state is MEMIF_BUSY_INTERNAL.
 *
 * \param    none
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_UpdateStatus(void)
{
    /* check if module state is initialized, otherwise, state could not be modified */
    if (Fee_GlobModuleState_st != MEMIF_UNINIT){
        if ( (Fee_Rb_WorkingState_en == FEE_RB_IDLE_E) || (Fee_Rb_WorkingState_en == FEE_RB_SOFT_SECTOR_REORG_MODE_E) ||
             (Fee_Rb_WorkingState_en == FEE_RB_STOPMODE_E) ){
            Fee_GlobModuleState_st = MEMIF_IDLE;
        }else{
            /* the else path will be reached for the following Fee_Rb_WorkingState_en:
             * - FEE_RB_WRITE_MODE_E
             * - FEE_RB_READ_MODE_E
             * - FEE_RB_INVALIDATE_MODE_E
             * - FEE_RB_SECTOR_ERASE_E (backup-mode might be set)
             * - FEE_RB_HARD_SECTOR_REORG_MODE_E (backup-mode might be set)
             */
            if (Fee_idxActQueue_u8 != FEE_JOB_TYPE_NVM_E){
                /* this is not a NvM-Order (internal or adapter), in this case the state is busy internal. If a
                 * backup mode is set to FEE_JOB_TYPE_NVM_E, the state is MEMIF_BUSY, because a NvM-Order was
                 * interrupted. */
                if (Fee_idxActQueueBackUp == FEE_JOB_TYPE_NVM_E){
                    /* it the backup mode is a NVM job, this job was interrupted and so the state has to be BUSY
                     * instead of BUSY_INTERNAL */
                    Fee_GlobModuleState_st = MEMIF_BUSY;
                }else{
                    Fee_GlobModuleState_st = MEMIF_BUSY_INTERNAL;
                }
            }else{
                /* this is a NvM-Order */
                Fee_GlobModuleState_st = MEMIF_BUSY;
            }
        }
    }
}

/**
 *********************************************************************
 * Fee_Rb_GetMigrationResult(): Service to return the result of the
 *                              migration operation.
 *
 * This functionality is not supported in Fs1. Therefore this function
 * returns always the default value MEMIF_RB_MIGRATION_RESULT_INIT.
 * This is just a stub to pass the linker in case FEE is used and
 * FS1 target.
 *
 * \param   Blocknumber:   Auto generated Fee block number which
 *                         corresponds to the respective persistent ID
 *
 * \retval  MEMIF_RB_MIGRATION_RESULT_INIT_E: Initialization value,
 *                                            result not yet available
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
MemIf_Rb_MigrationResult_ten Fee_Rb_GetMigrationResult(uint16 Blocknumber)
{
    /* unused parameters */
    (void)(Blocknumber);

    /* Return with default value */
    return(MEMIF_RB_MIGRATION_RESULT_INIT_E);
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
