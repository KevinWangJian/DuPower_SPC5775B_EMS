


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
#include "Fls.h"
#if (!defined(FLS_AR_RELEASE_MAJOR_VERSION) || (FLS_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
   // #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FLS_AR_RELEASE_MINOR_VERSION) || ((FLS_AR_RELEASE_MINOR_VERSION != 0) && (FLS_AR_RELEASE_MINOR_VERSION != 2)))
   // #error "AUTOSAR minor version undefined or mismatched"
#endif

#if (FEE_PRV_DEBUGGING != FALSE)
#include "Mcu.h"
/* FEE_PRV_DEBUGGING */
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#define FEE_PRV_REQ_STOPMODE 1

#if (FEE_PRESENT == 1)
/* Job mapping table */
#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
CONST (MemIf_JobResultType, AUTOMATIC) Fee_JobTypeMapping[FEE_NUM_RET_VAL_E] =
{
    MEMIF_JOB_PENDING,        /* FEE_ORDER_PENDING_E will be mapped to MEMIF_JOB_PENDING */
    MEMIF_JOB_OK,             /* FEE_ORDER_FINISHED_E will be mapped to MEMIF_JOB_OK
                                 (e.g. after writing or reading a block successfully)*/
    MEMIF_BLOCK_INVALID,      /* FEE_BLOCK_INVALIDATED_E will be mapped to MEMIF_BLOCK_INVALID
                                 (e.g. after reading back an invalidated block successfully) */
    MEMIF_BLOCK_INCONSISTENT, /* FEE_ERROR_E will be mapped to MEMIF_BLOCK_INCONSISTENT
                                 (e.g. if the block is not consistent in the flash) */
    MEMIF_JOB_PENDING,        /* FEE_SECTORCHANGE_E will be mapped to MEMIF_JOB_PENDING */
    MEMIF_JOB_PENDING,        /* FEE_SECTORFULL_E will be mapped to MEMIF_JOB_PENDING */
    MEMIF_JOB_FAILED,         /* FEE_ABORTED_E  will be mapped to MEMIF_JOB_FAILED
                                 (e.g. if not reachable states were called or the Fee/Fls
                                  are not intialized yet or a HW failure occured) */
    MEMIF_JOB_PENDING,        /* FEE_ERASE_SECTOR_E will be mapped to MEMIF_JOB_PENDING */
    MEMIF_JOB_PENDING         /* FEE_SEARCH_ABORTED_E will be mapped to MEMIF_JOB_PENDING
                                 (cannot be reached by any upper layer functions)*/
};
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"

#if (FEE_RB_ADDONS_CCAS != FALSE)
#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
VAR(boolean, AUTOMATIC) Fee_Rb_stRequestStopMode_b;
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
#endif

#if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
VAR(boolean, AUTOMATIC) Fee_Prv_stSuspendActiv_b;
VAR(boolean, AUTOMATIC) Fee_Prv_stHardReOrgErase_b;
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
#endif

#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
/* MR12 RULE 1504 VIOLATION: This is no function declaration but a variable only with an external linkage */
VAR(Fee_Rb_WorkingStateType_ten, AUTOMATIC) Fee_Rb_WorkingStateBackUp_en = FEE_RB_IDLE_E;    /* Backup of the working state */
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
VAR(uint8, AUTOMATIC) Fee_idxActQueueBackUp = (uint8)FEE_QUEUE_SIZE;    /* Backup queue index */
#define FEE_STOP_SEC_VAR_INIT_8
#include "Fee_MemMap.h"

#if (FEE_PRV_DEBUG_MONITOR != FALSE)
#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
VAR(Fee_DebugMonitoring_tst, AUTOMATIC)  Fee_DebugMonitoring;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
#endif

/* Workaround Overstamp invalid header to reduce init time */
#if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
#define FEE_START_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
VAR(uint8, AUTOMATIC) Fee_hdrBuffer_au8[FEE_PAGE_LEN] = {0};
#define FEE_STOP_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
#endif
/* END Workaround Overstamp invalid header to reduce init time */


/**
 *********************************************************************
 * Fee_MainFunction(): Main function of the module
 *
 * This function handles the requested orders and the internal
 * management operations. It has to be called cyclically by the
 * Fee's environment.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_MainFunction(void)
{
    VAR(uint8, AUTOMATIC) i;                                                        /* Loop counter */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal = FEE_ORDER_PENDING_E;                 /* Order return value */
    VAR(boolean, AUTOMATIC) stSectReorgInt_b;          /* Indicates an interruptable sector reorganization status */
    VAR(boolean, AUTOMATIC)  tmpContinueToErase_b = TRUE;
    #if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
    VAR(Fls_Rb_stSuspend_ten, AUTOMATIC) xRetSuspendVal;
    #endif
    /* Following requirements are handeled implicitly by the main function working mechanism:
     *
     * FEE169:
     * If the module initialization (started in the function Fee_Init) is completed in the module s main function, the
     * function Fee_MainFunction shall set the module status from MEMIF_BUSY_INTERNAL to MEMIF_IDLE once initialization
     * of the module has been successfully finished.
     *
     * FEE179:
     * If the current module status is MEMIF_BUSY_INTERNAL and if the internal management operation can be suspended
     * without jeopardizing the data consistency: the function Fee_MainFunction shall save all information which are
     * necessary to resume the internal management operation, suspend the internal management operation and start
     * processing the job requested by the upper layer.
     *
     * FEE180:
     * If the current module status is MEMIF_BUSY_INTERNAL and if the internal management operation can be aborted
     * without jeopardizing the data consistency: the function Fee_MainFunction shall save all information which are
     * necessary to restart the internal management operation, abort the internal management operation and start
     * processing the job requested by the upper layer.
     *
     * FEE181:
     * If an internal management operation has been suspended because of a job request from the upper layer, the
     * function Fee_MainFunction shall resume this internal management operation once the job requested by the upper
     * layer has been finished.
     *
     * FEE182:
     * If an internal management operation has been aborted because of a job request from the upper layer, the function
     * Fee_MainFunction shall restart this internal management operation once the job requested by the upper layer has
     * been finished.
     * */

    /* FEE057:
     * The function Fee_MainFunction shall asynchronously handle the read / write / erase / invalidate jobs
     * requested by the upper layer and internal management operations.
     * */
    /* Switch over the internal working state */
    switch (Fee_Rb_WorkingState_en)
    {
        #if (FEE_RB_ADDONS_CCAS == TRUE)
        /* Stop mode */
        case FEE_RB_STOPMODE_E:
        {
            Fee_Rb_stRequestStopMode_b = FEE_RB_REQUEST_STOP_MODE;
        }
        break;
        #endif

        /* Idle state */
        case FEE_RB_IDLE_E:
        {
            #if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
           /* Reset hard reorg erase marker, only relevant for the support of the suspend feature */
            Fee_Prv_stHardReOrgErase_b = FALSE;
            #endif


            /* Search new order in queue */
            Fee_idxActQueue_u8 = Fee_SearchNextOrder(TRUE);

            /* Check if any user orders have to be processed */
            if(Fee_idxActQueue_u8 != (uint8)FEE_QUEUE_SIZE)
            {
                Fee_LoadNextOrder();
            }
            else
            {
                /* No user orders are in the queue, check if at least one sector should be erased */
                for (i=0;i<FEE_NUM_FLASH_BANKS;i++)
                {
                    /* Check relevant sector states */
                    if(((Fee_LLSectorOrder_st[i].SecState_en == FEE_SECTOR_REQUEST2ERASE_E) ||
                        (Fee_LLSectorOrder_st[i].SecState_en == FEE_SECTOR_STATE_UNDEF_E)) &&
                        (Fee_Prv_stInit_u8 == FEE_PRV_ST_INIT_DONE))
                    {
                        /* Set the job type */
                        Fee_idxActQueue_u8 = (uint8)FEE_INTERNAL_JOB;

                        /* Mark a logical sector for an erase request in the global erase structure */
                        Fee_LLSetEraseSector(i);

                        /* Set the internal working state to erase */
                        Fee_Rb_WorkingState_en = FEE_RB_SECTOR_ERASE_E;

                        /* Leave the loop */
                        break;
                    }
                }

                /* Check for the necessity of a sector reorganization and perform at least
                 * one block transfer before executing the next user order (do not perform this
                 * during the ECU's initialization state in order to save time) */
                if(((Fee_LLCheckReorganizationNeed(FEE_REQUIRED_FREE_SPACE_BEFORE_SOFT_SR, 0) == FEE_SECTORFULL_E) &&
                    (Fee_Rb_WorkingState_en != FEE_RB_SECTOR_ERASE_E)) &&
                    (Fee_Prv_stInit_u8 == FEE_PRV_ST_INIT_DONE))
                {
                    /* Set the job type */
                    Fee_idxActQueue_u8 = (uint8)FEE_INTERNAL_JOB;

                    /* Set internal working state */
                    Fee_Rb_WorkingState_en = FEE_RB_SOFT_SECTOR_REORG_MODE_E;

                    /* Leave this case */
                    break;
                }
            }

            #if (FEE_RB_ADDONS_CCAS == TRUE)
            /* Check for a stop mode request */
            if (Fee_Rb_stRequestStopMode_b == FEE_RB_REQUEST_STOP_MODE)
            {
                /* Activate the stop mode due to a user request from the CC-AS adapter
                 * --> no other orders should be executed anymore */
                Fee_Rb_WorkingState_en = FEE_RB_STOPMODE_E;
            }
            #endif
        }
        break;

        /* A write or invalidate order was found */
        case FEE_RB_WRITE_MODE_E:
        case FEE_RB_INVALIDATE_MODE_E:
        {
            /* In case of NoFallback blocks a maintenance must be carried out before */
            #if ((FEE_RB_MAINTAIN != FALSE) && (FEE_NO_FALLBACK_ACTIVE != FALSE))
            switch (Fee_WriteStateNoFb_en)
            {
                /* Check the properties of the block and decide if the block has to be maintained first */
                case FEE_WRITE_NOFB_IDLE_E:
                {
                    /* Only double storage blocks with a NoFallback configuration have to be maintained */
                    // Shift of Flags not required, offset for security level is 0
                    if (((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
                            FEE_FLAG_SEC_LEVEL_MSK) == FEE_BLK_INT_DOUBLE_STORAGE) &&
                        ((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u))
                    {
                        Fee_WriteStateNoFb_en = FEE_WRITE_NOFB_MAINTAIN_E;
                    }
                    else
                    {
                        Fee_WriteStateNoFb_en = FEE_WRITE_NOFB_BLOCK_E;
                    }
                }
                break;

                /* Maintain the NoFallback block */
                case FEE_WRITE_NOFB_MAINTAIN_E:
                {
                    xRetVal = Fee_HLMaintainBlock();

                    if (xRetVal != FEE_ORDER_PENDING_E)
                    {
                        /* Proceed directly with the write order independent of a successful state
                         * -> Fee_HLMaintainBlock() also fails in case the block is not available on the medium */
                        Fee_WriteStateNoFb_en = FEE_WRITE_NOFB_BLOCK_E;

                        /* Order is not finished --> reset xRetVal to PENDING */
                        xRetVal = FEE_ORDER_PENDING_E;
                    }
                }
                break;

                /* Write the block */
                case FEE_WRITE_NOFB_BLOCK_E:
                {
                    /* Call the high level write function for order processing */
                    xRetVal = Fee_HLWriteBlock();

                    if (xRetVal != FEE_ORDER_PENDING_E)
                    {
                        /* Check if a sector reorganization needs to be executed
                         * Hint: SECTORFULL is also returned in case the write order would exceed the HSR threshold */
                        if(xRetVal == FEE_SECTORFULL_E)
                        {
                            /* Order is not finished --> reset xRetVal to PENDING */
                            xRetVal = FEE_ORDER_PENDING_E;

                            /* After Reorg return to init --> enforce maintain to be executed again after the reorg*/
                            Fee_WriteStateNoFb_en = FEE_WRITE_NOFB_IDLE_E;

                            /*trigger a reorganization */
                            Fee_TriggerHardSectorReorg(Fee_Rb_WorkingState_en);
                        }
                        else
                        {
                            /* The order was either finished successfully or with an error
                             * -> Reset the write state in both cases */
                            Fee_WriteStateNoFb_en = FEE_WRITE_NOFB_IDLE_E;
                        }
                    }
                }
                break;

                default:
                {
                    xRetVal = FEE_ERROR_E;
                }
                break;
            }
            #else
            /* Call the high level write function for order processing */
            xRetVal = Fee_HLWriteBlock();

            /* Check if a sector reorganization needs to be executed
             * Hint: SECTORFULL is also returned in case the write order would exceed the HSR threshold */
            if(xRetVal == FEE_SECTORFULL_E)
            {
                /* Order is not finished --> reset xRetVal to PENDING */
                xRetVal = FEE_ORDER_PENDING_E;

                /* Save the current working state and trigger a reorganization */
                Fee_TriggerHardSectorReorg(Fee_Rb_WorkingState_en);
            }
            #endif
        }
        break;

        #if (FEE_RB_MAINTAIN != FALSE)
        case FEE_RB_MAINTAIN_MODE_E:
        {
            /* Call the high level write function for order processing */
            xRetVal = Fee_HLMaintainBlock();
        }
        break;
        /* FEE_RB_MAINTAIN != FALSE */
        #endif

        /* A read order was found */
        case FEE_RB_READ_MODE_E:
        {
            /* Deviation from Autosar SWS:
             * ===========================
             * - Whether a block is invalidated or not is checked in the function Fee_HLReadBlock
             * - The block checksum is verified in the function Fee_HLReadBlock
             *
             * FEE075:
             * The function Fee_MainFunction shall check whether the block requested for reading has been
             * invalidated by the upper layer module. If so, the function Fee_MainFunction shall set the job result
             * to MEMIF_BLOCK_INVALID and call the job error notification function if configured.
             *
             * FEE023:
             * The function Fee_MainFunction shall check the consistency of the logical block being read before
             * notifying the caller. If an inconsistency of the read data is detected, the function Fee_MainFunction
             * shall set the job result to MEMIF_BLOCK_INCONSISTENT and call the error notification routine of the
             * upper layer if configured.
             *
             * Note: In this case the upper layer must not use the contents of the data buffer.
             * */

            /* Call the high level write function for order processing */
            xRetVal = Fee_HLReadBlock();
        }
        break;

        /* An internal erase order was found */
        case FEE_RB_SECTOR_ERASE_E:
        {
            #if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
            /* Check the Fls suspend status */
            xRetSuspendVal = Fls_Rb_GetSuspendStatus();

            /* Check if the suspend is already active ("accept and execute orders") */
            if(Fee_Prv_stSuspendActiv_b != FALSE)
            {
                /* Verify the suspend state */
                if(xRetSuspendVal == FLS_RB_ST_SUSPEND_IDLE_E)
                {
                    /* Reset the suspend done indicator */
                    Fee_Prv_stSuspendActiv_b = FALSE;
                }
                else if (xRetSuspendVal == FLS_RB_ST_RESUME_REQUESTED_E)
                {
                    /* Wait until it is resumed */
                }
                else
                {
                    /* Resume now */
                    if(Fls_Rb_Resume(FEE_PHYS_SEC_START0) != E_OK)
                    {
                        /* Do not continue to erase in order to avoid a double erase for the same sector */
                        tmpContinueToErase_b = FALSE;
                    }
                    else
                    {
                        /* Go on with the regular erase sequence */
                        tmpContinueToErase_b = TRUE;
                    }
                }
            }
            else
            {
                /* Suspension not active: check if it's accepted, all other suspend status will be
                 * ignored and go further to erase as usual */
                if(xRetSuspendVal == FLS_RB_ST_SUSPEND_ACC_AND_EXEC_ORDERS_E)
                {
                    /* Suspend is accepted:
                     * --> Set the status of suspend,
                     * --> Don't continue to erase
                     * --> Load the new order and execute it */
                    Fee_Prv_stSuspendActiv_b = TRUE;
                    tmpContinueToErase_b = FALSE;
                    Fee_LoadNextOrder();
                }
            }
            #endif
            if(tmpContinueToErase_b)
            {
                /* Call the low level erase function for order processing */
                if(Fee_LLEraseSector() != FEE_ORDER_PENDING_E)
                {
                    /* Check if a former user order has to be proceeded (this might be the case if
                     * a hard sector reorganization triggered the erase procedure) */
                    if(Fee_Rb_WorkingStateBackUp_en != FEE_RB_IDLE_E)
                    {
                        /* Go on with the original working state and queue index which triggered the sector reorg */
                        Fee_Rb_WorkingState_en  = Fee_Rb_WorkingStateBackUp_en;
                        Fee_idxActQueue_u8      = Fee_idxActQueueBackUp;

                        /* Reset the backup working type and queue index */
                        Fee_Rb_WorkingStateBackUp_en = FEE_RB_IDLE_E;
                        Fee_idxActQueueBackUp        = (uint8)FEE_QUEUE_SIZE;
                    }
                    else
                    {
                        /* Reset the internal working status */
                        Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;
                    }
                }
                #if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
                else if(!Fee_Prv_stHardReOrgErase_b)
                {
                    /* Search new order in queue */
                    Fee_idxActQueue_u8 = Fee_SearchNextOrder(FALSE);

                    /* Check for available higher prio orders */
                    if(Fee_idxActQueue_u8 != FEE_QUEUE_SIZE)
                    {
                        /* Verify the Fls main state */
                        if((Fee_Prv_stSuspendActiv_b == FALSE) && (Fls_GetStatus() != MEMIF_IDLE))
                        {
                            /* A suspend is necessary, pass the target address for the subsequent order */
                            if(Fls_Rb_Suspend(FEE_PHYS_SEC_START0) != E_OK)
                            {
                                /* Do nothing, stay in this erase statement */
                            }
                        }
                    }
                }
                else
                {
                    /* Do nothing */
                }
                #endif
            }
        }
        break;

        /* An internal soft reorganization order was found (checked if currently no user order is available) */
        case FEE_RB_SOFT_SECTOR_REORG_MODE_E:
        {
            /* Call the low level reorganization function for order processing */
            if(Fee_LLSectorReorganization(&stSectReorgInt_b) != FEE_ORDER_PENDING_E)
            {
                /* Reorganization is finished */
                Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;
            }
            else
            {
                /* Check for interruptability of the reorganization */
                if(stSectReorgInt_b != FALSE)
                {
                    /* Reset the internal working status although the reorganization
                     * might not be finished yet completely
                     * --> allow user orders to happen in between */
                    Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;
                }
            }
        }
        break;

        /* An internal hard reorganization order was found (checked if a user order was currently placed) */
        case FEE_RB_HARD_SECTOR_REORG_MODE_E:
        {
            /* Call the low level reorganization function for order processing */
            if (Fee_LLSectorReorganization(&stSectReorgInt_b) != FEE_ORDER_PENDING_E)
            {
                /* Go on with the original working state and queue index which triggered the sector reorg */
                Fee_Rb_WorkingState_en = Fee_Rb_WorkingStateBackUp_en;
                Fee_idxActQueue_u8     = Fee_idxActQueueBackUp;

                /* Reset the backup working type and queue index */
                Fee_Rb_WorkingStateBackUp_en = FEE_RB_IDLE_E;
                Fee_idxActQueueBackUp        = (uint8)FEE_QUEUE_SIZE;
            }
        }
        break;

        /* Default state */
        default:
        {
            /* Should never be reached, reset internal working status */
            Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;
        }
        break;
    }

    /* Note:
     * The Nvm believes that he is the only user of the Fee
     * --> Function call of Fee_GetJobResult should show the result for the last job which was started by the Nvm only.
     */

    /* FEE142: (requirement of function Fee_JobEndNotification)
     * If the job result is currently MEMIF_JOB_PENDING, the function Fee_JobEndNotification shall set the job
     * result to MEMIF_JOB_OK, else it shall leave the job result untouched.
     *
     * FEE143: (requirement of function Fee_JobErrorNotification)
     * If the job result is currently MEMIF_JOB_PENDING, the function Fee_JobErrorNotification shall set the job
     * result to MEMIF_JOB_OK, else it shall leave the job result untouched.*/

    /* Verify the current job owner */
    if (Fee_idxActQueue_u8 < (uint8)FEE_QUEUE_SIZE)
    {
        Fee_JobResult[Fee_idxActQueue_u8] = Fee_JobTypeMapping[xRetVal];

        /* For Write, Invalidate and Maintain jobs, if the request failed then return MEMIF_JOB_FAILED.
         * Above table may map the return value to MEMIF_BLOCK_INCONSISTENT, which is not a possible failure value for these requests.
         * Change done here instead of correcting the table, as the table is used for read request as well.
         * Also, for debugging purpose to have different internal return values for different error scenarios,
         * FEE_ERROR_E: for real hardware failures, FEE_ABORTED_E: for software failures like code reaching unreachable parts of the software. */
        if((Fee_JobResult[Fee_idxActQueue_u8] == MEMIF_BLOCK_INCONSISTENT) &&
           ((Fee_Rb_WorkingState_en == FEE_RB_WRITE_MODE_E) || (Fee_Rb_WorkingState_en == FEE_RB_INVALIDATE_MODE_E)
        #if (FEE_RB_MAINTAIN != FALSE)
            || (Fee_Rb_WorkingState_en == FEE_RB_MAINTAIN_MODE_E)
        #endif
           ))
        {
            Fee_JobResult[Fee_idxActQueue_u8] = MEMIF_JOB_FAILED;
        }
        else
        {
            /* Either the operation is still ongoing or completed successfuly or the request is not a write or invalidate requests.
             * In all these cases, do nothing, as status is already updated correctly. */
        }
    }

    /* Check the Fee order status independent from the job type */
    if(xRetVal != FEE_ORDER_PENDING_E)
    {
        /* A read, write or invalidate order was finished */

        /* Switch over the job result */
        switch(xRetVal)
        {
            /* Job finished */
            case FEE_ORDER_FINISHED_E:
            case FEE_BLOCK_INVALIDATED_E:
            {
                /* Check if a job end notification was configured for the currently finished order */
                if (Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].JobEndNotification_pfn != NULL_PTR)
                {
                    /* Call the user's job end notification */
                    Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].JobEndNotification_pfn();
                }
            }
            break;

            /* Job aborted with error */
            case FEE_ABORTED_E:
            case FEE_ERROR_E:
            {
                /* Check if a job end error was configured for the currently finished order */
                if (Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].JobErrorNotification_pfn != NULL_PTR)
                {
                    /* Call the user's job error notification */
                    Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].JobErrorNotification_pfn();
                }
            }
            break;

            /* Other cases */
            case FEE_ORDER_PENDING_E:
            case FEE_SECTORCHANGE_E:
            case FEE_SECTORFULL_E:
            default:
            {
                /* Cases should never be reached */
            }
            break;
        }


        /* A read, write or invalidate order was finished, reset respective queue entry and index */
        Fee_SrvSetFifoMode(FEE_NO_ORDER, Fee_idxActQueue_u8);
        Fee_idxActQueue_u8 = (uint8)FEE_QUEUE_SIZE;

        #if (FEE_PRV_DEBUGGING != FALSE)
        if ((Fee_Rb_WorkingState_en == FEE_RB_WRITE_MODE_E) ||
            (Fee_Rb_WorkingState_en == FEE_RB_INVALIDATE_MODE_E))
        {

            Fee_Prv_stModuleTest_st.Fee_WriteTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

            Fee_Prv_stModuleTest_st.Fee_WriteTimeDiff_u32 = MCU_RB_TIM0TICKS_TO_MS(
                                    Fee_Prv_stModuleTest_st.Fee_WriteTimeEnd_u32 -
                                    Fee_Prv_stModuleTest_st.Fee_WriteTimeStart_u32);
        }

        if(Fee_Rb_WorkingState_en == FEE_RB_READ_MODE_E)
        {
            Fee_Prv_stModuleTest_st.Fee_ReadTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

                            Fee_Prv_stModuleTest_st.Fee_ReadTimeDiff_u32 = MCU_RB_TIM0TICKS_TO_MS(
                                    Fee_Prv_stModuleTest_st.Fee_ReadTimeEnd_u32 -
                                    Fee_Prv_stModuleTest_st.Fee_ReadTimeStart_u32);
        }
        #endif


        /* Reset working state */
        Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;
    }

    /* Update module state, based on newest information in Main-Function */
    Fee_UpdateStatus();
}


/**
 *********************************************************************
 * Fee_SrvLoadNextOrder(): load next possible order in queue
 *
 * This function loads the next orders from the queue.
 * It has to be called only internally by the Fee's module.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
void Fee_LoadNextOrder(void)
{
    uint16 Length_u16;

    /* Switch over order modes */
    switch(Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en)
    {
        /* A read order has to be processed */
        case FEE_READ_ORDER:
        case FEE_FORCED_READ_ORDER:
        {
            /* Set internal working state */
            Fee_Rb_WorkingState_en = FEE_RB_READ_MODE_E;

            #if (FEE_PRV_DEBUGGING != FALSE)
            Fee_Prv_stModuleTest_st.Fee_ReadTimeStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
            #endif
        }
        break;

        /* A write- or invalidate order has to be processed */
        case FEE_WRITE_ORDER:
        case FEE_INVALIDATE_ORDER:
        {
            uint16 dataLen_u16 , blockPropIdx_u16;
            boolean noFbActive_b , doubleSecActive_b;


            if (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_INVALIDATE_ORDER)
            {
                dataLen_u16 = 0u;
            }
            else
            {
                dataLen_u16 = Fee_OrderFifo_st[Fee_idxActQueue_u8].Length_u16;
            }


            blockPropIdx_u16 = Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16;

            doubleSecActive_b = (Fee_BlockProperties_st[blockPropIdx_u16].Flags_u16 & FEE_FLAG_SEC_LEVEL_MSK) > 0u;

            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
            noFbActive_b  = (Fee_BlockProperties_st[blockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u;
            #else
            noFbActive_b = FALSE;
            #endif

            // Currently the size of a block is limited to one sector size
            //and even doubled in size it cannot overpass the MAXUINT16
            Length_u16 = (uint16) Fee_SrvCalcSpaceNeededForWrite(dataLen_u16 , doubleSecActive_b , noFbActive_b);


            /* Check for the necessity of a hard sector reorganization before executing any write orders.
             * Do not consider the security level because the low level function will check for enough
             * space copy wise so the first copy might get written before the HSR is triggered.
             * --> Additional check in HLD in order to fasten up reaction time
             * --> Hint: SECTORFULL is returned in case the respective threshold is already reached */
            if (Fee_LLCheckReorganizationNeed(FEE_REQUIRED_FREE_SPACE_BEFORE_HARD_SR, Length_u16) == FEE_SECTORFULL_E)
            {
                /* Save the current working state and queue index in order to come back afterwards */
                if (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_WRITE_ORDER)
                {
                    /* Save the current working state and trigger a reorganization */
                    Fee_TriggerHardSectorReorg(FEE_RB_WRITE_MODE_E);
                }
                else
                {
                    /* Save the current working state and trigger a reorganization */
                    Fee_TriggerHardSectorReorg(FEE_RB_INVALIDATE_MODE_E);
                }
            }
            else
            {
                /* Set internal working state */
                if (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_WRITE_ORDER)
                {
                    Fee_Rb_WorkingState_en = FEE_RB_WRITE_MODE_E;
                }
                else
                {
                    Fee_Rb_WorkingState_en = FEE_RB_INVALIDATE_MODE_E;
                }
            }
        }
        break;

        #if(FEE_RB_MAINTAIN != FALSE)
        case FEE_MAINTAIN_ORDER:
        {
            uint16 dataLen_u16 , blockPropIdx_u16;
            boolean noFbActive_b , doubleSecActive_b;

            /* Check for the necessity of a hard sector reorganization before executing any write orders.
             * Do not consider the security level because the low level function will check for enough
             * space copy wise so the first copy might get written before the HSR is triggered.
             * --> Additional check in HLD in order to fasten up reaction time */
            dataLen_u16 = Fee_OrderFifo_st[Fee_idxActQueue_u8].Length_u16;

            blockPropIdx_u16 = Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16;

            doubleSecActive_b = (Fee_BlockProperties_st[blockPropIdx_u16].Flags_u16 & FEE_FLAG_SEC_LEVEL_MSK) > 0u;

            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                noFbActive_b  = (Fee_BlockProperties_st[blockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u;
            #else
                noFbActive_b = FALSE;
            #endif

            Length_u16 = (uint16) Fee_SrvCalcSpaceNeededForWrite(dataLen_u16 , doubleSecActive_b , noFbActive_b);

            if(Fee_LLCheckReorganizationNeed(FEE_REQUIRED_FREE_SPACE_BEFORE_HARD_SR,Length_u16) == FEE_SECTORFULL_E)
            {
                /* Save the current working state and trigger a reorganization */
                Fee_TriggerHardSectorReorg(FEE_RB_MAINTAIN_MODE_E);
            }
            else
            {
                /* Set internal working state */
                Fee_Rb_WorkingState_en = FEE_RB_MAINTAIN_MODE_E;

                /* Set global module status to busy */
                Fee_GlobModuleState_st = MEMIF_BUSY;
            }
        }
        break;
        /* FEE_RB_MAINTAIN != FALSE */
        #endif

        /* No order has to be processed */
        case FEE_NO_ORDER:
        default:
        {
            /* This state should never be reached */
            Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;
        }
        break;
    }

    return;
}

/**
 *********************************************************************
 * Fee_SrvSearchNextOrder(): search the next possible order in queue
 *
 * This function searchs the next orders from the queue.
 * It has to be called only internally by the Fee's module.
 *
 * \param    boolean isIntOrder_b  check if internal order also found
 * \return
 * \retval   uint8 queue number
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
uint8 Fee_SearchNextOrder(boolean isIntOrder_b)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) idxActQueue_u8;
    VAR(uint8, AUTOMATIC) idexHighPrioOrder_u8;

    /* Check if a new job is in the queue. There are 2 prioritisations possible:
     *
     * 1. prioritisation of the job
     *    If a block is configured for FeeImmediateData=yes, this block will processed before the blocks
     *    with a normal priority (FeeImmediateData=no)
     *
     * 2. prioritisation of the job type:
     *    If there are 2 orders with the same priority, the following defined prioritisation will be used:
     *
     *   Low
     *    |     Adapter orders
     *    |     Nvm orders
     *    V     Fee - internal orders
     *   High
     *  */

    /* Reset high prio order index */
    idexHighPrioOrder_u8 = (uint8)FEE_QUEUE_SIZE;

    /* Reset queue activity index for order processing */
    idxActQueue_u8 = (uint8)FEE_QUEUE_SIZE;

    /* Loop over order queue */
    for(i=0; i<(uint8)FEE_QUEUE_SIZE; i++)
    {
        /* Check for an available queue entry */
        /* For idle state: no matter if it's internal job in running, new order can be accepted;
         * For suspending during erase: no internal order can be accepted */
        if((Fee_SrvGetFifoMode(i) != FEE_NO_ORDER) && (isIntOrder_b || (i != (uint8)FEE_INTERNAL_JOB)))
        {
            /* A new order was found */

            /* Set the queue activity index to the current entry */
            idxActQueue_u8 = i;

            /* If there is no order with a high priority available, the last found index will be assigned to
             * the Fee_idxActQueue_u8 because last entry in Fee_HlJobType_ten has the highest priority.
             * --> Last found order will be taken
             */
            /* Check for available high prio orders */
            if(Fee_OrderFifo_st[i].Prio_en == FEE_HIGH_PRIO_E)
            {
                /* This is the first high prio order */
                idexHighPrioOrder_u8 = i;
            }
        }
        else
        {
            /* Do nothing */
        }
    }

    /* Check for available high prio orders */
    if(idexHighPrioOrder_u8 != (uint8)FEE_QUEUE_SIZE)
    {
        /* At least one order with priority 1 was found, reset the queue activity index */
        idxActQueue_u8 = idexHighPrioOrder_u8;
    }

    return idxActQueue_u8;
}

/**
 *********************************************************************
 * Fee_TriggerHardSectorReorg(): Triggers a hard sector reorganization
 *
 * This function saves the passed working state and triggers a
 * a hard sector reorganization
 *
 * \param    Fee_Rb_WorkingStateType_ten    Current working state
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(void, FEE_CODE) Fee_TriggerHardSectorReorg(VAR(Fee_Rb_WorkingStateType_ten, FEE_VAR) WorkingState_en)
{
    /* Save the current working state and queue index in order to come back afterwards */
    Fee_Rb_WorkingStateBackUp_en = WorkingState_en;
    Fee_idxActQueueBackUp        = Fee_idxActQueue_u8;

    #if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
    /* Set for no suspend possible */
    Fee_Prv_stHardReOrgErase_b = TRUE;

    /* Resume if suspend active */
    if(Fee_Prv_stSuspendActiv_b != FALSE)
    {
        /* Check if the resume is accepted */
        if(Fls_Rb_Resume(FEE_PHYS_SEC_START0) == E_OK)
        {
            /* Set internal working state */
            Fee_Rb_WorkingState_en = FEE_RB_SECTOR_ERASE_E;
        }
        else
        {
            /* No error reaction necessary */
            ;
        }
    }
    else
    #endif
    {
        /* Set internal working state */
        Fee_Rb_WorkingState_en = FEE_RB_HARD_SECTOR_REORG_MODE_E;
    }

    /* Set the job type */
    Fee_idxActQueue_u8 = (uint8)FEE_INTERNAL_JOB;
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
