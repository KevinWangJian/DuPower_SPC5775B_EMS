

#ifndef FEE_PRV_FSIF_H
#define FEE_PRV_FSIF_H

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 * The FsIf (Filesystem-Interace) unit is the connection from the main function to the actual file system.
 * Currently only one filesystem (Fs2) is supported.
 * Due to that the FsIf unit is currently only a direct mapper to Fs2.
*/

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#if(2 == FEE_PRV_CFG_SELECTED_FS)
#include "rba_FeeFs2.h"
#endif

/*
 **********************************************************************************************************************
 * Inlines
 **********************************************************************************************************************
*/

/**
 * \brief   Initialize a file system.
*/
LOCAL_INLINE void Fee_Prv_FsIfInit(void)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    rba_FeeFs2_Init();
    #endif
}

/**
 * \brief   Let the file system start a read job.
 *
 * \param   order_pcst  Order which contains all information about the read job.
*/
LOCAL_INLINE void Fee_Prv_FsIfRead(Fee_Prv_OrderJob_tst const * order_pcst)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    rba_FeeFs2_Read(order_pcst);
    #endif
}

/**
 * \brief   Let the file system start a write job.
 *
 * \param   order_pcst  Order which contains all information about the write job.
*/
LOCAL_INLINE void Fee_Prv_FsIfWrite(Fee_Prv_OrderJob_tst const * order_pcst)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    rba_FeeFs2_Write(order_pcst);
    #endif
}

/**
 * \brief   Let the file system start an invalidate job.
 *
 * \param   order_pcst  Order which contains all information about the invalidate job.
*/
LOCAL_INLINE void Fee_Prv_FsIfInvalidateBlock(Fee_Prv_OrderJob_tst const * order_pcst)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    rba_FeeFs2_InvalidateBlock(order_pcst);
    #endif
}

/**
 * \brief   Let the file system start an erase immediate job.
 *
 * \param   order_pcst  Order which contains all information about the erase immediate job.
 *
 * \attention   Currently no file system supports erase immediate.
*/
LOCAL_INLINE void Fee_Prv_FsIfEraseImmediateBlock(Fee_Prv_OrderJob_tst const * order_pcst)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    rba_FeeFs2_EraseImmediateBlock(order_pcst);
    #endif
}

/**
 * \brief   Let the file system cancel a job.
 *          Can also be called when a background maintenance action shall be called.
 *          This is for example used to abort a running soft reorganization.
 *
*/
LOCAL_INLINE void Fee_Prv_FsIfCancel(void)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    rba_FeeFs2_Cancel();
    #endif
}


/**
 * \brief   Do the work of a write job.
 *
 * \retval  MEMIF_JOB_PENDING   Write is not yet finished
 * \retval  MEMIF_JOB_OK        Write finished successfully
 * \retval  MEMIF_JOB_FAILED    Write failed
*/
LOCAL_INLINE MemIf_JobResultType Fee_Prv_FsIfWriteDo(void)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    return(rba_FeeFs2_WriteDo());
    #endif
}

/**
 * \brief   Do the work of a read job.
 *
 * \retval  MEMIF_JOB_PENDING           Read is not yet finished
 * \retval  MEMIF_JOB_OK                Read finished successfully
 * \retval  MEMIF_BLOCK_INCONSISTENT    Block was not found or the data was not consistent
 * \retval  MEMIF_BLOCK_INVALID         Block was previously invalidated with an invalidate order
 * \retval  MEMIF_JOB_FAILED            Read failed
*/
LOCAL_INLINE MemIf_JobResultType Fee_Prv_FsIfReadDo(void)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    return(rba_FeeFs2_ReadDo());
    #endif
}

/**
 * \brief   Do the work of an invalidate job.
 *
 * \retval  MEMIF_JOB_PENDING   Invalidate is not yet finished
 * \retval  MEMIF_JOB_OK        Invalidate finished successfully
 * \retval  MEMIF_JOB_FAILED    Invalidate failed
*/
LOCAL_INLINE MemIf_JobResultType Fee_Prv_FsIfInvalidateBlockDo(void)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    return(rba_FeeFs2_InvalidateBlockDo());
    #endif
}

/**
 * \brief   Do the work of an erase immediate job.
 *
 * \retval  MEMIF_JOB_PENDING   Erase immediate is not yet finished
 * \retval  MEMIF_JOB_OK        Erase immediate finished successfully
 * \retval  MEMIF_JOB_FAILED    Erase immediate failed
 *
 * \attention   Currently no file system supports erase immediate.
*/
LOCAL_INLINE MemIf_JobResultType Fee_Prv_FsIfEraseImmediateBlockDo(void)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    return(rba_FeeFs2_EraseImmediateBlockDo());
    #endif
}

/**
 * \brief   Let the file system perform some background actions.
 *          This can for example mean erasing a sector in the background.
 *
 * \retval  MEMIF_JOB_PENDING   A background operation is currently running
 * \retval  MEMIF_JOB_OK        No background operation is currently running
*/
LOCAL_INLINE MemIf_JobResultType Fee_Prv_FsIfBackground(void)
{
    #if(2 == FEE_PRV_CFG_SELECTED_FS)
    return(rba_FeeFs2_Background());
    #endif
}

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/* FEE_PRV_FSIF_H */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
 **********************************************************************************************************************
 * End of header file: $Name______:$
 **********************************************************************************************************************
</BASDKey>*/
