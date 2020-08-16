

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "Fee.h"

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

#include "Fee_Prv.h"

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
Fee_Prv_DriverState_ten Fee_Prv_DriverState_en      = FEE_PRV_DRIVERSTATE_UNINIT_E; /* Driver state                     */
MemIf_ModeType          Fee_Prv_DriverMode_en       = MEMIF_MODE_SLOW;              /* Driver mode                      */
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
static boolean Fee_Prv_BackgroundEnabled_b = FALSE; /* Erasing in background allowed    */
#define FEE_STOP_SEC_VAR_INIT_8
#include "Fee_MemMap.h"

/* Pointer to the order which is currently being processed */
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
static Fee_Prv_OrderJob_tst * Fee_Prv_ProcCurrentOrder_pcst = NULL_PTR;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

/*
 **********************************************************************************************************************
 * Implementation
 **********************************************************************************************************************
*/

/**
 * \brief   The main function does the actual work of the Fee.
 *          The more often it is scheduled the faster the Fee is.
*/
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"

void Fee_MainFunction(void)
{
    MemIf_JobResultType result_en = MEMIF_JOB_PENDING;

    /*
     * Measure main function execution time.
     * Attention: The result is not the actual time the main function really needed since it can be interrupted.
     *            Nevertheless it is a good indicator for debugging purposes.
     */
    Fee_Prv_DbgWatchStart(&Fee_Prv_DbgInfo_st.time_st.procMain_st);

    /* Reset the effort limitation */
    Fee_Prv_LibEffortReset();

    /*
     * Get the next order from the order unit.
     * Prioritization is done by the order unit, NvM has higher priority before any adapter.
     */
    if(NULL_PTR == Fee_Prv_ProcCurrentOrder_pcst)
    {
        Fee_Prv_ProcCurrentOrder_pcst = Fee_Prv_OrderBegin();
        if(
            (NULL_PTR                           != Fee_Prv_ProcCurrentOrder_pcst) &&
            (FEE_PRV_DRIVERSTATE_BACKGROUND_E   == Fee_Prv_DriverState_en       )
        )
        {
            Fee_Prv_FsIfCancel();
        }
    }

    /* Check whether a new order can be started */
    if(FEE_PRV_DRIVERSTATE_IDLE_E == Fee_Prv_DriverState_en)
    {
        /*
         * If a new order is available start the order in the Fs.
         * Then set the appropriate driver state.
         */
        if(NULL_PTR != Fee_Prv_ProcCurrentOrder_pcst)
        {
            switch(Fee_Prv_ProcCurrentOrder_pcst->type_en)
            {
                case FEE_PRV_ORDERTYPE_READ_E:
                    Fee_Prv_FsIfRead(Fee_Prv_ProcCurrentOrder_pcst);
                    Fee_Prv_DriverState_en = FEE_PRV_DRIVERSTATE_READ_E;
                break;

                case FEE_PRV_ORDERTYPE_WRITE_E:
                    Fee_Prv_FsIfWrite(Fee_Prv_ProcCurrentOrder_pcst);
                    Fee_Prv_DriverState_en = FEE_PRV_DRIVERSTATE_WRITE_E;
                break;

                case FEE_PRV_ORDERTYPE_INVALIDATE_E:
                    Fee_Prv_FsIfInvalidateBlock(Fee_Prv_ProcCurrentOrder_pcst);
                    Fee_Prv_DriverState_en = FEE_PRV_DRIVERSTATE_INVALIDATEBLOCK_E;
                break;

                case FEE_PRV_ORDERTYPE_BLOCKMAINTENANCE_E:
                    Fee_Prv_DriverState_en = FEE_PRV_DRIVERSTATE_BLOCKMAINTENANCE_E;
                break;

                default:
                    Fee_Prv_OrderEnd(Fee_Prv_ProcCurrentOrder_pcst, MEMIF_JOB_FAILED);
                break;
            }
        }
    }

    /* Based on the driver state left the Fs do the work */
    switch(Fee_Prv_DriverState_en)
    {
        case FEE_PRV_DRIVERSTATE_IDLE_E:
            /*
             * In case the Fee is currently IDLE,
             * check whether any maintenance functions can be executed in the background
             */
            if(Fee_Prv_BackgroundEnabled_b)
            {
                result_en = Fee_Prv_FsIfBackground();
                if(MEMIF_JOB_PENDING == result_en)
                {
                    Fee_Prv_DriverState_en = FEE_PRV_DRIVERSTATE_BACKGROUND_E;
                }
            }
        break;
        case FEE_PRV_DRIVERSTATE_BACKGROUND_E:          result_en = Fee_Prv_FsIfBackground();           break;
        case FEE_PRV_DRIVERSTATE_READ_E:                result_en = Fee_Prv_FsIfReadDo();               break;
        case FEE_PRV_DRIVERSTATE_WRITE_E:               result_en = Fee_Prv_FsIfWriteDo();              break;
        case FEE_PRV_DRIVERSTATE_INVALIDATEBLOCK_E:     result_en = Fee_Prv_FsIfInvalidateBlockDo();    break;
        case FEE_PRV_DRIVERSTATE_BLOCKMAINTENANCE_E:    result_en = MEMIF_JOB_OK;                       break;
        default:                                        result_en = MEMIF_JOB_FAILED;                   break;
    }

    /* In case the result is not MEMIF_JOB_PENDING any more reset the driver state to IDLE */
    if(MEMIF_JOB_PENDING != result_en)
    {
        /* If an order was finished inform the order unit */
        if(
            (NULL_PTR                           != Fee_Prv_ProcCurrentOrder_pcst) &&
            (FEE_PRV_DRIVERSTATE_BACKGROUND_E   != Fee_Prv_DriverState_en       )
        )
        {
            Fee_Prv_OrderEnd(Fee_Prv_ProcCurrentOrder_pcst, result_en);
        }
        Fee_Prv_ProcCurrentOrder_pcst   = NULL_PTR;
        Fee_Prv_DriverState_en          = FEE_PRV_DRIVERSTATE_IDLE_E;
        Fee_Rb_WorkingState_en          = FEE_RB_IDLE_E;
    }

    if(Fee_Prv_BackgroundEnabled_b)
    {
        Fee_Prv_DbgMainFunction();
    }

    Fee_Prv_DbgWatchStop(&Fee_Prv_DbgInfo_st.time_st.procMain_st, FALSE);
}

/**
 * \brief   Initialize the Fee.
*/

#if (FEE_AR42_API_COMPLIANCE == STD_ON)
/*MR12 RULE 8.13 VIOLATION: AR4.2 defines this function prototype with a non-constant pointer*/
void Fee_Init(Fee_ConfigType const * ConfigPtr)
#else
void Fee_Init(void)
#endif
{
    // ignore AR4.2 Config Pointer because Postcompile configuration is not possible
    #if (FEE_AR42_API_COMPLIANCE == STD_ON)
    if(ConfigPtr != NULL_PTR){}
    #endif

    /* Measure init time */
    Fee_Prv_DbgWatchStart(&Fee_Prv_DbgInfo_st.time_st.procInit_st);

    Fee_Prv_DriverState_en = FEE_PRV_DRIVERSTATE_INIT_E;

    /* Do not limit the effort to spend in the init - full speed is required */
    Fee_Prv_LibUseEffortLimit(FALSE);

    /*
     * Set the medium synchronous.
     * That means the flash is polled and Fls_MainFunction calls are triggered until flash jobs are finished.
     */
    Fee_Prv_MediumSetSync(TRUE);

    /* Initialize the file system - this will take the most time */
    Fee_Prv_FsIfInit();

    /* Compatibility: The polling state shall be visible since it is present in the public header file */
    Fee_stMain = FEE_NORMAL_MODE_E;

    /* Finally set the driver state to IDLE */
    Fee_Prv_DriverState_en = FEE_PRV_DRIVERSTATE_IDLE_E;

    Fee_Prv_DbgWatchStop(&Fee_Prv_DbgInfo_st.time_st.procInit_st, FALSE);

    /* If enabled read the debug block */
    Fee_Prv_DbgBlockRead();

    /* Stop the system if a block was lost */
    Fee_Prv_DbgCheckLayout();
}

/**
 * \brief   Mark end of the init.
 *          After calling this function erasing in the background is allowed.
 *          Also the Fee is set in a more cooperative mode to make sure task duration constraints are not violated.
*/
void Fee_Rb_EndInit(void)
{
    Fee_Prv_LibUseEffortLimit(TRUE);
    Fee_Prv_MediumSetSync(FALSE);
    Fee_Prv_BackgroundEnabled_b = TRUE;
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/
