

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "Fee.h"

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

#include "Fee_Prv.h"

#if (TRUE == FEE_PRV_CFG_DBG)


#if (TRUE == FEE_PRV_CFG_DBG_TIME)
#include "Mcu.h"
#endif

#if (TRUE == FEE_PRV_CFG_DBG_DUMP)
#include "stdio.h"
#include "rba_FlsPc.h"
#endif

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

Fee_Prv_DbgInfo_tst Fee_Prv_DbgInfo_st;
static Fee_Prv_Dbg_tst Fee_Prv_Dbg_st;

#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

#if (TRUE == FEE_PRV_CFG_DBG_CHECKLAYOUT)
#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
static uint8 Fee_Prv_DbgCheckLayoutBfr_au8[1u];
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
#endif

#if (TRUE == FEE_PRV_CFG_DBG_BLOCK)
#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
uint8 Fee_Prv_DbgBfr_au8[FEE_PRV_CFG_DBG_BLOCK_SIZE];
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
#endif



/*
 **********************************************************************************************************************
 * Static declarations
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
static void Fee_Prv_DbgHistInsert(uint32 * hist_pu32, uint32 value_u32, uint32 histSize_u32);
#if (TRUE == FEE_PRV_CFG_DBG_TIME)
static void Fee_Prv_DbgTeMerge(Fee_Prv_DbgTimeEntry_tst * t1_pst, Fee_Prv_DbgTimeEntry_tst const * t2_pcst);
#endif

/*
 **********************************************************************************************************************
 * Implementation
 **********************************************************************************************************************
*/

/**
 * \brief   Insert a value into a histogram.
 *          The histogram is in logarithmic scale with basis of 2.
 *          The intervals of the baskets in the histogram are
 *          [0, 1[
 *          [1, 2[
 *          [2, 4[
 *          [4, 8[
 *          ...
 *          [log(2,histSize_u32 - 1),infinity[
 *
 * \param   hist_pu32       Pointer to the histogram
 * \param   value_u32       Value that shall be inserted into the histogram
 * \param   histSize_u32    Size of the histogram
*/
static void Fee_Prv_DbgHistInsert(uint32 * hist_pu32, uint32 value_u32, uint32 histSize_u32)
{
    uint32 basket_u32 = 0u;

    while(
        (0u         < (value_u32 >> (basket_u32 + 1u))) &&
        (basket_u32 < (histSize_u32 - 1u))
    )
    {
        basket_u32++;
    }

    hist_pu32[basket_u32]++;
}

#if (TRUE == FEE_PRV_CFG_DBG_TIME)
/**
 * \brief   Merge histograms and maximum values of two time entries.
 *
 * \param   t1_pst      First time entry, will also be the target of the merge
 * \param   t2_pcst     Second time entry
*/
static void Fee_Prv_DbgTeMerge(Fee_Prv_DbgTimeEntry_tst * t1_pst, Fee_Prv_DbgTimeEntry_tst const * t2_pcst)
{
    uint32 a_u32;
    for(a_u32 = 0; a_u32 < FEE_PRV_CFG_DBG_TIME_HISTOGRAM_BASKETNUM; a_u32++)
    {
        t1_pst->hist_au32[a_u32] += t2_pcst->hist_au32[a_u32];
    }
    if(t1_pst->tiMax_u32 < t2_pcst->tiMax_u32)
    {
        t1_pst->tiMax_u32 = t2_pcst->tiMax_u32;
    }
}
#endif

/**
 * \brief   Main function of the debug unit to execute cyclic debugging actions.
*/
void Fee_Prv_DbgMainFunction(void)
{
#if (TRUE == FEE_PRV_CFG_DBG_BLOCK)
    /*
     * Only start a write of the debug block under the following conditions:
     * - A write of the debug block is requested
     * - Fee_Rb_EndInit was called (Fee_Prv_EraseEnabled_b = TRUE)
     * - No effort was spent already
     * - The Fee is currently idle
     */
    if(
        (TRUE                                       == Fee_Prv_Dbg_st.isDebugBlockWriteRequested_b  )   &&
        (Fee_Prv_LibEffortMeasure_st.effortCtr_u32  == Fee_Prv_ConfigMaxEffort_cu32                 )   &&
        (MEMIF_IDLE                                 == Fee_GetStatus()                              )
    )
    {
        uint32 packAdr_u32 = 0u;

        /* Pack the content of the debug struct into the write buffer */
#if (TRUE == FEE_PRV_CFG_DBG_TIME)
        if(sizeof(Fee_Prv_DbgBfr_au8) >= (packAdr_u32 + sizeof(Fee_Prv_DbgInfo_st.time_st)))
        {
            Fee_Prv_LibMemCopy(
                (uint8 const *)&Fee_Prv_DbgInfo_st.time_st,
                &Fee_Prv_DbgBfr_au8[packAdr_u32],
                sizeof(Fee_Prv_DbgInfo_st.time_st)
            );
            packAdr_u32 += sizeof(Fee_Prv_DbgInfo_st.time_st);
        }
#endif
#if (TRUE == FEE_PRV_CFG_DBG_ERASECOUNTERS)
        if(sizeof(Fee_Prv_DbgBfr_au8) >= (packAdr_u32 + sizeof(Fee_Prv_DbgInfo_st.eraseCounters_st)))
        {
            Fee_Prv_LibMemCopy(
                (uint8 const *)&Fee_Prv_DbgInfo_st.eraseCounters_st,
                &Fee_Prv_DbgBfr_au8[packAdr_u32],
                sizeof(Fee_Prv_DbgInfo_st.eraseCounters_st)
            );
            packAdr_u32 += sizeof(Fee_Prv_DbgInfo_st.eraseCounters_st);
        }
#endif

        /* Place an order at the Fee */
        if(E_OK == Fee_Write(FeeConf_FeeBlockConfiguration_Fee_DebugBlock, &Fee_Prv_DbgBfr_au8[0u]))
        {
            /* Track the number of debug block write for debugging purposes */
            Fee_Prv_Dbg_st.nrDbgBlockWrites_u32++;

            Fee_Prv_Dbg_st.isDebugBlockWriteRequested_b = FALSE;
        }
    }
#endif  /* FEE_PRV_CFG_DBG_BLOCK */
}

#if (TRUE == FEE_PRV_CFG_DBG_TIME)
/**
 * \brief   Start a timing measurement.
 *
 * \param   time_pst    Time entry which shall be used for measuring
*/
void Fee_Prv_DbgWatchStart(Fee_Prv_DbgTimeEntry_tst * time_pst)
{
    time_pst->tiTmp_u32 = Mcu_Rb_GetSysTicks();
}

/**
 * \brief   Stop a previously started timing measurement and evaluate the result.
 *
 * \param   time_pst            Time entry which was used for starting the measurement
 * \param   updateDebugBlock_b  In case the time is a new maximum trigger storing the debug block
 *
 * \seealso Fee_Prv_DbgWatchStart
*/
void Fee_Prv_DbgWatchStop(Fee_Prv_DbgTimeEntry_tst * time_pst, boolean updateDebugBlock_b)
{
    time_pst->tiLast_u32 = MCU_RB_TICKS_TO_US(Mcu_Rb_GetSysTicks() - time_pst->tiTmp_u32);
    time_pst->tiAcc_u32 += time_pst->tiLast_u32;
    if(time_pst->tiMax_u32 < time_pst->tiLast_u32)
    {
        time_pst->tiMax_u32 = time_pst->tiLast_u32;
        if(TRUE == updateDebugBlock_b)
        {
            Fee_Prv_Dbg_st.isDebugBlockWriteRequested_b = TRUE;
        }
    }
    Fee_Prv_DbgHistInsert(
        &time_pst->hist_au32[0],
        time_pst->tiLast_u32,
        FEE_PRV_CFG_DBG_TIME_HISTOGRAM_BASKETNUM
    );
}
#endif  /* FEE_PRV_CFG_DBG_TIME */

#if (TRUE == FEE_PRV_CFG_DBG_ERASECOUNTERS)
/**
 * \brief   Track the erase of a sector in the debug block.
 *
 * \param   ID of the sector that shall be tracked
*/
void Fee_Prv_DbgEraseCountersTrack(rba_FeeFs2_Prv_Sector_tst const * sector_pcst)
{
    uint32 id_u32 = rba_FeeFs2_Prv_SectorGetId(sector_pcst);

    /* Increment the sector specific erase counter */
    Fee_Prv_DbgInfo_st.eraseCounters_st.sectorDeleteAbs_au32[id_u32]++;

    /*
     * Find out the erase delta and remember it in the histogram.
     * Do not track the delta if the sector counter is 0.
     * In case the sector counter is 0 the sector was in undefined state on startup.
     */
    if(0u < sector_pcst->counter_u32)
    {
        uint32 delta_u32 = rba_FeeFs2_Prv_SectorGetMaxCounter() - sector_pcst->counter_u32;
        Fee_Prv_DbgHistInsert(
            &Fee_Prv_DbgInfo_st.eraseCounters_st.sectorDeleteDelta_aau32[id_u32][0u],
            delta_u32,
            FEE_PRV_CFG_DBG_ERASECOUNTERS_HISTOGRAM_BASKETNUM
        );
    }

    /* Trigger storing the debug info struct */
    Fee_Prv_Dbg_st.isDebugBlockWriteRequested_b = TRUE;
}
#endif  /* FEE_PRV_CFG_DBG_ERASECOUNTERS */

#if (TRUE == FEE_PRV_CFG_DBG_CHECKLAYOUT)
/**
 * \brief   Check that all blocks in a list are present - if not, go in a endless loop.
 *          This function is useful for reset tests.
 *          When a block gets lost this function prevents that the dump is modified further.
*/
void Fee_Prv_DbgCheckLayout(void)
{
    uint32 a_u32;
    for(a_u32 = 0; a_u32 < sizeof(Fee_Prv_DbgCheckLayoutBlocklist_au16)/sizeof(uint16); a_u32++)
    {
        if(E_OK == Fee_Read(Fee_Prv_DbgCheckLayoutBlocklist_au16[a_u32], 0, &Fee_Prv_DbgCheckLayoutBfr_au8[0], 1))
        {
            do
            {
                Fee_MainFunction();
                Fls_MainFunction();
            } while(MEMIF_JOB_PENDING == Fee_GetJobResult());

            if(
                (MEMIF_JOB_OK           != Fee_GetJobResult())  &&
                (MEMIF_BLOCK_INVALID    != Fee_GetJobResult())
            )
            {
                /* Block was lost - freeze the system */
                Fee_Prv_Dbg_st.freeze_b = TRUE;
                break;
            }
        }
        else
        {
            /* Something strange is going on - freeze the system */
            Fee_Prv_Dbg_st.freeze_b = TRUE;
            break;
        }
    }

    /* Endless loop to prevent that the dump is further modified */
    while(TRUE == Fee_Prv_Dbg_st.freeze_b)
    {
        Fee_Prv_DbgCheckLayoutBfr_au8[0]++;
    }
}
#endif  /* FEE_PRV_CFG_DBG_CHECKLAYOUT */

#if (TRUE == FEE_PRV_CFG_DBG_DUMP)
/**
 * \brief   Create a dump in the Fee development simulation.
 *          This is only active during development.
*/
void Fee_Prv_DbgDump(void)
{
    char filename_ac[50];
    sprintf(filename_ac, "Fee_Dump%u", Fee_Prv_Dbg_st.nrDump_u32);
    rba_FlsPc_SaveFlsDump(filename_ac);
    Fee_Prv_Dbg_st.nrDump_u32++;
}

/**
 * \brief   Create a dump if the job result is failed.
 *          Useful for finding unexpected errors.
 *          This is only active during development.
*/
void Fee_Prv_DbgFailDump(MemIf_JobResultType result_en)
{
    if(MEMIF_JOB_FAILED == result_en)
    {
        Fee_Prv_DbgDump();
    }
}
#endif  /* FEE_PRV_CFG_DBG_DUMP */

#if (TRUE == FEE_PRV_CFG_DBG_BLOCK)
void Fee_Prv_DbgBlockRead(void)
{
    Fee_Prv_OrderJob_tst            order_st;
    MemIf_JobResultType             jobResult_en;
    MemIf_Rb_MigrationResult_ten    dummyMigrationResult_en;
    uint32                          packAdr_u32;

    /* Setup order */
    order_st.type_en                = FEE_PRV_ORDERTYPE_READ_E;
    order_st.bfr_pu8                = (uint8 *)(&Fee_Prv_DbgBfr_au8[0u]);
    order_st.blockNumber_u16        = FeeConf_FeeBlockConfiguration_Fee_DebugBlock;
    order_st.length_u16             = FEE_PRV_CFG_DBG_BLOCK_SIZE;
    order_st.offset_u16             = 0u;
    order_st.migrationResult_pen    = &dummyMigrationResult_en;

    /* Perform the read */
    Fee_Prv_FsIfRead(&order_st);
    do
    {
        jobResult_en = Fee_Prv_FsIfReadDo();
        Fls_MainFunction();
    } while(MEMIF_JOB_PENDING == jobResult_en);

    if(MEMIF_JOB_OK != jobResult_en)
    {
        /* Set all to 0 */
        Fee_Prv_LibMemSet(&Fee_Prv_DbgBfr_au8[0u], 0u, sizeof(Fee_Prv_DbgBfr_au8));
    }

    packAdr_u32 = 0u;

#if (TRUE == FEE_PRV_CFG_DBG_TIME)
    /*
     * This function shall only be called at the end of Fee_Init.
     * At this place a value for the init time is already available.
     * This measurement shall not be overwritten but merged with the already available data.
     */
    Fee_Prv_DbgTimeEntry_tst init_st = Fee_Prv_DbgInfo_st.time_st.procInit_st;

    if(sizeof(Fee_Prv_DbgBfr_au8) >= (packAdr_u32 + sizeof(Fee_Prv_DbgInfo_st.time_st)))
    {
        Fee_Prv_LibMemCopy(
            &Fee_Prv_DbgBfr_au8[packAdr_u32],
            (uint8 *)&Fee_Prv_DbgInfo_st.time_st,
            sizeof(Fee_Prv_DbgInfo_st.time_st)
        );
        packAdr_u32 += sizeof(Fee_Prv_DbgInfo_st.time_st);
    }

    Fee_Prv_DbgTeMerge(&Fee_Prv_DbgInfo_st.time_st.procInit_st, &init_st);
#endif /* FEE_PRV_CFG_DBG_TIME */

#if (TRUE == FEE_PRV_CFG_DBG_ERASECOUNTERS)
    if(sizeof(Fee_Prv_DbgBfr_au8) >= (packAdr_u32 + sizeof(Fee_Prv_DbgInfo_st.eraseCounters_st)))
    {
        Fee_Prv_LibMemCopy(
            &Fee_Prv_DbgBfr_au8[packAdr_u32],
            (uint8 *)&Fee_Prv_DbgInfo_st.eraseCounters_st,
            sizeof(Fee_Prv_DbgInfo_st.eraseCounters_st)
        );
        packAdr_u32 += sizeof(Fee_Prv_DbgInfo_st.eraseCounters_st);
    }
#endif  /* FEE_PRV_CFG_DBG_ERASECOUNTERS */

}
#endif  /* FEE_PRV_CFG_DBG_BLOCK */

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

#endif  /* FEE_PRV_CFG_DBG */

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/
