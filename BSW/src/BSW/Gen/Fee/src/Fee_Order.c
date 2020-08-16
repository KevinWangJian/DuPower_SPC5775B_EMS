

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "Fee.h"

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

#include "Fee_Prv.h"
#include "Fee_Cfg_SchM.h"

#if (STD_ON == FEE_DEV_ERROR_DETECT)
#include "Det.h"
#endif

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
static Fee_Prv_Order_tst Fee_Prv_Order_st;  /* Internal variables of the order unit */
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

/*
 **********************************************************************************************************************
 * Static declaration
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
static void Fee_Prv_OrderDetReport(uint8 apiId_u8, uint8 errorId_u8);

static Std_ReturnType Fee_Prv_OrderDetCheckModuleInit       (uint8 apiId_u8                                                         );
static Std_ReturnType Fee_Prv_OrderDetCheckModuleIdle       (uint8 apiId_u8                                                         );
static Std_ReturnType Fee_Prv_OrderDetCheckBlkCfg           (uint8 apiId_u8, uint16 blkNr_u16                                       );
static Std_ReturnType Fee_Prv_OrderDetCheckAdrPtr           (uint8 apiId_u8, void const * bfr_pcv                                   );
static Std_ReturnType Fee_Prv_OrderDetCheckBlkOfs           (uint8 apiId_u8, uint16 blkNr_u16, uint16 blkOfs_u16                    );
static Std_ReturnType Fee_Prv_OrderDetCheckBlkLen           (uint8 apiId_u8, uint16 blkNr_u16, uint16 blkOfs_u16, uint16 blkLen_u16 );
static Std_ReturnType Fee_Prv_OrderDetCheckBlkLenNull       (uint8 apiId_u8, uint16 blkLen_u16                                      );
static Std_ReturnType Fee_Prv_OrderDetCheckBlkVarLenCfg     (uint8 apiId_u8, uint16 blkNr_u16, boolean active_b                     );
static Std_ReturnType Fee_Prv_OrderDetCheckBlkMigrationCfg  (uint8 apiId_u8, uint16 blkNr_u16, boolean active_b                     );

static Std_ReturnType Fee_Prv_OrderPut(uint8 apiId_u8, Fee_Prv_OrderJob_tst const * order_pcst);

/*
 **********************************************************************************************************************
 * Implementation
 **********************************************************************************************************************
*/

/**
 * \brief   Forward an error the Det module.
 *          In case Det error reporting is turned off, it is not forwarded here.
 *
 * \param   apiId_u8    The ID of the API
 * \param   errorId_u8  The ID of the error
*/
static void Fee_Prv_OrderDetReport(uint8 apiId_u8, uint8 errorId_u8)
{
    #if (STD_ON == FEE_DEV_ERROR_DETECT)
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, apiId_u8, errorId_u8);
    #else
    (void)apiId_u8;
    (void)errorId_u8;
    #endif
}


/**
 * \brief   Check whether the Fee is initialized (Fee_Init was called).
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 *
 * \retval  E_OK        Fee is initialized
 * \retval  E_NOT_OK    Fee is not initialized
*/
static Std_ReturnType Fee_Prv_OrderDetCheckModuleInit(uint8 apiId_u8)
{
    Std_ReturnType result_en = E_OK;
    if(MEMIF_UNINIT == Fee_GetStatus())
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_UNINIT);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Check whether the Fee is currently idle
 *          - Fee_Init was called
 *          - No internal or external action is being processed
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 *
 * \retval  E_OK        Fee_GetStatus() returns MEMIF_IDLE
 * \retval  E_NOT_OK    Fee_GetStatus() does not return MEMIF_IDLE
*/
static Std_ReturnType Fee_Prv_OrderDetCheckModuleIdle(uint8 apiId_u8)
{
    Std_ReturnType result_en;
    if(MEMIF_UNINIT == Fee_GetStatus())
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_UNINIT);
        result_en = E_NOT_OK;
    }
    else if(MEMIF_BUSY_INTERNAL == Fee_GetStatus())
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_BUSY_INTERNAL);
        result_en = E_NOT_OK;
    }
    else if(MEMIF_BUSY == Fee_GetStatus())
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_BUSY);
        result_en = E_NOT_OK;
    }
    else
    {
        result_en = E_OK;
    }
    return(result_en);
}

/**
 * \brief   Check whether a block number is valid.
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 * \param   blkNr_u16   The block number that shall be checked
 *
 * \retval  E_OK        The block number is valid
 * \retval  E_NOT_OK    The block number is not valid
*/
static Std_ReturnType Fee_Prv_OrderDetCheckBlkCfg(uint8 apiId_u8, uint16 blkNr_u16)
{
    Std_ReturnType result_en = E_OK;
    if(FEE_NUM_BLOCKS <= blkNr_u16)
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_INVALID_BLOCK_NO);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Check whether a pointer is a NULL_PTR.
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 * \param   bfr_pcv     The pointer that shall be checked
 *
 * \retval  E_OK        The pointer is not a NULL_PTR
 * \retval  E_NOT_OK    The pointer is a NULL_PTR
*/
static Std_ReturnType Fee_Prv_OrderDetCheckAdrPtr(uint8 apiId_u8, void const * bfr_pcv)
{
    Std_ReturnType result_en = E_OK;
    if(NULL_PTR == bfr_pcv)
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_INVALID_DATA_PTR);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Check whether an offset is longer or equal the block length.
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 * \param   blkNr_u16   The block number
 * \param   blkOfs_u16  The offset that shall be checked
 *
 * \retval  E_OK        The offset is smaller than the length of the block
 * \retval  E_NOT_OK    The offset is longer or equal the length of the block
*/
static Std_ReturnType Fee_Prv_OrderDetCheckBlkOfs(uint8 apiId_u8, uint16 blkNr_u16, uint16 blkOfs_u16)
{
    Std_ReturnType result_en = E_OK;
    if(blkOfs_u16 >= Fee_Prv_ConfigGetBlockLengthByBlockNr(blkNr_u16))
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_INVALID_BLOCK_OFS);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Check that length + offset do not exceed block length.
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 * \param   blkNr_u16   The block number
 * \param   blkOfs_u16  The offset
 * \param   blkLen_u16  The requested length
 *
 * \retval  E_OK        Offset + Length are bigger than the block length
 * \retval  E_NOT_OK    Offset + Length are smaller or equal the block length
*/
static Std_ReturnType Fee_Prv_OrderDetCheckBlkLen(uint8 apiId_u8, uint16 blkNr_u16, uint16 blkOfs_u16, uint16 blkLen_u16)
{
    Std_ReturnType result_en = E_OK;
    if((blkOfs_u16 + blkLen_u16) > Fee_Prv_ConfigGetBlockLengthByBlockNr(blkNr_u16))
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_INVALID_BLOCK_LEN);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Check that requested block length is not zero.
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 * \param   blkNr_u16   The block number
 * \param   blkLen_u16  The requested length
 *
 * \retval  E_OK        Requested length is bigger than zero
 * \retval  E_NOT_OK    Requested length is zero
*/
static Std_ReturnType Fee_Prv_OrderDetCheckBlkLenNull(uint8 apiId_u8, uint16 blkLen_u16)
{
    Std_ReturnType result_en = E_OK;
    if(0u == blkLen_u16)
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_INVALID_BLOCK_LEN);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Checks that requested block is configured for variable block length.
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 * \param   blkNr_u16   The block number
 * \param   active_b    Under which condition the det error should be set
 *
 * \retval  E_OK        Block is configured for variable block length
 * \retval  E_NOT_OK    Block is not configured for variable block length
*/
static Std_ReturnType Fee_Prv_OrderDetCheckBlkVarLenCfg(uint8 apiId_u8, uint16 blkNr_u16, boolean active_b)
{
    Std_ReturnType result_en = E_OK;
    if(active_b != Fee_Prv_ConfigIsBlockLengthVariable(blkNr_u16))
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_INVALID_VAR_BLK_LEN_CFG);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Checks that requested block is configured for migration.
 *
 * \param   apiId_u8    The API which requests this check, needed for Det_ReportError in case of failure
 * \param   blkNr_u16   The block number
 * \param   active_b    Under which condition the det error should be set
 *
 * \retval  E_OK        Block is configured for migration
 * \retval  E_NOT_OK    Block is not configured for migration
*/
static Std_ReturnType Fee_Prv_OrderDetCheckBlkMigrationCfg(uint8 apiId_u8, uint16 blkNr_u16, boolean active_b)
{
    Std_ReturnType result_en        = E_OK;
    uint16         persistentId_u16 = Fee_BlockProperties_st[blkNr_u16].BlockPersistentId_u16;

    if(active_b != Fee_Prv_ConfigIsMigrationActive(persistentId_u16))
    {
        Fee_Prv_OrderDetReport(apiId_u8, FEE_E_INVALID_MIGRATION_CFG);
        result_en = E_NOT_OK;
    }
    return(result_en);
}

/**
 * \brief   Try to place an order in the internal order slot.
 *          Based on block configuration the order slots is chosen.
 *          If the Fee is not ready or the order slot is occupied E_NOT_OK is returned.
 *
 * \param   apiId_u8    The ID of the API which places the order
 * \param   order_pcst  The order that shall be placed
 *
 * \retval  E_OK        Order placed successfully
 * \retval  E_NOT_OK    Order could not be placed
*/
static Std_ReturnType Fee_Prv_OrderPut(uint8 apiId_u8, Fee_Prv_OrderJob_tst const * order_pcst)
{
    Std_ReturnType              result_en       = E_NOT_OK;
    Fee_Prv_ConfigRequester_ten requester_en    = Fee_Prv_ConfigGetRequester(order_pcst->blockNumber_u16);

    SchM_Enter_Fee_Order();
    /*
     * Make sure the order slot is free.
     * A spin lock is needed since the main function might want to finish an order asynchronous.
     */
    if(FEE_PRV_ORDERTYPE_NONE_E == Fee_Prv_Order_st.jobs_ast[requester_en].type_en)
    {
        /* Set job and result of the current order */
        Fee_Prv_Order_st.jobs_ast   [requester_en] = *order_pcst;
        Fee_Prv_Order_st.results_aen[requester_en] = MEMIF_JOB_PENDING;
        result_en = E_OK;
    }
    SchM_Exit_Fee_Order();

    /*
     * In case placing the order of NvM or an adapter did not work trigger Det error.
     * Do not do this for internal orders.
     * Do not do this under interrupt lock!
     */
    if(E_NOT_OK == result_en)
    {
        switch(requester_en)
        {
            case FEE_PRV_REQUESTER_NVM_E:       Fee_Prv_OrderDetReport(apiId_u8, FEE_E_BUSY         );  break;
            case FEE_PRV_REQUESTER_ADAPTER_E:   Fee_Prv_OrderDetReport(apiId_u8, FEE_E_BUSY_INTERNAL);  break;
            default:                            /* Not DET report for internal orders */                break;
        }
    }

    return(result_en);
}

/**
 * \brief   Called by the main function if it wants to begin an order.
 *          NvM orders always have priority before adapter orders.
 *
 * \return  The next order that shall be started.
*/
Fee_Prv_OrderJob_tst * Fee_Prv_OrderBegin(void)
{
    uint32 requester_u32;
    Fee_Prv_OrderJob_tst * result_pst = NULL_PTR;

    for(requester_u32 = (uint32)FEE_PRV_REQUESTER_NVM_E; (requester_u32 < (uint32)FEE_PRV_REQUESTER_MAX_E) && (NULL_PTR == result_pst); requester_u32++)
    {
        if(FEE_PRV_ORDERTYPE_NONE_E != Fee_Prv_Order_st.jobs_ast[requester_u32].type_en)
        {
            /* Begin order under interrupt lock since at the same time an external requester might modify the order. */
            SchM_Enter_Fee_Order();
            result_pst = &Fee_Prv_Order_st.jobs_ast[requester_u32];
            SchM_Exit_Fee_Order();
        }
    }

    return(result_pst);
}

/**
 * \brief   Called by the main function if it wants to finish an order.
 *          If a callback is configured the callback is called.
 *
 * \param   order_pst   The order that shall be finished
 * \param   result_en   Result of that order
 *
 * \attention   This function calls Fee user callbacks under spin lock!
 *              That means the Fee user shall only do very short operations in its callback!
*/
void Fee_Prv_OrderEnd(Fee_Prv_OrderJob_tst * order_pst, MemIf_JobResultType result_en)
{
    Fee_Prv_ConfigNotification_tpfn notification_pfn    = NULL_PTR;
    Fee_Prv_ConfigRequester_ten     requester_en        = Fee_Prv_ConfigGetRequester(order_pst->blockNumber_u16);

     /* Find out the configured notification for this job results and this block */
    if(
        (MEMIF_JOB_OK           == result_en) ||
        (MEMIF_BLOCK_INVALID    == result_en)
    )
    {
        notification_pfn = Fee_Prv_ConfigGetJobEndNotification(order_pst->blockNumber_u16);
    }
    else
    {
        notification_pfn = Fee_Prv_ConfigGetJobErrorNotification(order_pst->blockNumber_u16);
    }

    /* Finish an order under spin lock */
    SchM_Enter_Fee_Order();

    Fee_Prv_Order_st.results_aen[requester_en] = result_en;

    /* Calculate migration result in case a read order is finished */
    if(FEE_PRV_ORDERTYPE_READ_E == order_pst->type_en)
    {
        /* Check if migration result was already set */
        if(MEMIF_RB_MIGRATION_RESULT_INIT_E == Fee_Prv_Order_st.firstInitMigrationResult_aen[order_pst->blockNumber_u16])
        {
            Fee_Prv_Order_st.firstInitMigrationResult_aen[order_pst->blockNumber_u16] =
                    Fee_Prv_Order_st.currentMigrationResult_en;
        }
    }

    order_pst->type_en = FEE_PRV_ORDERTYPE_NONE_E;

    if(NULL_PTR != notification_pfn)
    {
        notification_pfn();
    }

    SchM_Exit_Fee_Order();
}

/**
 * \brief   Start a read job.
 *
 * \param   Blocknumber     Block number as generated in Fee_Cfg.h - This is not the persistent ID!
 * \param   BlockOffset     The offset where the read shall start from in bytes
 * \param   DataBufferPtr   Buffer to read data to
 * \param   Length          Amount of data to read in bytes
 *
 * \retval  E_OK        Order accepted, will be executed asynchronously
 * \retval  E_NOT_OK    Order not accepted
*/
Std_ReturnType Fee_Read(uint16 Blocknumber, uint16 BlockOffset, uint8 * DataBufferPtr, uint16 Length)
{
    Std_ReturnType result_en = E_OK;

    /* Check parameters */
    if(E_OK != Fee_Prv_OrderDetCheckModuleInit    (FEE_SID_READ)                                  ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckAdrPtr        (FEE_SID_READ, (void const *)DataBufferPtr)     ) { result_en = E_NOT_OK; }
    if(E_OK == Fee_Prv_OrderDetCheckBlkCfg(FEE_SID_READ, Blocknumber))
    {
        if(E_OK != Fee_Prv_OrderDetCheckBlkOfs          (FEE_SID_READ, Blocknumber, BlockOffset)        ) { result_en = E_NOT_OK; }
        if(E_OK != Fee_Prv_OrderDetCheckBlkLen          (FEE_SID_READ, Blocknumber, BlockOffset, Length)) { result_en = E_NOT_OK; }
        if(E_OK != Fee_Prv_OrderDetCheckBlkMigrationCfg (FEE_SID_READ, Blocknumber, FALSE)              ) { result_en = E_NOT_OK; }
    }
    else
    {
        result_en = E_NOT_OK;
    }

    if(E_OK == result_en)
    {
        Fee_Prv_OrderJob_tst order_st;

        /*
         * Prepare order and try to place it.
         * If placing the order is not possible E_NOT_OK is returned by Fee_Prv_OrderPut.
         */
        order_st.type_en                = FEE_PRV_ORDERTYPE_READ_E;
        order_st.migrationResult_pen    = &(Fee_Prv_Order_st.currentMigrationResult_en);
        order_st.bfr_pu8                = DataBufferPtr;
        order_st.bfr_pcu8               = NULL_PTR;
        order_st.blockNumber_u16        = Blocknumber;
        order_st.length_u16             = Length;
        order_st.offset_u16             = BlockOffset;

        result_en = Fee_Prv_OrderPut(FEE_SID_READ, &order_st);
    }

    return(result_en);
}

/**
 * \brief   Starts a read job when block length is variable and calculated on runtime.
 *
 * \param   Blocknumber     Block number as generated in Fee_Cfg.h - This is not the persistent ID!
 * \param   BlockOffset     The offset where the read shall start from in bytes
 * \param   DataBufferPtr   Buffer to read data to
 * \param   Length          Amount of data to read in bytes
 *
 * \retval  E_OK        Order accepted, will be executed asynchronously
 * \retval  E_NOT_OK    Order not accepted
*/
Std_ReturnType Fee_Rb_VarLenRead(uint16 Blocknumber, uint16 BlockOffset, uint8 * DataBufferPtr, uint16 Length)
{
    Std_ReturnType result_en = E_OK;

    /* Check parameters */
    if(E_OK != Fee_Prv_OrderDetCheckModuleInit      (FEE_SID_RB_VARLENREAD)                                 ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckAdrPtr          (FEE_SID_RB_VARLENREAD, (void const *)DataBufferPtr)    ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckBlkLenNull      (FEE_SID_RB_VARLENREAD, Length)                         ) { result_en = E_NOT_OK; }

    if(E_OK == Fee_Prv_OrderDetCheckBlkCfg(FEE_SID_RB_VARLENREAD, Blocknumber))
    {
        if(E_OK != Fee_Prv_OrderDetCheckBlkMigrationCfg (FEE_SID_RB_VARLENREAD, Blocknumber, TRUE)          ) { result_en = E_NOT_OK; }
    }
    else
    {
        result_en = E_NOT_OK;
    }

    if(E_OK == result_en)
    {
        Fee_Prv_OrderJob_tst order_st;

        /*
         * Prepare order and try to place it.
         * If placing the order is not possible E_NOT_OK is returned by Fee_Prv_OrderPut.
         */
        order_st.type_en                = FEE_PRV_ORDERTYPE_READ_E;
        order_st.migrationResult_pen    = &(Fee_Prv_Order_st.currentMigrationResult_en);
        order_st.bfr_pu8                = DataBufferPtr;
        order_st.bfr_pcu8               = NULL_PTR;
        order_st.blockNumber_u16        = Blocknumber;
        order_st.length_u16             = Length;
        order_st.offset_u16             = BlockOffset;

        result_en = Fee_Prv_OrderPut(FEE_SID_RB_VARLENREAD, &order_st);
    }

    return(result_en);
}

/**
 * \brief   Start a write job.
 *
 * \param   Blocknumber     Block number as generated in Fee_Cfg.h - This is not the persistent ID!
 * \param   DataBufferPtr   Buffer to write data from
 *
 * \retval  E_OK        Order accepted, will be executed asynchronously
 * \retval  E_NOT_OK    Order not accepted
*/
/* MR12 RULE 8.13 VIOLATION: DataBufferPtr is not const because it is also not const in the public header file */
Std_ReturnType Fee_Write(uint16 Blocknumber, uint8 * DataBufferPtr)
{
    Std_ReturnType result_en = E_OK;

    /* Check parameters */
    if(E_OK != Fee_Prv_OrderDetCheckModuleInit    (FEE_SID_WRITE)                                 ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckAdrPtr        (FEE_SID_WRITE, (void const *)DataBufferPtr)    ) { result_en = E_NOT_OK; }

    if(E_OK == Fee_Prv_OrderDetCheckBlkCfg(FEE_SID_WRITE, Blocknumber))
    {
        if(E_OK != Fee_Prv_OrderDetCheckBlkVarLenCfg  (FEE_SID_WRITE, Blocknumber, FALSE)         ) { result_en = E_NOT_OK; }
    }
    else
    {
        result_en = E_NOT_OK;
    }

    if(E_OK == result_en)
    {
        Fee_Prv_OrderJob_tst order_st;

        /*
         * Prepare order and try to place it.
         * If placing the order is not possible E_NOT_OK is returned by Fee_Prv_OrderPut.
         */
        order_st.type_en            = FEE_PRV_ORDERTYPE_WRITE_E;
        order_st.bfr_pu8            = NULL_PTR;
        order_st.bfr_pcu8           = DataBufferPtr;
        order_st.blockNumber_u16    = Blocknumber;
        order_st.length_u16         = Fee_Prv_ConfigGetBlockLengthByBlockNr(Blocknumber);
        order_st.offset_u16         = 0;

        result_en = Fee_Prv_OrderPut(FEE_SID_WRITE, &order_st);
    }

    return(result_en);
}

/**
 * \brief   Starts a write job when block length is variable and calculated on runtime.
 *
 * \param   Blocknumber     Block number as generated in Fee_Cfg.h - This is not the persistent ID!
 * \param   DataBufferPtr   Buffer to write data from
 * \param   Length          NV block length
 *
 * \retval  E_OK        Order accepted, will be executed asynchronously
 * \retval  E_NOT_OK    Order not accepted
*/
/* MR12 RULE 8.13 VIOLATION: DataBufferPtr is not const because it is also not const in the public header file */
Std_ReturnType Fee_Rb_VarLenWrite(uint16 Blocknumber, uint8 * DataBufferPtr, uint16 Length)
{
    Std_ReturnType result_en = E_OK;

    /* Check parameters */
    if(E_OK != Fee_Prv_OrderDetCheckModuleInit    (FEE_SID_RB_VARLENWRITE)                                 ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckAdrPtr        (FEE_SID_RB_VARLENWRITE, (void const *)DataBufferPtr)    ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckBlkLenNull    (FEE_SID_RB_VARLENWRITE, Length)                         ) { result_en = E_NOT_OK; }

    if(E_OK == Fee_Prv_OrderDetCheckBlkCfg(FEE_SID_RB_VARLENWRITE, Blocknumber))
    {
        if(E_OK != Fee_Prv_OrderDetCheckBlkVarLenCfg  (FEE_SID_RB_VARLENWRITE, Blocknumber, TRUE)          ) { result_en = E_NOT_OK; }
    }
    else
    {
        result_en = E_NOT_OK;
    }

    if(E_OK == result_en)
    {
        Fee_Prv_OrderJob_tst order_st;

        /*
         * Prepare order and try to place it.
         * If placing the order is not possible E_NOT_OK is returned by Fee_Prv_OrderPut.
         */
        order_st.type_en            = FEE_PRV_ORDERTYPE_WRITE_E;
        order_st.bfr_pu8            = NULL_PTR;
        order_st.bfr_pcu8           = DataBufferPtr;
        order_st.blockNumber_u16    = Blocknumber;
        order_st.length_u16         = Length;
        order_st.offset_u16         = 0;

        result_en = Fee_Prv_OrderPut(FEE_SID_RB_VARLENWRITE, &order_st);
    }

    return(result_en);
}

/**
 * \brief   Start an invalidate job.
 *
 * \param   Blocknumber     Block number as generated in Fee_Cfg.h - This is not the persistent ID!
 *
 * \retval  E_OK        Order accepted, will be executed asynchronously
 * \retval  E_NOT_OK    Order not accepted
*/
Std_ReturnType Fee_InvalidateBlock(uint16 Blocknumber)
{
    Std_ReturnType result_en = E_OK;

    /* Check parameters */
    if(E_OK != Fee_Prv_OrderDetCheckModuleInit    (FEE_SID_INVALIDATE)                ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckBlkCfg        (FEE_SID_INVALIDATE, Blocknumber)   ) { result_en = E_NOT_OK; }

    if(E_OK == result_en)
    {
        Fee_Prv_OrderJob_tst order_st;

        /*
         * Prepare order and try to place it.
         * If placing the order is not possible E_NOT_OK is returned by Fee_Prv_OrderPut.
         */
        order_st.type_en            = FEE_PRV_ORDERTYPE_INVALIDATE_E;
        order_st.bfr_pu8            = NULL_PTR;
        order_st.bfr_pcu8           = NULL_PTR;
        order_st.blockNumber_u16    = Blocknumber;
        order_st.length_u16         = 0;
        order_st.offset_u16         = 0;

        result_en = Fee_Prv_OrderPut(FEE_SID_INVALIDATE, &order_st);
    }

    return(result_en);
}

/**
 * \brief   Erase immediate data.
 *
 * \param   Blocknumber     Block number as generated in Fee_Cfg.h - This is not the persistent ID!
 *
 * \retval  E_OK        Order accepted, will be executed asynchronously
 * \retval  E_NOT_OK    Order not accepted
 *
 * \attention   Currently not supported!
*/
Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber)
{
    (void)BlockNumber;
    return(E_NOT_OK);
}

/**
 * \brief   Cancel running operation.
 *
 * \attention   Currently not supported!
*/
void Fee_Cancel(void)
{
}

/**
 * \brief   Get the status of the Fee module.
 *
 * \retval  MEMIF_UNINIT        The Fee_Init was not called yet
 * \retval  MEMIF_IDLE          The Fee_Init was called, NvM and adapter slots are free, no background operation running
 * \retval  MEMIF_BUSY_INTERNAL a) Adapter job is running b) Background operation (maybe erase) is running c) Fee_Init is running
 * \retval  MEMIF_BUSY          NvM order is running
*/
MemIf_StatusType Fee_GetStatus(void)
{
    MemIf_StatusType result_en = MEMIF_UNINIT;

    if(FEE_PRV_DRIVERSTATE_INIT_E < Fee_Prv_DriverState_en)
    {
        result_en = MEMIF_IDLE;
        if(FEE_PRV_ORDERTYPE_NONE_E != Fee_Prv_Order_st.jobs_ast[FEE_PRV_REQUESTER_NVM_E].type_en)
        {
            result_en = MEMIF_BUSY;
        }
        else if(
            (FEE_PRV_ORDERTYPE_NONE_E != Fee_Prv_Order_st.jobs_ast[FEE_PRV_REQUESTER_ADAPTER_E].type_en ) ||
            (FEE_PRV_ORDERTYPE_NONE_E != Fee_Prv_Order_st.jobs_ast[FEE_PRV_REQUESTER_DEBUG_E].type_en   )
        )
        {
            result_en = MEMIF_BUSY_INTERNAL;
        }
        else if(FEE_PRV_DRIVERSTATE_BACKGROUND_E == Fee_Prv_DriverState_en)
        {
            result_en = MEMIF_BUSY_INTERNAL;
        }
        else
        {
        }
    }
    else if(FEE_PRV_DRIVERSTATE_INIT_E == Fee_Prv_DriverState_en)
    {
        result_en = MEMIF_BUSY_INTERNAL;
    }
    else
    {
    }

    return(result_en);
}

/**
 * \brief   Return the result of the last NvM order.
 *
 * \retval  MEMIF_JOB_OK                Last job executed successfully
 * \retval  MEMIF_JOB_FAILED            Last job failed unexpected
 * \retval  MEMIF_JOB_PENDING           Last job is still running
 * \retval  MEMIF_BLOCK_INCONSISTENT    Last job was a read and
 *                                      a) Not a single instance of all instances has consistent data
 *                                      b) The block is not present at all
 * \retval  MEMIF_BLOCK_INVALIDATED     Last job was a read and the block was invalidated intentionally
 *
 * \attention   Since the job result can change asynchronously a time consuming spin lock is needed!
 *              Please consider this when creating do/while wait loops for the Fee.
*/
MemIf_JobResultType Fee_GetJobResult(void)
{
    MemIf_JobResultType result_en;

    if(E_OK != Fee_Prv_OrderDetCheckModuleInit(FEE_SID_GETJOBRESULT))
    {
        result_en = MEMIF_JOB_FAILED;
    }
    else
    {
        /* Copy job result under spin lock since this can change every time asynchronously */
        SchM_Enter_Fee_Order();
        result_en = Fee_Prv_Order_st.results_aen[FEE_PRV_REQUESTER_NVM_E];
        SchM_Exit_Fee_Order();
    }

    return(result_en);
}

/**
 * \brief   Return the result of the last Adapter order.
 *
 * \retval  MEMIF_JOB_OK                Last job executed successfully
 * \retval  MEMIF_JOB_FAILED            Last job failed unexpected
 * \retval  MEMIF_JOB_PENDING           Last job is still running
 * \retval  MEMIF_BLOCK_INCONSISTENT    Last job was a read and
 *                                      a) Not a single instance of all instances has consistent data
 *                                      b) The block is not present at all
 * \retval  MEMIF_BLOCK_INVALIDATED     Last job was a read and the block was invalidated intentionally
 *
 * \attention   Since the job result can change asynchronously a time consuming spin lock is needed!
 *              Please consider this when creating do/while wait loops for the Fee.
*/
MemIf_JobResultType Fee_Rb_GetAdapterJobResult(void)
{
    MemIf_JobResultType result_en;

    if(E_OK != Fee_Prv_OrderDetCheckModuleInit(FEE_SID_RB_ADAPTERGETJOBRESULT))
    {
        result_en = MEMIF_JOB_FAILED;
    }
    else
    {
        /* Copy job result under spin lock since this can change every time asynchronously */
        SchM_Enter_Fee_Order();
        result_en = Fee_Prv_Order_st.results_aen[FEE_PRV_REQUESTER_ADAPTER_E];
        SchM_Exit_Fee_Order();
    }

    return(result_en);
}

/**
 * \brief   Returns the migration result of data reading during initialisation
 *
 * \param  Blocknumber  Block number as generated in Fee_Cfg.h
 *
 * \retval  MEMIF_RB_MIGRATION_RESULT_INIT_E               Initialization value, result not yet available
 * \retval  MEMIF_RB_MIGRATION_RESULT_NOT_NECESSARY_E      RAM size == EEPROM size (migration not necessary)
 * \retval  MEMIF_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E    RAM size < EEPROM size (remaining data discarded)
 * \retval  MEMIF_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E     RAM size > EEPROM size (remaining data filled with zero)
 * \retval  MEMIF_RB_MIGRATION_RESULT_NOT_DONE_E           Migration not done, because data were not read
 * \retval  MEMIF_RB_MIGRATION_RESULT_DEACTIVATED_E        Migrations is deactivated by configuration
 *
 * \attention   Since the migration result can change asynchronously a time consuming spin lock is needed!
 *              Please consider this when creating do/while wait loops for the Fee.
*/
MemIf_Rb_MigrationResult_ten Fee_Rb_GetMigrationResult(uint16 Blocknumber)
{
    MemIf_Rb_MigrationResult_ten result_en;

    if(E_OK != Fee_Prv_OrderDetCheckModuleInit(FEE_SID_GETMIGRATIONRESULT))
    {
        result_en = MEMIF_RB_MIGRATION_RESULT_INIT_E;
    }
    else if(E_OK != Fee_Prv_OrderDetCheckBlkCfg(FEE_SID_GETMIGRATIONRESULT,Blocknumber))
    {
        result_en = MEMIF_RB_MIGRATION_RESULT_INIT_E;
    }
    else
    {
        /* Copy migration result under spin lock since this can change every time asynchronously */
        SchM_Enter_Fee_Order();
        result_en = Fee_Prv_Order_st.firstInitMigrationResult_aen[Blocknumber];
        SchM_Exit_Fee_Order();
    }

    return(result_en);
}



#if (STD_ON == FEE_SET_MODE_SUPPORTED)
/**
 * \brief   Set the mode of the Fee and the underlying flash driver.
 *          It must be assured that the main function is not running when calling this interface.
 *
 * \param   Mode    New mode
*/
void Fee_SetMode(MemIf_ModeType Mode)
{
    if(E_OK != Fee_Prv_OrderDetCheckModuleIdle(FEE_SID_SETMODE))
    {
        /* Do nothing */
    }
    else
    {
        if(FEE_PRV_DRIVERSTATE_IDLE_E == Fee_Prv_DriverState_en)
        {
            Fls_SetMode(Mode);
            SchM_Enter_Fee_Order();
            Fee_Prv_DriverMode_en = Mode;
            SchM_Exit_Fee_Order();
        }
    }
}
#endif

#if (STD_ON == FEE_VERSION_INFO_API)
/**
 * \brief   Get version information about this Fee.
 *
 * \param   VersionInfoPtr  Pointer to a standard version struct that shall be filled
*/
void Fee_GetVersionInfo(Std_VersionInfoType * VersionInfoPtr)
{
    if(E_OK != Fee_Prv_OrderDetCheckAdrPtr(FEE_SID_GETVERSIONINFO, (void const *)VersionInfoPtr))
    {
        /* Do nothing */
    }
    else
    {
        VersionInfoPtr->vendorID            = FEE_VENDOR_ID;
        VersionInfoPtr->moduleID            = FEE_MODULE_ID;
        VersionInfoPtr->sw_major_version    = FEE_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version    = FEE_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version    = FEE_SW_PATCH_VERSION;
    }
}
#endif

#if(FEE_RB_MAINTAIN != FALSE)
/**
 * \brief   Make sure that the double storage of a specified block number is intact.
 *
 * \param   Blocknumber     The block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \attention   This API is currently not supported!
 *              Nevertheless E_OK is returned and the job result is set to MEMIF_JOB_OK if there is currently no job running.
 *              Reason:
 *              There is an automatic repair mechanism which will repair the redundant storage if it gets lost once.
 *              This is active during a soft reorganization of the DFLASH in the background.
*/
Std_ReturnType Fee_Rb_BlockMaintenance(uint16 Blocknumber)
{
    Std_ReturnType result_en = E_OK;

    /* Check parameters */
    if(E_OK != Fee_Prv_OrderDetCheckModuleInit    (FEE_SID_MAINTAIN)                ) { result_en = E_NOT_OK; }
    if(E_OK != Fee_Prv_OrderDetCheckBlkCfg        (FEE_SID_MAINTAIN, Blocknumber)   ) { result_en = E_NOT_OK; }

    if(E_OK == result_en)
    {
        Fee_Prv_OrderJob_tst order_st;

        /*
         * Prepare order and try to place it.
         * If placing the order is not possible E_NOT_OK is returned by Fee_Prv_OrderPut.
         */
        order_st.type_en            = FEE_PRV_ORDERTYPE_BLOCKMAINTENANCE_E;
        order_st.bfr_pu8            = NULL_PTR;
        order_st.bfr_pcu8           = NULL_PTR;
        order_st.blockNumber_u16    = Blocknumber;
        order_st.length_u16         = Fee_Prv_ConfigGetBlockLengthByBlockNr(Blocknumber);
        order_st.offset_u16         = 0;

        result_en = Fee_Prv_OrderPut(FEE_SID_MAINTAIN, &order_st);
    }

    return(result_en);
}
#endif

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/
