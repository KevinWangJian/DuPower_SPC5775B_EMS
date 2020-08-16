

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "Fee.h"

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

#include "Crc.h"
#include "Fee_Prv.h"

/*
 **********************************************************************************************************************
 * Defines
 **********************************************************************************************************************
*/

#define FEE_PRV_MEDIUM_MAXSHREDDER  (FEE_SEC_HEADER_SIZE)
#define FEE_PRV_MEDIUM_FLASHBEG     (FEE_PHYS_SEC_START0)
#define FEE_PRV_MEDIUM_FLASHEND     (FEE_PRV_MEDIUM_FLASHBEG + (((FEE_PHYS_SEC_END0 + 1u) - FEE_PHYS_SEC_START0) * FEE_NUM_FLASH_BANKS_AVAILABLE))

#define FEE_PRV_MEDIUM_INVERASE_8BYTE       \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT, \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT, \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT, \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT, \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT, \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT, \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT, \
    (uint8)~FEE_PRV_CFG_ERASE_PATTERN_8BIT

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CONST_8
#include "Fee_MemMap.h"
static uint8 const Fee_Prv_MediumInverseErasePattern_cau8[FEE_PRV_MEDIUM_MAXSHREDDER] =
{
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE,
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE,
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE,
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE,
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE,
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE,
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE,
    FEE_PRV_MEDIUM_INVERASE_8BYTE, FEE_PRV_MEDIUM_INVERASE_8BYTE
};
#define FEE_STOP_SEC_CONST_8
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
/* Static */
static Fee_Prv_MediumCalcCrc_tst    Fee_Prv_MediumCalcCrc_st;
static Fee_Prv_MediumLoad_tst       Fee_Prv_MediumLoad_st;
static Fee_Prv_MediumWrite_tst      Fee_Prv_MediumWrite_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED_SECURED
#include "Fee_MemMap.h"
static Fee_Prv_Medium_tst           Fee_Prv_Medium_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED_SECURED
#include "Fee_MemMap.h"


#if (defined(FLS_RB_ROBUST_PROG_STATUS_API) && (TRUE == FLS_RB_ROBUST_PROG_STATUS_API))
#define FEE_START_SEC_VAR_CLEARED_8_SECURED
#include "Fee_MemMap.h"
static uint8 Fee_Prv_MediumRescueBfr_au8[RBA_FLS_WORDLINE_SIZE];
#define FEE_STOP_SEC_VAR_CLEARED_8_SECURED
#include "Fee_MemMap.h"
#endif
/*
 **********************************************************************************************************************
 * Implementation
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"

/**
 * \brief   Check the status of flash jobs.
 *          In synchronous mode call the Fls_MainFunction until the job is not pending any more.
 *          In case the last flash order returned E_NOT_OK then MEMIF_JOB_FAILED is returned.
 *          This way the higher layers do not know whether an error occurred during job placing or job execution.
 *          In the end the reaction is typically always the same: Retry or abort.
 *          To reduce the number of software paths MEMIF_JOB_FAILED and E_NOT_OK are both mapped to MEMIF_JOB_FAILED.
 *
 * \retval  MEMIF_JOB_PENDING   Job still pending
 * \retval  MEMIF_JOB_OK        Job finished successfully
 * \retval  MEMIF_JOB_FAILED    Job finished with errors
*/
static MemIf_JobResultType Fee_Prv_MediumFlsDo(void)
{
    MemIf_JobResultType result_en = MEMIF_JOB_FAILED;
    if(E_OK == Fee_Prv_Medium_st.lastFlsResult_en)
    {
        if(TRUE == Fee_Prv_Medium_st.sync_b)
        {
            do
            {
                Fls_MainFunction();
            } while(MEMIF_JOB_PENDING == Fls_GetJobResult());
        }
        result_en = Fls_GetJobResult();
        if(MEMIF_BLOCK_INCONSISTENT == result_en)
        {
            result_en = MEMIF_JOB_FAILED;
        }
        Fee_Prv_DbgFailDump(result_en);
    }
    else
    {
        Fee_Prv_DbgDump();
    }
    return(result_en);
}

/**
 * \brief   Mark the medium buffer dirty
*/
static void Fee_Prv_MediumSetBfrDirty(void)
{
    Fee_Prv_Medium_st.limitLo_u32 = 0u;
    Fee_Prv_Medium_st.limitHi_u32 = 0u;
}

/**
 * \brief   Load some data from the flash to the RAM in the medium buffer.
 *          This is useful for buffered access to the flash.
 *
 * \param   adr_u32     Address in the flash to load from
 * \param   length_u32  Amount of bytes to load
 *
 * \retval  MEMIF_JOB_PENDING   Loading still going on
 * \retval  MEMIF_JOB_OK        Loading finished successfully
 * \retval  MEMIF_JOB_FAILED    Loading finished with an error (in this case the content of the buffer is undefined
*/
static MemIf_JobResultType Fee_Prv_MediumLoad(uint32 adr_u32, uint32 length_u32, Fee_Prv_MediumLoadMode_ten loadMode_en)
{
    MemIf_JobResultType result_en = MEMIF_JOB_PENDING;

    if(
        (Fee_Prv_Medium_st.limitLo_u32 <= (adr_u32 + 0u         )   ) &&
        (Fee_Prv_Medium_st.limitHi_u32 >= (adr_u32 + length_u32 )   )
    )
    {
        result_en = MEMIF_JOB_OK;
    }
    else
    {
        if(FEE_PRV_LOAD_BUSY_E != Fee_Prv_MediumLoad_st.state_en)
        {
            if(
                (FEE_PRV_MEDIUM_FLASHBEG <= (adr_u32 + 0u           )               ) && /* Address must be valid DFLASH address                            */
                (FEE_PRV_MEDIUM_FLASHEND >= (adr_u32 + length_u32   )               ) && /* Address must be valid DFLASH address                            */
                (length_u32              <= sizeof(Fee_Prv_Medium_st.buffer_u.u8)   ) && /* Request amount must fit into buffer                             */
                (0u                      == ((FEE_VIRTUAL_PAGE_SIZE - 1u) & adr_u32))    /* Only allow 32 bit aligned accesses to avoid alignment problems  */
            )
            {
                if(FEE_PRV_POSTLOAD_E == loadMode_en)
                {
                    Fee_Prv_MediumLoad_st.reloadAdr_u32 = Fee_Prv_LibMin(
                        adr_u32,
                        FEE_PRV_MEDIUM_FLASHEND - sizeof(Fee_Prv_Medium_st.buffer_u.u8)
                    );
                }
                else
                {
                    Fee_Prv_MediumLoad_st.reloadAdr_u32 = Fee_Prv_LibMax(
                        (adr_u32 - sizeof(Fee_Prv_Medium_st.buffer_u.u8)) + length_u32,
                        FEE_PRV_MEDIUM_FLASHBEG
                    );
                }

                /* Set buffer dirty */
                Fee_Prv_MediumSetBfrDirty();

                /* Start buffer load */
                Fee_Prv_MediumRead(Fee_Prv_MediumLoad_st.reloadAdr_u32, &Fee_Prv_Medium_st.buffer_u.u8[0u], sizeof(Fee_Prv_Medium_st.buffer_u.u8));

                Fee_Prv_MediumLoad_st.state_en = FEE_PRV_LOAD_BUSY_E;
            }
            else
            {
                result_en = MEMIF_JOB_FAILED;
            }
        }

        if(MEMIF_JOB_PENDING == result_en)
        {
            result_en = Fee_Prv_MediumReadDo();
        }

        if(MEMIF_JOB_PENDING != result_en)
        {
            Fee_Prv_MediumLoad_st.state_en = FEE_PRV_LOAD_IDLE_E;

            if(MEMIF_JOB_OK == result_en)
            {
                Fee_Prv_Medium_st.limitLo_u32 = Fee_Prv_MediumLoad_st.reloadAdr_u32;
                Fee_Prv_Medium_st.limitHi_u32 = Fee_Prv_MediumLoad_st.reloadAdr_u32 + sizeof(Fee_Prv_Medium_st.buffer_u.u8);
            }
        }
    }

    return(result_en);
}

/**
 * \brief   Start a programming operation on the flash.
 *          Contains the sole call of Fls_Write in the whole Fee!
 *
 * \param   adr_u32     Address to write to
 * \param   bfr_pcv     Buffer to write from
 * \param   length_u32  Amount of bytes to write
*/
static void Fee_Prv_MediumProgram(uint32 adr_u32, void const * bfr_pcv, uint32 length_u32)
{
    Fee_Prv_MediumSetBfrDirty();

    /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
    Fee_Prv_Medium_st.lastFlsResult_en = Fls_Write(adr_u32, bfr_pcv, length_u32);
}

/**
 * \brief   Do the work for a program job.
*/
static MemIf_JobResultType Fee_Prv_MediumProgramDo(void)
{
    return(Fee_Prv_MediumFlsDo());
}

/**
 * \brief   Set synchronous (polling) or asynchronous flash access.
 *
 * \param   newSync_b   TRUE = synchronous, FALSE = asynchronous
 *
 * \attention   If the flash access is set to synchronous the Fee_MainFunction can take very long!
 *              Calling this function must consider the scheduling environment.
 *              Typically synchronous flash access is only acceptable in init.
*/
void Fee_Prv_MediumSetSync(boolean newSync_b)
{
    Fee_Prv_Medium_st.sync_b = newSync_b;
}

/**
 * \brief   Start a read operation from the flash.
 *          Contains the sole call of Fls_Read in the whole Fee!
 *
 * \param   adr_u32     Address to read from
 * \param   bfr_pv      Buffer to read to
 * \param   length_u32  Amount of bytes to read
*/
void Fee_Prv_MediumRead(uint32 adr_u32, void * bfr_pv, uint32 length_u32)
{
    /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
    Fee_Prv_Medium_st.lastFlsResult_en = Fls_Read(adr_u32, bfr_pv, length_u32);
}

/**
 * \brief   Start a write operation to the flash.
 *          Contains the sole call of Fls_Write in the whole Fee!
 *
 * \param   adr_u32     Address to write to
 * \param   bfr_pcv     Buffer to write from
 * \param   length_u32  Amount of bytes to write
*/
void Fee_Prv_MediumWrite(uint32 adr_u32, void const * bfr_pcv, uint32 length_u32)
{
    Fee_Prv_MediumWrite_st.adr_u32      = adr_u32;
    Fee_Prv_MediumWrite_st.bfr_pcv      = bfr_pcv;
    Fee_Prv_MediumWrite_st.length_u32   = length_u32;
    Fee_Prv_MediumWrite_st.done_u32     = 0u;
    FEE_PRV_LIBTRANS(Fee_Prv_MediumWrite_st, FEE_PRV_MEDIUM_WRITE_BLANKCHECK_E);
}

/**
 * \brief   Erase a part of the flash.
 *          Contains the sole call of Fls_Erase in the whole Fee!
 *
 * \param   adr_u32     Address where the erase shall begin
 * \param   length_u32  Amount of bytes to erase
*/
void Fee_Prv_MediumErase(uint32 adr_u32, uint32 length_u32)
{
    Fee_Prv_MediumSetBfrDirty();
    Fee_Prv_Medium_st.lastFlsResult_en = Fls_Erase(adr_u32, length_u32);
}

/**
 * \brief   Compare the content of a piece of flash with the content of a piece of RAM
 *          Contains the sole call of Fls_Compare in the whole Fee!
 *
 * \param   flsAdr_u32  Address in flash where the compare shall start
 * \param   bfr_pcv     Address in the RAM where the compare shall start
 * \param   length_u32  Amount of bytes to compare
*/
void Fee_Prv_MediumCompare(uint32 flsAdr_u32, void const * bfr_pcv, uint32 length_u32)
{
    /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
    Fee_Prv_Medium_st.lastFlsResult_en = Fls_Compare(flsAdr_u32, bfr_pcv, length_u32);
}

/**
 * \brief   Check whether a piece of flash is erased or programmed.
 *          Contains the sole call of Fls_Rb_BlankCheck in the whole Fee!
 *
 * \param   adr_u32     Address in flash where the blank check shall start
 * \param   length_u32  Amount of bytes which shall be checked
*/
void Fee_Prv_MediumBlankCheck(uint32 adr_u32, uint32 length_u32)
{
    /*
     * Currently a buffer for the blank check is not provided to the flash (NULL_PTR argument).
     * This is done since the Fee does currently not support any flashes which need a buffer for a blank check.
     * For example RENESAS flash is not yet supported since it does not support overprogramming of flash cells.
     */
    Fee_Prv_Medium_st.lastFlsResult_en = Fls_Rb_BlankCheck(adr_u32, NULL_PTR, length_u32);
}

/**
 * \brief   Destroy already programmed data.
 *          This is typically realized by overprogramming with the inverse erase pattern.
 *
 * \param   adr_u32     Address of the data which shall be shredded
 * \param   length_u32  Amount of bytes to shredder
*/
void Fee_Prv_MediumShredder(uint32 adr_u32, uint32 length_u32)
{
    if(length_u32 <= sizeof(Fee_Prv_MediumInverseErasePattern_cau8))
    {
        Fee_Prv_MediumProgram(
            adr_u32,
            &Fee_Prv_MediumInverseErasePattern_cau8[0u],
            length_u32
        );
    }
    else
    {
        Fee_Prv_Medium_st.lastFlsResult_en = E_NOT_OK;
    }
}

/**
 * \brief   Calculate the CRC directly from the flash.
 *
 * \param   adr_u32     Address where the calculation shall start
 * \param   length_u32  Amount of bytes to consider
 * \param   crc_pu32    Point to an uint32 where the result is placed
 * \param   firstCall_b Is this the first call for a chain of CRC calculations or not
*/
void Fee_Prv_MediumCalcCrc(uint32 adr_u32, uint32 length_u32, uint32 * crc_pu32, boolean firstCall_b)
{
    Fee_Prv_MediumCalcCrc_st.nrBytesDone_u32    = 0;
    Fee_Prv_MediumCalcCrc_st.length_u32         = length_u32;
    Fee_Prv_MediumCalcCrc_st.crc_pu32           = crc_pu32;
    Fee_Prv_MediumCalcCrc_st.firstCall_b        = firstCall_b;

    Fee_Prv_MediumSetIterator(adr_u32);
}

/**
 * \brief   Do the work for a read job.
*/
MemIf_JobResultType Fee_Prv_MediumReadDo(void)
{
    return(Fee_Prv_MediumFlsDo());
}

/**
 * \brief   Before programming assure that the space which shall be programmed is blank
 *
 * \pre     (BLANKCHECK == state)
 * \post    (MEMIF_JOB_OK      == result) && (PROGRAM       == state) && (TRUE == entry )
 *          (MEMIF_JOB_PENDING == result) && (BLANKCHECK    == state) && (FALSE == entry)
 *          (MEMIF_JOB_FAILED  == result)
*/
static MemIf_JobResultType Fee_Prv_MediumWrite_BlankCheck(Fee_Prv_MediumWrite_tst * fsm_pst)
{
    MemIf_JobResultType result_en;

    if(FEE_PRV_LIBENTRY)
    {
        Fee_Prv_MediumBlankCheck(fsm_pst->adr_u32, fsm_pst->length_u32);
    }

    result_en = Fee_Prv_MediumBlankCheckDo();

    if(MEMIF_JOB_OK == result_en)
    {
        FEE_PRV_LIBSC(FEE_PRV_MEDIUM_WRITE_PROGRAM_E);
    }

    return(result_en);
}

/**
 * \brief   After it was checked that the space is blank,
 *          copy the user data to an internal buffer and start programming using this buffer.
 *
 * \pre     (WRITE == state)
 * \post    (bytes2Program_u32 = min(size(Internal Buffer), length - done))
 * \post    (Internal Buffer == External Buffer)
 * \post    (Dirty(Internal Buffer))
 * \post    (MEMIF_JOB_OK      == result) && (COMPARE == state) && (TRUE == entry )
 *          (MEMIF_JOB_PENDING == result) && (PROGRAM == state) && (FALSE == entry)
 *          (MEMIF_JOB_FAILED  == result)
*/
static MemIf_JobResultType Fee_Prv_MediumWrite_Program(Fee_Prv_MediumWrite_tst * fsm_pst)
{
    MemIf_JobResultType result_en;
    uint8 const *       startAdr_pcu8;

    if(FEE_PRV_LIBENTRY)
    {
        /*
         * Need to convert the void const * to a uint8 const * pointer to add the offset of the already done bytes.
         * Pointer arithmetic with void pointers is not senseful
         */

        /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
        startAdr_pcu8  = fsm_pst->bfr_pcv;
        startAdr_pcu8 += fsm_pst->done_u32;

        fsm_pst->bytes2Program_u32 = Fee_Prv_LibMin(sizeof(Fee_Prv_Medium_st.buffer_u.u8), fsm_pst->length_u32 - fsm_pst->done_u32);
        Fee_Prv_LibMemCopy(startAdr_pcu8, &Fee_Prv_Medium_st.buffer_u.u8[0u], fsm_pst->bytes2Program_u32);
        Fee_Prv_MediumSetBfrDirty();

        Fee_Prv_MediumProgram(fsm_pst->adr_u32 + fsm_pst->done_u32, &Fee_Prv_Medium_st.buffer_u.u8[0u], fsm_pst->bytes2Program_u32);
    }

    result_en = Fee_Prv_MediumProgramDo();

    if(MEMIF_JOB_OK == result_en)
    {
        FEE_PRV_LIBSC(FEE_PRV_MEDIUM_WRITE_COMPARE_E);
    }

    return(result_en);
}

/**
 * \brief   Compare what should have been programmed with what was actually programmed
 *
 * \pre     (COMPARE == state)
 * \post    (MEMIF_JOB_OK      == result) && (PROGRAM   == state) && (TRUE  == entry) && (done = doneOld + bytes2Program) && (done <  length)
 *          (MEMIF_JOB_OK      == result) && (FINAL     == state) && (TRUE  == entry) && (done = doneOld + bytes2Program) && (done >= length)
 *          (MEMIF_JOB_PENDING == result) && (COMPARE   == state) && (FALSE == entry)
 *          (MEMIF_JOB_FAILED  == result)
*/
static MemIf_JobResultType Fee_Prv_MediumWrite_Compare(Fee_Prv_MediumWrite_tst * fsm_pst)
{
    MemIf_JobResultType result_en;

    if(FEE_PRV_LIBENTRY)
    {
        Fee_Prv_MediumCompare(fsm_pst->adr_u32 + fsm_pst->done_u32, &Fee_Prv_Medium_st.buffer_u.u8[0u], fsm_pst->bytes2Program_u32);
    }

    result_en = Fee_Prv_MediumCompareDo();

    if(MEMIF_JOB_OK == result_en)
    {
        fsm_pst->done_u32 += fsm_pst->bytes2Program_u32;
        if(fsm_pst->done_u32 < fsm_pst->length_u32)
        {
            FEE_PRV_LIBSC(FEE_PRV_MEDIUM_WRITE_PROGRAM_E);
        }
        else
        {
            FEE_PRV_LIBSC(FEE_PRV_MEDIUM_WRITE_FINAL_E);
        }
    }

    return(result_en);
}

/**
 * \brief   Do the work for a write job.
*/
MemIf_JobResultType Fee_Prv_MediumWriteDo(void)
{
    Fee_Prv_MediumWrite_tst *   fsm_pst;
    MemIf_JobResultType         result_en;

    fsm_pst = &Fee_Prv_MediumWrite_st;

    do
    {
        switch(fsm_pst->state_en)
        {
            case FEE_PRV_MEDIUM_WRITE_BLANKCHECK_E: result_en = Fee_Prv_MediumWrite_BlankCheck(fsm_pst);    break;
            case FEE_PRV_MEDIUM_WRITE_PROGRAM_E:    result_en = Fee_Prv_MediumWrite_Program(fsm_pst);       break;
            case FEE_PRV_MEDIUM_WRITE_COMPARE_E:    result_en = Fee_Prv_MediumWrite_Compare(fsm_pst);       break;
            default:                                result_en = MEMIF_JOB_FAILED;                           break;
        }
    } while((MEMIF_JOB_OK == result_en) && (FEE_PRV_MEDIUM_WRITE_FINAL_E != fsm_pst->state_en));

    if(MEMIF_JOB_PENDING != result_en)
    {
        FEE_PRV_LIBSC(FEE_PRV_MEDIUM_WRITE_IDLE_E);
    }

    return(result_en);
}


/**
 * \brief   Do the work for an erase job.
*/
MemIf_JobResultType Fee_Prv_MediumEraseDo(void)
{
    return(Fee_Prv_MediumFlsDo());
}

/**
 * \brief   Do the work for a compare job.
*/
MemIf_JobResultType Fee_Prv_MediumCompareDo(void)
{
    return(Fee_Prv_MediumFlsDo());
}

/**
 * \brief   Do the work for a blank check job.
*/
MemIf_JobResultType Fee_Prv_MediumBlankCheckDo(void)
{
    return(Fee_Prv_MediumFlsDo());
}

/**
 * \brief   Do the work for a shredder job.
*/
MemIf_JobResultType Fee_Prv_MediumShredderDo(void)
{
    MemIf_JobResultType result_en;

    result_en = Fee_Prv_MediumProgramDo();

    if(MEMIF_JOB_FAILED == result_en)
    {
        /*
         * IFX flash driver returns MEMIF_JOB_OK on overprogramming already programmed pages.
         * JDP/ST flash driver returns MEMIF_JOB_FAILED on overprogramming.
         * In order to equalize the behaviour a FAILED job is interpreted as OK job for overprogramming.
         */
        result_en = MEMIF_JOB_OK;
    }

    return(result_en);
}

/**
 * \brief   The worker function for the CRC calculation.
 *
 * \return                      Job status
 * \retval  MEMIF_JOB_PENDING:  Job pending
 * \retval  MEMIF_JOB_OK:       CRC calculation successful
 * \retval  MEMIF_JOB_FAILED:   CRC calculation not successful (currently not possible)
*/
MemIf_JobResultType Fee_Prv_MediumCalcCrcDo(void)
{
    void               const *  ptr_pcv;
    MemIf_JobResultType         result_en   = MEMIF_JOB_PENDING;
    uint32 nrBytesToConsider_u32            = Fee_Prv_LibMin(
        sizeof(Fee_Prv_Medium_st.buffer_u.u8),
        Fee_Prv_MediumCalcCrc_st.length_u32 - Fee_Prv_MediumCalcCrc_st.nrBytesDone_u32
    );

    if(0u < nrBytesToConsider_u32)
    {
        if(MEMIF_JOB_OK == Fee_Prv_MediumNext(nrBytesToConsider_u32, &ptr_pcv))
        {
            /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
            *Fee_Prv_MediumCalcCrc_st.crc_pu32 = Crc_CalculateCRC32(
                ptr_pcv,
                nrBytesToConsider_u32,
                *Fee_Prv_MediumCalcCrc_st.crc_pu32,
                Fee_Prv_MediumCalcCrc_st.firstCall_b
            );

            Fee_Prv_MediumCalcCrc_st.nrBytesDone_u32 += nrBytesToConsider_u32;
            Fee_Prv_MediumCalcCrc_st.firstCall_b      = FALSE;
        }
    }

    /* Length should never be smaller, but to be safe consider it */
    if(Fee_Prv_MediumCalcCrc_st.length_u32 <= Fee_Prv_MediumCalcCrc_st.nrBytesDone_u32)
    {
        result_en = MEMIF_JOB_OK;
    }

    return(result_en);
}

/**
 * \brief   Set the iterator to a location in the flash.
 *          From there on the iterator can be used to step forwards or backwards through the flash.
 *
 * \param   adr_u32     Address in flash where the iterator shall point to
*/
void Fee_Prv_MediumSetIterator(uint32 adr_u32)
{
    Fee_Prv_Medium_st.iterator_u32 = adr_u32;
}

/**
 * \brief   Get the value of the flash iterator.
 * \seealso Fee_Prv_MediumSetIterator
*/
uint32 Fee_Prv_MediumGetIterator(void)
{
    return(Fee_Prv_Medium_st.iterator_u32);
}

#if (defined(FLS_RB_ROBUST_PROG_STATUS_API) && (TRUE == FLS_RB_ROBUST_PROG_STATUS_API))

/**
 * \brief   Get the size of a single wordline.
 *
 * \return  Size of a wordline in the flash in bytes
*/
uint32 Fee_Prv_MediumGetWlSize(void)
{
    return(RBA_FLS_WORDLINE_SIZE);
}
/**
 * \brief   Find out whether the flash lost data on the same word line during last programming action.
 *
 * \return  Word line error occurred YES/NO
*/
boolean Fee_Prv_MediumHasWlError(void)
{
    uint32              dummyErrorAdr_u32;
    uint8           *   dummyBfr_pu8;
    uint32              dummyLength_u32;
    Std_ReturnType      status_en;
    boolean             result_b;

    status_en = Fls_Rb_GetRobustProgStatus(&dummyErrorAdr_u32, &dummyBfr_pu8, &dummyLength_u32);

    result_b = FALSE;
    if(E_NOT_OK == status_en)
    {
        result_b = TRUE;
    }
    return(result_b);
}

/**
 *  \brief  Get the address of a damaged word line.
 *
 * \return  Address of the damaged word line that was damaged with the last programming action
*/
uint32 Fee_Prv_MediumGetWlErrorAdr(void)
{
    uint32      errorAdr_u32;
    uint8   *   dummyBfr_pu8;
    uint32      dummyLength_u32;

    (void)Fls_Rb_GetRobustProgStatus(&errorAdr_u32, &dummyBfr_pu8, &dummyLength_u32);

    return(errorAdr_u32);
}

/**
 *  \brief  Get the amount of data that was rescued before a word line was damaged.
 *
 * \return  Amount of rescued data
*/
uint32 Fee_Prv_MediumGetWlErrorLength(void)
{
    uint32      dummyErrorAdr_u32;
    uint8   *   dummyBfr_pu8;
    uint32      length_u32;

    (void)Fls_Rb_GetRobustProgStatus(&dummyErrorAdr_u32, &dummyBfr_pu8, &length_u32);

    return(length_u32);
}

/**
 * \brief   Safe the data of the defect wordline from the flash buffer to the Fee buffer.
 *          This is required since the data of the wordline can be thrown away with every flash job.
*/
void Fee_Prv_MediumRescueWlData(void)
{
    uint32              dummyErrorAdr_u32;
    uint8           *   flsBfr_pu8;
    uint32              length_u32;
    Std_ReturnType      status_en;

    status_en = Fls_Rb_GetRobustProgStatus(&dummyErrorAdr_u32, &flsBfr_pu8, &length_u32);

    if((E_NOT_OK == status_en) && (NULL_PTR != flsBfr_pu8))
    {
        Fee_Prv_LibMemCopy(flsBfr_pu8, &Fee_Prv_MediumRescueBfr_au8[0u], length_u32);
    }
}

/**
 * \brief   Get a pointer to the data that was previously rescued with Fee_Prv_MediumRescueWlData().
 *
 * \return  Pointer to previously rescued data
*/
uint8 const * Fee_Prv_MediumGetWlData(void)
{
    return((uint8 const *)&Fee_Prv_MediumRescueBfr_au8[0u]);
}
#endif


/*
 * Those functions are activated if direct read from the Fls is not active.
 * Currently this is not fully supported in the whole Fee so that part must currently always stay OFF.
*/

/**
 * \brief   Set a pointer to the current iterator then increase the iterator for specified length.
 *
 * \param   length_u32  Amount of bytes to step after pointer is set to current iterator
 * \param   ptr_cppcv   Pointer to the pointer which shall be set to the address of the iterator
 *
 * \retval  MEMIF_JOB_PENDING   Job still pending
 * \retval  MEMIF_JOB_OK        Job finished successfully
 * \retval  MEMIF_JOB_FAILED    Job finished with errors
*/
MemIf_JobResultType Fee_Prv_MediumNext(uint32 length_u32, void const * * ptr_cppcv)
{
    MemIf_JobResultType result_en = Fee_Prv_MediumLoad(Fee_Prv_Medium_st.iterator_u32, length_u32, FEE_PRV_POSTLOAD_E);

    if(MEMIF_JOB_OK == result_en)
    {
        uint32 index_u32                = Fee_Prv_Medium_st.iterator_u32 - Fee_Prv_Medium_st.limitLo_u32;
        *ptr_cppcv                      = &Fee_Prv_Medium_st.buffer_u.u8[index_u32];
        Fee_Prv_Medium_st.iterator_u32  += length_u32;
    }

    return(result_en);
}

/**
 * \brief   Set a pointer to the current iterator then increase the iterator for specified length.
 *
 * \param   length_u32  Amount of bytes to step after pointer is set to current iterator
 * \param   ptr_cppcv   Pointer to the pointer which shall be set to the address of the iterator
 *
 * \retval  MEMIF_JOB_PENDING   Job still pending
 * \retval  MEMIF_JOB_OK        Job finished successfully
 * \retval  MEMIF_JOB_FAILED    Job finished with errors
*/
MemIf_JobResultType Fee_Prv_MediumPre(uint32 length_u32, void const * * ptr_cppcv)
{
    MemIf_JobResultType result_en = Fee_Prv_MediumLoad(Fee_Prv_Medium_st.iterator_u32, length_u32, FEE_PRV_PRELOAD_E);

    if(MEMIF_JOB_OK == result_en)
    {
        uint32 index_u32                = Fee_Prv_Medium_st.iterator_u32 - Fee_Prv_Medium_st.limitLo_u32;
        *ptr_cppcv                      = &Fee_Prv_Medium_st.buffer_u.u8[index_u32];
        Fee_Prv_Medium_st.iterator_u32  -= length_u32;
    }

    return(result_en);
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
